/*
 * ModuleEnablerDialogTreeModel.h
 *
 *  Created on: Aug 8, 2013
 *      Author: gregorp
 */

#ifndef MODULEENABLERDIALOGTREEMODEL_H_
#define MODULEENABLERDIALOGTREEMODEL_H_

#include <QtCore/QString>

#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLayout>
#include <QtGui/QTreeWidget>
#include <QtGui/QPushButton>
#include <QtGui/QComboBox>
#include <QtCore/QAbstractItemModel>
#include <QtGui/QSortFilterProxyModel>
#include <algorithm>
#include <memory>
#include <libutil/TTAssert.h>

namespace tt_utils {

// class extends QAbstractItemModel with linked list
// of TreeItem (nested class) that expose interface
// to model data (being std::vector<ModuleInfo> internally).
// this vector can be set using setModuleVector function
class ModuleEnablerDialogTreeModel : public QAbstractItemModel {
Q_OBJECT

private:
  enum ItemTypeT {
    All, Systems
  };
  Qt::CheckState checkedState_;
  #define ModuleEnablerDialog_CheckBoxColumn 1

public:
  typedef struct ModuleInfo {
    QString modName;
    QString displayedName;
    bool isEnabled;
    bool isFailed;
    bool isLoaded;
    bool currentlyEnabled;
    QString category;
  } ModuleInfo;

  typedef std::vector<ModuleInfo> ModuleVector;
  typedef std::vector<ModuleInfo*> pModuleVector;

private:
  // nested class which represents ModuleInfo
  // data on the tree
  class TreeItem {
  public:

    // distinguish which tree has been
    // clicked via combo box
    enum ItemTypeT {
      All, Systems
    };

    TreeItem(const QList<QVariant>& data, ItemTypeT tree,
        ModuleInfo& moduleInfo, TreeItem* parent = 0);
    TreeItem(const QList<QVariant> data, ItemTypeT tree, TreeItem* parent = 0) :
        mModuleInfo(*(new ModuleInfo())), mItemData(data), mParent(parent), mTree(tree) {
    }
    ~TreeItem();

    void appendChild(TreeItem *child);
    void deleteAllChildren(TreeItem* ptr);
    void deleteAllChildren();

    TreeItem* child(int row);
    int row() const;
    TreeItem* parent();
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;

    // set data in <column> to <value>
    void setData(int column, QVariant value) {
      mItemData[column] = value;
    }

    void setData(QList<QVariant> itemData) {
      mItemData = itemData;
    }

    // sets each child data in <column> to <value>
    void setChildrenData(int column, QVariant value);

    // sets children check state and updates
    // its currentlyEnabled as appropriate
    void updateChildren(Qt::CheckState value);

    void setHierarchy(int hierarchy) {
      mHierarchy = hierarchy;
    }

    const int hierarchy() {
      return mHierarchy;
    }

    // search utilities: functions and unary predicates

    // hasChildChecked returns true if any ModuleInfo
    // represented by this TreeItem children is checked
    // otherwise returns false
    bool hasChildChecked() const {
      for (QList<TreeItem*>::const_iterator it = mChildren.begin();
          it != mChildren.end(); it++) {
        QVariant stateItem = (*it)->data(ModuleEnablerDialog_CheckBoxColumn);
        if (stateItem == Qt::Checked) {
          return true;
        }
      }
      return false;
    }

    // hasChildUnchecked returns true if any ModuleInfo
    // represented by this TreeItem children is unchecked
    // otherwise returns false
    bool hasChildUnchecked() const {
      for (QList<TreeItem*>::const_iterator it = mChildren.begin();
          it != mChildren.end(); it++) {
        QVariant stateItem = (*it)->data(ModuleEnablerDialog_CheckBoxColumn);
        if (stateItem == Qt::Unchecked) {
          return true;
        }
      }
      return false;
    }

    // hasChildpartiallyChecked returns true if any ModuleInfo
    // represented by this TreeItem children is partially checked
    // otherwise returns false
    bool hasChildPartiallyChecked() const {
      for (QList<TreeItem*>::const_iterator it = mChildren.begin();
          it != mChildren.end(); it++) {
        QVariant stateItem = (*it)->data(ModuleEnablerDialog_CheckBoxColumn);
        if (stateItem == Qt::PartiallyChecked) {
          return true;
        }
      }
      return false;
    }

    struct checked {
      bool operator()(const TreeItem* t) {
        return t->data(ModuleEnablerDialog_CheckBoxColumn) == Qt::Checked;
      }
    };

    struct unchecked {
      bool operator()(const TreeItem* t) {
        return t->data(ModuleEnablerDialog_CheckBoxColumn) == Qt::Unchecked;
      }
    };

    bool hasChildChecked(TreeItem* item) {
      return std::find_if(item->childItems().begin(), item->childItems().end(),
          checked()) != item->childItems().end();
    }

    bool hasChildUnchecked(TreeItem* item) {
      return std::find_if(item->childItems().begin(), item->childItems().end(),
          unchecked()) != item->childItems().end();
    }

    bool partiallyChecked() const {
      for (QList<TreeItem*>::const_iterator it = mChildren.begin();
          it != mChildren.end(); it++) {
        if ((*it)->hasChildChecked() && (*it)->hasChildUnchecked())
          return true;
      }
      return false;
    }

    ItemTypeT tree() {
      return mTree;
    }

    QList<TreeItem*>& childItems() {
      return mChildren;
    }

    ModuleInfo& mModuleInfo;
    QModelIndex mIndex;

  private:
    QList<TreeItem*> mChildren;
    QList<QVariant> mItemData;
    TreeItem* mParent;
    int mHierarchy; // 1:module  -1:root  0:anything else
    ItemTypeT mTree;
  };

public:
  ModuleEnablerDialogTreeModel(QObject *parent = 0);

  // deletes all children and sets
  // root pointers to NULL
  ~ModuleEnablerDialogTreeModel();

  // returns internal index data for a given role.
  // internal index data is a pointer to an instance
  // of TreeItem which represents information about
  // its ModuleInfo
  QVariant data(const QModelIndex &index, int role) const;

  // returns the item flags for the given index
  Qt::ItemFlags flags(const QModelIndex &index) const;

  // returns header info
  QVariant headerData(int section, Qt::Orientation orientation,
      int role = Qt::DisplayRole) const;

  QModelIndex index(int row, int column, const QModelIndex &parent =
      QModelIndex()) const;
  QModelIndex parent(const QModelIndex &index) const;
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;

  void setClickedItemType(ItemTypeT clickedItemType) {
    mClickedItemType = clickedItemType;
  }

  // sets a given vector as modules data
  // and populates tree
  void setModuleVector(ModuleVector v) {
    mModuleVector = v;
    ItemTypeT currentItem = mClickedItemType;
    comboIndexChanged(Systems);
    comboIndexChanged(All);
    comboIndexChanged(currentItem);
  }

  // sets the role data for the item at <index>
  // to <value> and updates affected TreeItems
  // and ModuleInfo. returns true if successful
  // otherwise returns false
  bool setData(const QModelIndex & index, const QVariant & value, int role =
      Qt::EditRole);

  // reverts enable state for all ModuleInfo
  // found in <mModuleVector> to its origin
  void restoreDefault() {
    std::for_each(mModuleVector.begin(), mModuleVector.end(), restore());
  }

  // deletes all children and sets
  // root pointers to NULL
  void clear();

  // returns pointer to QStringList of modules for
  // which current enable state differs from <isEnabled>
  QStringList* changedModules() const;

  // returns current enable state
  // of module with given <modName>
  bool isModuleEnabled(const QString& modName) const;

  struct restore {
    void operator()(ModuleInfo& m) {
      m.currentlyEnabled = m.isEnabled;
    }
  };

  struct displayedNameCmp {
    QString name_;
    bool operator()(const TreeItem* t) {
      return t->mModuleInfo.displayedName == name_;
    }
    displayedNameCmp(QString name) :
        name_(name) {
    }
  };

public slots:

  // populate model again after combo box
  // chosen value has been changed
  void comboIndexChanged(int index) {
    beginResetModel();
    mClickedItemType = (ItemTypeT) index;
    setupModelData();
    endResetModel();
  }

private:

  // populate model data for each ModuleInfo
  // found in <mModuleVector>, if <mRoot>
  // already exists just point it to appropriate
  // items tree (All or Systems)
  void setupModelData();

  // updates all affected TreeItems with respect
  // to tree from which it was called
  void updateModelItems(TreeItem* item);

  // updates all affected TreeItems without respect
  // to tree from which it was called
  void updateParents(TreeItem* item);

  // returns a map associating categories with ModuleInfo
  std::map<QString, pModuleVector*>* moduleToCategoryVectorsMap(
      ModuleVector& v) const;

  // returns the vector of ModuleInfo categories
  // will create new <mCategoryModuleVecMap>
  std::vector<QString>* getCategories(ModuleVector& v);

  TreeItem* mRoot, *mRoot_All, *mRoot_Systems;
  ItemTypeT mClickedItemType;
  ModuleVector mModuleVector;

  typedef std::map<QString, pModuleVector*> StringModuleVecMap;
  std::auto_ptr<StringModuleVecMap> mCategoryModuleVecMap;

  // this function will expand a tree structure by
  // mapping each ModuleInfo to system and category
  void appendCategoryChildItems(TreeItem* root,
      const std::auto_ptr<StringModuleVecMap>& categoryModuleVecMap);

};

// helper class to sort the tree
class ModuleEnablerDialogTreeSortModel : public QSortFilterProxyModel {
  Q_OBJECT
public:
  ModuleEnablerDialogTreeSortModel(QObject* parent) : QSortFilterProxyModel(parent) {}

  // maps proxy index to source index
  // and returns its data
  QVariant data(const QModelIndex& index, int role) const;

  // calls source model setData
  // and updates proxy model
  bool setData(const QModelIndex & index, const QVariant & value, int role =
        Qt::EditRole);
};

} /* namespace tt_utils */
#endif /* MODULEENABLERDIALOGTREEMODEL_H_ */
