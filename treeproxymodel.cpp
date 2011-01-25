#include "treeproxymodel.h"

#include <QDate>

TreeProxyModel::TreeProxyModel(QAbstractItemModel* sourceModel, QObject *parent) :
    QAbstractProxyModel(parent)
{
    setSourceModel(sourceModel);
}

void TreeProxyModel::setSourceModel(QAbstractItemModel* model)
{
    if (sourceModel()) {
        disconnect(sourceModel(), SIGNAL(modelReset()), this, SLOT(sourceReset()));
        disconnect(sourceModel(), SIGNAL(rowsInserted(QModelIndex, int, int)),
                   this, SLOT(sourceRowsInserted(QModelIndex,int,int)));
        disconnect(sourceModel(), SIGNAL(rowsRemoved(QModelIndex, int, int)),
                   this, SLOT(sourceRowsRemoved(QModelIndex,int,int)));
    }

    QAbstractProxyModel::setSourceModel(model);

    if (model) {
        connect(sourceModel(), SIGNAL(modelReset()), this, SLOT(sourceReset()));
        connect(sourceModel(), SIGNAL(rowsInserted(QModelIndex, int, int)),
                this, SLOT(sourceRowsInserted(QModelIndex,int,int)));
        connect(sourceModel(), SIGNAL(rowsRemoved(QModelIndex, int, int)),
                this, SLOT(sourceRowsRemoved(QModelIndex,int,int)));
    }
    reset();
}

QVariant TreeProxyModel::data(const QModelIndex &proxyIndex, int role) const
{
    if ((role == Qt::EditRole || role == Qt::DisplayRole)) {
        int start = proxyIndex.internalId();
        if (start == 0) {
            int offset = sourceDateRow(proxyIndex.row());
            if (proxyIndex.column() == 1) {

                QModelIndex idx = sourceModel()->index(offset, 1);
                QDate date = idx.data().toDate();
                return date.toString();
            }
            if (proxyIndex.column() == 2) {

                double value = 0.0;
                if (proxyIndex.isValid()) {
                    int startIdx = sourceDateRow(proxyIndex.row());
                    int endIdx = sourceDateRow(proxyIndex.row()+1);
                    for (int i=startIdx; i<endIdx; ++i) {
                        value += sourceModel()->index(i, 2).data().toDouble();
                    }
                }
                return " Summe: " + QString::number(value);
            }
        }
    }

    return QAbstractProxyModel::data(proxyIndex, role);
}

int TreeProxyModel::columnCount(const QModelIndex &parent) const
{
    return sourceModel()->columnCount(mapToSource(parent));
}

int TreeProxyModel::rowCount(const QModelIndex &parent) const
{
    if( parent.internalId() != 0 || parent.column() > 0 || !sourceModel())
        return 0;

    // Liefert die Anzahl der rows für die Tage
    if (!parent.isValid()) {
        if (!sourceRowCache.isEmpty())
            return sourceRowCache.count();
        QDate currentDate;
        int rows = 0;
        int sourceRows = sourceModel()->rowCount();

        for (int i = 0; i < sourceRows; ++i) {
            /*
            The new model change the type automatic.

            QString rowDateString = sourceModel()->index(i, 1).data().toString();
            QDate rowDate = QDate::fromString(rowDateString);
            */
            QDate rowDate = sourceModel()->index(i, 1).data().toDate();
            if (rowDate != currentDate) {
                sourceRowCache.append(i);
                currentDate = rowDate;
                ++rows;
            }
        }
        return rows;
    }

    // Liefert die Anzahl der rows für einen Tag
    int start = sourceDateRow(parent.row());
    int end = sourceDateRow(parent.row()+1);
    return (end-start);
}

/** Liefert zu einem Datum die Start-Row im Source-Modell. Damit nicht immer
    neu die Startposition bestimmt werden muss, werden sie im sourceRowCache
    abgelegt.
*/
int TreeProxyModel::sourceDateRow(int row) const
{
    if (row <= 0)
        return 0;
    if (sourceRowCache.isEmpty())
        return rowCount(QModelIndex());

    if (row >= sourceRowCache.count()) {
        if (!sourceModel())
            return 0;
        return sourceModel()->rowCount();
    }
    return sourceRowCache.at(row);
}

/** Liefert den ModelIndex des SourceModels zum ModelIndex des ProxyModels
  */
QModelIndex TreeProxyModel::mapToSource(const QModelIndex &proxyIndex) const
{
    int offset = proxyIndex.internalId();
    if (offset == 0)
        return QModelIndex();

    int startRow = sourceDateRow(offset-1);
    return sourceModel()->index(startRow+proxyIndex.row(), proxyIndex.column());
}

QModelIndex TreeProxyModel::index(int row, int column, const QModelIndex &parent) const
{
    if (row < 0 || column < 0 || column >= columnCount(parent) || parent.column() > 0)
        return QModelIndex();
    if (!parent.isValid())
        return createIndex(row, column, 0);
    return createIndex(row, column, parent.row()+1);
}

QModelIndex TreeProxyModel::parent(const QModelIndex &index) const
{
    int offset = index.internalId();
    if (offset == 0 || !index.isValid())
        return QModelIndex();
    return createIndex(offset-1, 0, 0);
}

bool TreeProxyModel::hasChildren(const QModelIndex &parent) const
{
    QModelIndex grandparent = parent.parent();
    if (!grandparent.isValid())
        return true;
    return false;
}

QModelIndex TreeProxyModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    if (!sourceIndex.isValid())
        return QModelIndex();
    if (sourceRowCache.isEmpty())
        rowCount(QModelIndex());
    QList<int>::iterator it;
    it = qLowerBound(sourceRowCache.begin(), sourceRowCache.end(), sourceIndex.row());
    if (*it != sourceIndex.row())
        --it;
    int dateRow = qMax(0, it - sourceRowCache.begin());
    int row = sourceIndex.row() - sourceRowCache.at(dateRow);
    return createIndex(row, sourceIndex.column(), dateRow + 1);
}

void TreeProxyModel::sourceReset()
{
    sourceRowCache.clear();
    reset();
}

void TreeProxyModel::sourceRowsInserted(const QModelIndex &parent, int start, int end)
{
    sourceRowCache.clear();
    reset();
}

void TreeProxyModel::sourceRowsRemoved(const QModelIndex &parent, int start, int end)
{
    sourceRowCache.clear();
    reset();
}
