/*
 * ModuleEnablerDialogTreeModel.cpp
 *
 *  Created on: Aug 8, 2013
 *      Author: gregorp
 */

#include "ModuleEnablerDialogTreeModel.h"
#include <libbase/ExtensionRegisterer.h>

namespace tt_utils {

#define ModuleEnablerDialog_ModNameColumn  3
#define ModuleEnablerDialog_CheckBoxColumn 1

ModuleEnablerDialogTreeModel::TreeItem::TreeItem(const QList<QVariant> &data,
    ItemTypeT tree, ModuleInfo& moduleInfo, TreeItem *parent) :
    mModuleInfo(moduleInfo), mItemData(data), mParent(parent), mTree(tree) {
  mHierarchy = 0;
}

ModuleEnablerDialogTreeModel::TreeItem::~TreeItem() {
  qDeleteAll(mChildren);
  mChildren.clear();
}

void ModuleEnablerDialogTreeModel::TreeItem::appendChild(TreeItem *item) {
  mChildren.append(item);
}

ModuleEnablerDialogTreeModel::TreeItem* ModuleEnablerDialogTreeModel::TreeItem::child(
    int row) {
  return mChildren.value(row);
}

int ModuleEnablerDialogTreeModel::TreeItem::childCount() const {
  return mChildren.count();
}

int ModuleEnablerDialogTreeModel::TreeItem::columnCount() const {
  return mItemData.count();
}

QVariant ModuleEnablerDialogTreeModel::TreeItem::data(int column) const {
  return mItemData.value(column);
}

ModuleEnablerDialogTreeModel::TreeItem* ModuleEnablerDialogTreeModel::TreeItem::parent() {
  return mParent;
}

int ModuleEnablerDialogTreeModel::TreeItem::row() const {
  if (mParent)
    return mParent->mChildren.indexOf(const_cast<TreeItem*>(this));

  return 0;
}

//sets each child data in <column> to <value>
void ModuleEnablerDialogTreeModel::TreeItem::setChildrenData(int column,
    QVariant value) {
  for (QList<TreeItem*>::iterator it = mChildren.begin(); it != mChildren.end();
      it++) {
    (*it)->setData(column, value);
  }
}

// sets children check state and updates
// its currentlyEnabled as appropriate
void ModuleEnablerDialogTreeModel::TreeItem::updateChildren(
    Qt::CheckState value) {
  for (QList<TreeItem*>::iterator it = mChildren.begin(); it != mChildren.end();
      it++) {
    (*it)->setData(ModuleEnablerDialog_CheckBoxColumn, value);
    (*it)->mModuleInfo.currentlyEnabled = (value == Qt::Checked ? true : false);
    if (!(*it)->childItems().isEmpty())
      (*it)->updateChildren(value);
  }
}

void ModuleEnablerDialogTreeModel::TreeItem::deleteAllChildren(TreeItem* ptr) {
  qDeleteAll(ptr->mChildren);
  ptr->mChildren.clear();
}
void ModuleEnablerDialogTreeModel::TreeItem::deleteAllChildren() {
  qDeleteAll(mChildren);
  mChildren.clear();
}

ModuleEnablerDialogTreeModel::ModuleEnablerDialogTreeModel(QObject *parent) :
    QAbstractItemModel(parent), checkedState_(Qt::Checked), mRoot(NULL), mRoot_All(
    NULL), mRoot_Systems(NULL) {
  mRoot = new TreeItem(QList<QVariant>(), TreeItem::All);
  mClickedItemType = All;
}

// deletes all children and sets
// root pointers to NULL
ModuleEnablerDialogTreeModel::~ModuleEnablerDialogTreeModel() {
  if(mRoot!=NULL) delete mRoot;
  mRoot = NULL;
  mRoot_All = NULL;
  mRoot_Systems = NULL;
}

int ModuleEnablerDialogTreeModel::columnCount(const QModelIndex &parent) const {
  if (parent.isValid())
    return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
  else
    return mRoot->columnCount();
}

// returns the item flags for the given index
Qt::ItemFlags ModuleEnablerDialogTreeModel::flags(
    const QModelIndex &index) const {
  if (!index.isValid())
    return 0;
  Qt::ItemFlags flags = QAbstractItemModel::flags(index);
  if (index.column() == ModuleEnablerDialog_CheckBoxColumn)
    flags |= Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;
  return flags;
}

// returns header info
QVariant ModuleEnablerDialogTreeModel::headerData(int section,
    Qt::Orientation orientation, int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    return mRoot->data(section);
  return QVariant();
}

QModelIndex ModuleEnablerDialogTreeModel::index(int row, int column,
    const QModelIndex &parent) const {
  if (!hasIndex(row, column, parent))
    return QModelIndex();

  TreeItem *parentItem;

  if (!parent.isValid()) {
    parentItem = mRoot;
  } else
    parentItem = static_cast<TreeItem*>(parent.internalPointer());

  TreeItem *childItem = parentItem->child(row);
  if (childItem) {
    if (parentItem == mRoot_Systems) {
      parentItem->mModuleInfo.currentlyEnabled =
          childItem->mModuleInfo.isEnabled;
      QVariant value = (
          childItem->mModuleInfo.isEnabled ? Qt::Checked : Qt::Unchecked);
    }
    return createIndex(row, column, childItem);
  } else {
    return QModelIndex();
  }
}

QModelIndex ModuleEnablerDialogTreeModel::parent(
    const QModelIndex &index) const {
  if (!index.isValid())
    return QModelIndex();

  TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
  TreeItem *parentItem = childItem->parent();

  if (parentItem == mRoot)
    return QModelIndex();

  return createIndex(parentItem->row(), 0, parentItem);
}

int ModuleEnablerDialogTreeModel::rowCount(const QModelIndex &parent) const {
  TreeItem *parentItem;
  if (parent.column() > 0)
    return 0;

  if (!parent.isValid())
    parentItem = mRoot;
  else
    parentItem = static_cast<TreeItem*>(parent.internalPointer());

  return parentItem->childCount();
}

// populate model data for each ModuleInfo
// found in <mModuleVector>, if <mRoot>
// already exists just point it to appropriate
// items tree (All or Systems)
void ModuleEnablerDialogTreeModel::setupModelData() {
  if (!mRoot) {
    mRoot = new TreeItem(QList<QVariant>(), TreeItem::All);
  }
  QList<QVariant> rootData1;
  rootData1.push_back(tr("Module name"));
  rootData1.push_back(tr("Enabled"));
  rootData1.push_back(tr("Extension status"));

  switch (mClickedItemType) {
  case All: {
    if (!mRoot_All) {
      mRoot_All = new TreeItem(rootData1, TreeItem::All);
      mRoot_All->mModuleInfo.displayedName = tr("Module name");
      mRoot_All->setHierarchy(-1);

      for (ModuleVector::iterator it = mModuleVector.begin();
          it != mModuleVector.end(); it++) {
        QList<QVariant> childData;
        childData << (*it).displayedName;
        childData << ((*it).isEnabled ? Qt::Checked : Qt::Unchecked);

        if (it->isFailed) {
          childData << (tr("Load failed"));
        } else if (it->isLoaded) {
          childData << (tr("Loaded"));
        } else {
          childData << (tr("Not loaded yet"));
        }
        if (!mRoot_Systems) {
          it->isEnabled = !it->isFailed && it->isEnabled;
          it->currentlyEnabled = it->isEnabled;
        }

        TreeItem* child = new TreeItem(childData, TreeItem::All, *it,
            mRoot_All);
        child->setData(ModuleEnablerDialog_CheckBoxColumn,
            (it->isEnabled ? Qt::Checked : Qt::Unchecked));
        child->setHierarchy(1);

        mRoot_All->appendChild(child);
      }
    }
    mRoot_All->setData(rootData1);
    mRoot = mRoot_All;
    break;
  }
  case Systems: {
    if (!mRoot_Systems) {
      mRoot_Systems = new TreeItem(rootData1, TreeItem::Systems);
      mRoot_Systems->mModuleInfo.displayedName = tr("System/Module name");
      mRoot_Systems->setHierarchy(-1);

      mCategoryModuleVecMap = std::auto_ptr<StringModuleVecMap>(
          moduleToCategoryVectorsMap(mModuleVector));
      appendCategoryChildItems(mRoot_Systems, mCategoryModuleVecMap);
    }
    mRoot_Systems->setData(rootData1);
    mRoot = mRoot_Systems;
    break;
  }
  default:
    TTAssert(0 == "Never gets here");
    break;
  }
}

// deletes all children and sets
// root pointers to NULL
void ModuleEnablerDialogTreeModel::clear() {
  if(mRoot!=NULL) delete mRoot;
  mRoot = NULL;
  mRoot_All = NULL;
  mRoot_Systems = NULL;
}

// returns pointer to QStringList of modules for
// which current enable state differs from <isEnabled>
QStringList* ModuleEnablerDialogTreeModel::changedModules() const {
  QStringList * list = new QStringList();
  for (ModuleVector::const_iterator it = mModuleVector.begin();
      it != mModuleVector.end(); it++) {
    if (it->currentlyEnabled != it->isEnabled) {
      list->push_back(it->modName);
    }
  }
  return list;
}

// returns current enable state
// of module with given <modName>
bool ModuleEnablerDialogTreeModel::isModuleEnabled(
    const QString &modName) const {
  ModuleVector::const_iterator it = mModuleVector.begin();
  while (it != mModuleVector.end() && !(it->modName == modName)) {
    it++;
  }
  TTAssert(it != mModuleVector.end());
  return it->currentlyEnabled;
}

// returns a map associating categories with ModuleInfo
std::map<QString, ModuleEnablerDialogTreeModel::pModuleVector*>* ModuleEnablerDialogTreeModel::moduleToCategoryVectorsMap(
    ModuleVector& v) const {
  std::auto_ptr<StringModuleVecMap> map(new StringModuleVecMap);
  for (ModuleVector::iterator it = v.begin(); it != v.end(); it++) {
    if ((*map).find((*it).category) == (*map).end()) {
      (*map)[(*it).category] = new pModuleVector;
    }
    (*map)[(*it).category]->push_back(&(*it));
  }
  return map.release();
}

// returns the vector of ModuleInfo categories
// will create new <mCategoryModuleVecMap>
std::vector<QString>* ModuleEnablerDialogTreeModel::getCategories(
    ModuleVector& v) {
  std::auto_ptr<std::vector<QString> > vector(new std::vector<QString>());
  mCategoryModuleVecMap = std::auto_ptr<StringModuleVecMap>(
            moduleToCategoryVectorsMap(mModuleVector));
  for(StringModuleVecMap::iterator it = mCategoryModuleVecMap->begin();
      it != mCategoryModuleVecMap->end(); it++){
    vector->push_back((*it).first);
  }
  return vector.release();
}

// this function will expand a tree structure by
// mapping each ModuleInfo to system and category
void ModuleEnablerDialogTreeModel::appendCategoryChildItems(TreeItem* root,
    const std::auto_ptr<StringModuleVecMap>& categoryModuleVecMap) {
  StringModuleVecMap::iterator mapIt = categoryModuleVecMap->begin();
  while (mapIt != categoryModuleVecMap->end()) {

    std::vector<TreeItem*> systems;

    // create new category item
    ModuleInfo* tmpModule = new ModuleInfo;

    QList<QVariant> tmpList;
    tmpList.append((*mapIt).first); //[0]
    tmpList.append(Qt::Unchecked);
    tmpList.append(tr(""));         //[2]
    TreeItem* categoryItem = new TreeItem(tmpList, TreeItem::Systems,
        *tmpModule, root);
    categoryItem->mModuleInfo.displayedName = (*mapIt).first;
    categoryItem->setHierarchy(0);
    root->appendChild(categoryItem);

    for (pModuleVector::iterator vecIt = (*mapIt).second->begin();
        vecIt != (*mapIt).second->end(); vecIt++) {
      QList<QVariant> childData;                                        //column:
      childData << (*vecIt)->displayedName;                             //[0]
      childData << ((*vecIt)->isEnabled ? Qt::Checked : Qt::Unchecked); //[1]

      if ((*vecIt)->isFailed) {
        childData << (tr("Load failed"));                               //[2]
      } else if ((*vecIt)->isLoaded) {
        childData << (tr("Loaded"));
      } else {
        childData << (tr("Not loaded yet"));
      }

      if (!mRoot_All) {
        (*vecIt)->isEnabled = !(*vecIt)->isFailed && (*vecIt)->isEnabled;
        (*vecIt)->currentlyEnabled = (*vecIt)->isEnabled; // avoid overwrite
      }

      QString systemName = ExtensionRegisterer::extractSystemName(
          (*vecIt)->modName);
      if (systemName.isEmpty()) {
        systemName = QString("MidOSS");
      }

      TreeItem * systemItem = NULL;
      TreeItem* newModuleItem = NULL;

      QList<TreeItem*>::iterator iter = std::find_if(
          categoryItem->childItems().begin(), categoryItem->childItems().end(),
          displayedNameCmp(systemName));
      if (iter != categoryItem->childItems().end()) {
        systemItem = *iter;
      }

      QList<QVariant> tmpList(childData);
      tmpList[0] = systemName;
      tmpList[1] = Qt::Unchecked;
      tmpList[2] = "";

      // if no such system has been found create new TreeItem
      if (systemItem == NULL) {
        ModuleInfo* tmpModule = new ModuleInfo(*(*vecIt));
        tmpModule->currentlyEnabled = (*vecIt)->currentlyEnabled;
        tmpModule->isEnabled = (*vecIt)->isEnabled;

        systemItem = new TreeItem(tmpList, TreeItem::Systems, *tmpModule,
            categoryItem);
        systemItem->mModuleInfo.displayedName = systemName;
        systemItem->setHierarchy(0);

        QString name = ExtensionRegisterer::extractModuleName(
            (*vecIt)->displayedName);
        QList<QVariant> tmpList(childData);
        tmpList[0] = name;

        // and now append new module to the system
        newModuleItem = new TreeItem(tmpList, TreeItem::Systems, *(*vecIt),
            systemItem);

        categoryItem->appendChild(systemItem);
      } else {
        // system already exists
        QList<QVariant> tmpList(childData);
        tmpList[0] = ExtensionRegisterer::extractModuleName(
            (*vecIt)->displayedName);

        // just append new module to the system
        newModuleItem = new TreeItem(tmpList, TreeItem::Systems, *(*vecIt),
            systemItem);
      }
      newModuleItem->setHierarchy(1);
      systemItem->appendChild(newModuleItem);
      updateParents(newModuleItem);
    }

    mapIt++;
  }
}

// returns internal index data for a given role.
// internal index data is a pointer to an instance
// of TreeItem which represents information about
// its ModuleInfo
QVariant ModuleEnablerDialogTreeModel::data(const QModelIndex &index,
    int role) const {
  if (!index.isValid())
    return QVariant();

  TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
  item->mIndex = index;

  if (role == Qt::DisplayRole) {
    if (index.column() != ModuleEnablerDialog_CheckBoxColumn
        || item->hierarchy() == -1)
      return item->data(index.column());
  }

  if (role == Qt::CheckStateRole && item->hierarchy() != -1) {
    if (index.column() == ModuleEnablerDialog_CheckBoxColumn) {

      if (item->hierarchy() == 1) { // the last level in the tree hierarchy
        if (item->mModuleInfo.currentlyEnabled) {
          return Qt::Checked;
        } else {
          return Qt::Unchecked;
        }
      } else {
        // every level other than last level
        return item->data(index.column());
      }
    }
  }

  return QVariant();
}

// sets the role data for the item at <index>
// to <value> and updates affected TreeItems
// and ModuleInfo. returns true if successful
// otherwise returns false
bool ModuleEnablerDialogTreeModel::setData(const QModelIndex & index,
    const QVariant & value, int role) {
  if (role
      == Qt::CheckStateRole&& index.column() == ModuleEnablerDialog_CheckBoxColumn) {
    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    Qt::CheckState checkedState;
    if (value == Qt::Checked) {
      checkedState = Qt::Checked;
    } else if (value == Qt::Unchecked) {
      checkedState = Qt::Unchecked;
    } else {
      checkedState = Qt::PartiallyChecked;
    }

    //set this item currentlyEnabled and check state
    if (item->hierarchy() == 1) { // the last level in the tree hierarchy
      item->mModuleInfo.currentlyEnabled = (
          checkedState == Qt::Checked ? true : false);
      item->setData(ModuleEnablerDialog_CheckBoxColumn, checkedState);
      if (mRoot_Systems != NULL) {
        updateModelItems(item);
      }
    } else { // every level other than last level
      if (checkedState == Qt::Checked || checkedState == Qt::Unchecked) {
        item->setData(index.column(), checkedState);
        // update children
        item->updateChildren(checkedState);
        // and parents
        updateParents(item);
      }
    }

    emit dataChanged(QModelIndex(), QModelIndex());
    return true;
  }

  return false;
}

// updates all affected TreeItems with respect
// to tree from which it was called
void ModuleEnablerDialogTreeModel::updateModelItems(TreeItem* item) {
  if (mClickedItemType == All && mRoot_Systems != NULL) {
    QList<TreeItem*>::iterator itCategories =
        mRoot_Systems->childItems().begin();
    QList<TreeItem*>::iterator itSystem;
    bool found = false;
    QVariant systemValue = Qt::Unchecked;
    while (itCategories != mRoot_Systems->childItems().end() && !found) {
      itSystem = (*itCategories)->childItems().begin();
      while (itSystem != (*itCategories)->childItems().end() && !found) {
        QList<TreeItem*>::iterator itModule = std::find_if(
            (*itSystem)->childItems().begin(), (*itSystem)->childItems().end(),
            displayedNameCmp(item->mModuleInfo.displayedName));
        if (itModule != (*itSystem)->childItems().end()) {
          found = true;

          (*itModule)->setData(ModuleEnablerDialog_CheckBoxColumn,
              item->data(ModuleEnablerDialog_CheckBoxColumn));
          updateParents(*itModule);
        }
        itSystem++;
      }
      itCategories++;
    }
  } else {
    updateParents(item);
  }
}

// updates all affected TreeItems without respect
// to tree from which it was called
void ModuleEnablerDialogTreeModel::updateParents(TreeItem* item) {
  Qt::CheckState value;

  if (item->parent()->hierarchy() == -1)
    return;

  do {
    TreeItem* current = item->parent();
    value = Qt::PartiallyChecked;

    if (current->hasChildChecked()) {
      if (!current->hasChildUnchecked()
          && !current->hasChildPartiallyChecked()) {
        value = Qt::Checked;
      }
    }
    if (current->hasChildUnchecked()) {
      if (!current->hasChildChecked() && !current->hasChildPartiallyChecked()) {
        value = Qt::Unchecked;
      }
    }

    current->setData(ModuleEnablerDialog_CheckBoxColumn, value);
    item = current;
  } while (item->parent()->hierarchy() != -1);

}

// maps proxy index to source index
// and returns its data
QVariant ModuleEnablerDialogTreeSortModel::data(const QModelIndex& index, int role) const {
  if (!index.isValid())
      return QVariant();
  return sourceModel()->data(mapToSource(index), role);
}

// calls source model setData
// and updates proxy model
bool ModuleEnablerDialogTreeSortModel::setData(const QModelIndex & index, const QVariant & value, int role){
  sourceModel()->setData(mapToSource(index), value, role);
  emit dataChanged(QModelIndex(),QModelIndex());
  return true;
}

} /* namespace tt_utils */
