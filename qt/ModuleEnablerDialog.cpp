/* _*_ C++ _*_ */
#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <libutil/TTAssert.h>

#include <QtCore/QTimer>
#include <QtCore/QUrl>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLayout>
#include <QtGui/QToolTip>
#include <QtGui/QCheckBox>

#include <libbase/ExtensionRegisterer.h>
#include <liblogger/ologger.h>

#include <libbasegui/ModuleEnablerDialogTreeModel.h>
#include "ModuleEnablerDialog.h"

LOGGER_SUBSYSTEM("BASE:GUI", "Module enabler dialog");

namespace tt_utils {

ModuleEnablerDialog::ModuleEnablerDialog(QWidget* parent, Qt::WindowFlags f) :
    QDialog(parent, f), mTreeStableTicks(2) {
  setWindowTitle(tr("Enable or disable modules"));
  resize(640, 480);

  QStringList comboHeaders;
  comboHeaders.push_back(tr("All"));
  comboHeaders.push_back(tr("Systems"));
  mCombo = new QComboBox;
  mCombo->addItems(comboHeaders);

  mSourceTreeModel = new ModuleEnablerDialogTreeModel(this);
  mProxyTreeModel = new ModuleEnablerDialogTreeSortModel(this);
  mProxyTreeModel->setSourceModel(mSourceTreeModel);
  mQTreeView = new QTreeView;
  mQTreeView->setModel(mProxyTreeModel);
  mQTreeView->setSortingEnabled(true);

  {
    QHBoxLayout * buttonsLayout = new QHBoxLayout();
    QPushButton * buttonOk = new QPushButton(tr("&Ok"), this);
    QPushButton * buttonCancel = new QPushButton(tr("&Cancel"), this);
    buttonsLayout->addWidget(buttonOk);
    buttonsLayout->addWidget(buttonCancel);

    QVBoxLayout * mainLayout = new QVBoxLayout();
    mainLayout->addWidget(mCombo);
    mainLayout->addWidget(mQTreeView);
    mainLayout->addLayout(buttonsLayout);
    this->setLayout(mainLayout);

    connect(buttonOk, SIGNAL(clicked()), this, SLOT(accept()));
    connect(buttonCancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(mCombo, SIGNAL(currentIndexChanged(int)), mSourceTreeModel,
    SLOT(comboIndexChanged(int)));
    connect(mCombo, SIGNAL(currentIndexChanged(int)), this,
        SLOT(comboIndexChanged()));
  }
}

ModuleEnablerDialog::~ModuleEnablerDialog() {
}

void ModuleEnablerDialog::done(int r) {
  mTreeStableTicks = 2;
  if (r != QDialog::Accepted) {
    // Dialog was rejected, no module should be enabled or disabled.
    mSourceTreeModel->restoreDefault();
  }
  QDialog::done(r);
  emit dialogFinished(r);
}

void ModuleEnablerDialog::comboIndexChanged(){
  mQTreeView->expandAll();
  mQTreeView->resizeColumnToContents(0);
}

void ModuleEnablerDialog::clearModuleInfo() {
  mSourceTreeModel->clear();
}

// set this vector as modules data
// for ModuleEnablerDialogTreeModel
void ModuleEnablerDialog::addModuleInfo(
    ModuleEnablerDialogTreeModel::ModuleVector v) {
  mSourceTreeModel->setModuleVector(v);
  mProxyTreeModel->sort(0, Qt::AscendingOrder);
  mQTreeView->expandAll();
  mQTreeView->resizeColumnToContents(0);
}

// returns pointer to QStringList of modules for
// which current enable state differs from <isEnabled>
QStringList * ModuleEnablerDialog::changedModules() const {
  return mSourceTreeModel->changedModules();
}

// returns current enable state
// of module with given <modName>
bool ModuleEnablerDialog::isModuleEnabled(const QString &modName) const {
  return mSourceTreeModel->isModuleEnabled(modName);
}

}
