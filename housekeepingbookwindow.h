#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QGroupBox;
class QTreeView;
class QSqlRelationalTableModel;

class HousekeepingBookWindow : public QMainWindow
{
    Q_OBJECT

public:
    HousekeepingBookWindow(QWidget *parent = 0);

private slots:

//    void addUmsatz();

private:

    QGroupBox* createUmsatzBox();
    QGroupBox* createShowBox();

    QTreeView *umsatzView;
    QSqlRelationalTableModel *model;
};

#endif // MAINWINDOW_H
