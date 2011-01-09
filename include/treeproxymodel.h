#ifndef TREEPROXYMODEL_H
#define TREEPROXYMODEL_H

#include <QAbstractProxyModel>
#include <QList>

/** proxy model for sqlrelationmodel into a tree,
    one top level node per day.
*/
class TreeProxyModel : public QAbstractProxyModel
{
    Q_OBJECT
public:
    TreeProxyModel(QAbstractItemModel *sourceModel, QObject *parent = 0);

    int columnCount(const QModelIndex &parent) const;
    int rowCount(const QModelIndex &parent) const;
    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const;
    QModelIndex mapToSource(const QModelIndex &proxyIndex) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index = QModelIndex()) const;
    bool hasChildren(const QModelIndex &parent = QModelIndex()) const;

signals:

public slots:

private:
    int sourceDateRow(int row) const;
    mutable QList<int> sourceRowCache;
};

#endif // TREEPROXYMODEL_H
