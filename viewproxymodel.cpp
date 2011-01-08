#include "viewproxymodel.h"

ViewProxyModel::ViewProxyModel(QAbstractItemModel* sourceModel, QObject *parent) :
    QAbstractProxyModel(parent)
{
    setSourceModel(sourceModel);
}

QModelIndex ViewProxyModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    return QModelIndex();
}

QModelIndex ViewProxyModel::mapToSource(const QModelIndex &proxyIndex) const
{
    return QModelIndex();
}
