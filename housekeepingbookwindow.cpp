#include "housekeepingbookwindow.h"

#include <QtGui>
#include <QtSql>

HousekeepingBookWindow::HousekeepingBookWindow(QWidget *parent) :
    QMainWindow(parent)
{
    model = new QSqlRelationalTableModel(this);
    model->setTable("umsatz");
    model->setRelation(3, QSqlRelation("waehrung", "id", "zeichen"));
    model->setRelation(4, QSqlRelation("kategorie", "id", "kurzinfo"));
    model->setRelation(5, QSqlRelation("zahlart", "id", "kurzinfo"));
    model->select();

    QGroupBox* umsatz = createUmsatzBox();
    QGroupBox* show = createShowBox();

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(umsatz, 0, 0);
    layout->addWidget(show, 0, 1);

    QWidget* central = new QWidget;
    central->setLayout(layout);
    setCentralWidget(central);

    resize(400, 400);
    setWindowTitle("Housekeeping Book");
}

QGroupBox* HousekeepingBookWindow::createUmsatzBox()
{
    QGroupBox* box = new QGroupBox("Umsatz");

    umsatzView = new QTreeView;
    umsatzView->setModel(model);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(umsatzView, 0, 0);
    box->setLayout(layout);

    return box;
}

QGroupBox* HousekeepingBookWindow::createShowBox()
{
    QGroupBox* box = new QGroupBox("Show");

    return box;
}
