/* -*- C++ -*- */

#ifndef MOSS_ModuleEnablerDialog_H
#define MOSS_ModuleEnablerDialog_H

#include <QtCore/QString>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLayout>
#include <QtGui/QPushButton>
#include <QtGui/QComboBox>
#include <QtCore/QAbstractItemModel>
#include <QtGui/QSortFilterProxyModel>

#include <libbasegui/ModuleEnablerDialogTreeModel.h>

#include "basegui_dll_export.h"

namespace tt_utils{

class ModuleEnablerDialogTreeModel;

  /** dialog window for enabling modules */
  class DllExport ModuleEnablerDialog : public QDialog {

    Q_OBJECT

  public:
    ModuleEnablerDialog(QWidget* parent,
                        Qt::WindowFlags f = 0);
    ~ModuleEnablerDialog();

    void clearModuleInfo();


    // returns pointer to QStringList of modules for
    // which current enable state differs from <isEnabled>
    QStringList * changedModules() const;

    // returns current enable state
    // of module with given <modName>
    bool isModuleEnabled(const QString &modName) const;

    //set this vector as modules data in TreeModel
    void addModuleInfo(ModuleEnablerDialogTreeModel::ModuleVector v);

  signals:
    void dialogFinished(int result);

  protected slots:
    void done(int r);
    void comboIndexChanged();

  private:
    enum ItemTypeT { meditModule, meditSystem };
    int mTreeStableTicks;

    QComboBox* mCombo;
    QTreeView* mQTreeView;
    ModuleEnablerDialogTreeModel* mSourceTreeModel;
    QSortFilterProxyModel* mProxyTreeModel;
    ItemTypeT mClickedItemType;
  };
}
#endif

