#ifndef VIEWPROXYMODEL_H
#define VIEWPROXYMODEL_H

#include <QAbstractProxyModel>

/** proxy model for my sqlrelationmodel for a chart view
  */
class ViewProxyModel : public QAbstractProxyModel
{
    Q_OBJECT
public:
    ViewProxyModel(QAbstractItemModel *sourceModel, QObject *parent = 0);

    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const;
    QModelIndex mapToSource(const QModelIndex &proxyIndex) const;

signals:

public slots:

private:

};

#endif // VIEWPROXYMODEL_H
