#include "treeproxymodel.h"

TreeProxyModel::TreeProxyModel(QAbstractItemModel* sourceModel, QObject *parent) :
    QAbstractProxyModel(parent)
{
    setSourceModel(sourceModel);
}

QModelIndex TreeProxyModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    return QModelIndex();
}

QModelIndex TreeProxyModel::mapToSource(const QModelIndex &proxyIndex) const
{
    return QModelIndex();
}
