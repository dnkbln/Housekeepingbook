#include "mysqlrelationaltablemodel.h"

#include <QDate>

MySqlRelationalTableModel::MySqlRelationalTableModel(QObject *parent) :
    QSqlRelationalTableModel(parent)
{
}

QVariant MySqlRelationalTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || (role != Qt::DisplayRole && role != Qt::EditRole))
        return QVariant();

    if (index.column() == 1) {
        QVariant varDate = QSqlRelationalTableModel::data(index, role);
        QDate date = QDate::fromString(varDate.toString());
        return QVariant(date);
    }

    return QSqlRelationalTableModel::data(index, role);
}

bool MySqlRelationalTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.column() == 1) {
        QDate date = value.toDate();
        QString strDate = date.toString();
        QVariant varDate(strDate);

        return QSqlRelationalTableModel::setData(index, varDate, role);
    }

    return QSqlRelationalTableModel::setData(index, value, role);
}
