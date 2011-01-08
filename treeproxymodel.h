#ifndef TREEPROXYMODEL_H
#define TREEPROXYMODEL_H

#include <QAbstractProxyModel>

/** proxy model for sqlrelationmodel into a tree,
    one top level node per day.
*/
class TreeProxyModel : public QAbstractProxyModel
{
    Q_OBJECT
public:
    TreeProxyModel(QAbstractItemModel *sourceModel, QObject *parent = 0);

    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const;
    QModelIndex mapToSource(const QModelIndex &proxyIndex) const;

signals:

public slots:

private:

};

#endif // TREEPROXYMODEL_H
