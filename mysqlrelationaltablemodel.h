#ifndef MYSQLRELATIONALTABLEMODEL_H
#define MYSQLRELATIONALTABLEMODEL_H

#include <QSqlRelationalTableModel>

/** \short SqlRelationalTableModel for table umsatz.

    \brief This TableModel change the columntype from string to date for
    the column 1. Only the function data and setDate are overwrite.

*/
class MySqlRelationalTableModel : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    MySqlRelationalTableModel(QObject *parent = 0);
    QVariant data(const QModelIndex &item, int role=Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant& value, int role=Qt::EditRole);
};

#endif // MYSQLRELATIONALTABLEMODEL_H
