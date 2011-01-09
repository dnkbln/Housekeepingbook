#include "housekeepingbookwindow.h"
#include "addumsatzdialog.h"
#include "pieview.h"
#include "treeproxymodel.h"

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
    model->setSort(1, Qt::AscendingOrder);

    QGroupBox* umsatz = createUmsatzBox();
    pieChart = new PieView;
    pieChart->setModel(model);
    QSplitter *splitter = new QSplitter;

    splitter->addWidget(umsatz);
    splitter->addWidget(pieChart);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);

    setCentralWidget(splitter);
    createMenuBar();

    resize(400, 400);
    setWindowTitle("Housekeeping Book");
}

QGroupBox* HousekeepingBookWindow::createUmsatzBox()
{
    QGroupBox* box = new QGroupBox("Umsatz");

    umsatzView = new QTreeView;

    treeModel = new TreeProxyModel(model, this);
    umsatzView->setModel(treeModel);

    addUmsatzAction = new QAction("Füge Umsatz hinzu", this);
    umsatzView->addAction(addUmsatzAction);
    connect(addUmsatzAction, SIGNAL(triggered(bool)), this, SLOT(addUmsatz()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(umsatzView);
    box->setLayout(layout);

    return box;
}

QGroupBox* HousekeepingBookWindow::createShowBox()
{
    QGroupBox* box = new QGroupBox("Show");

    return box;
}

void HousekeepingBookWindow::createMenuBar()
{
    QAction *addAction = new QAction("Umsatz hinzufügen", this);
    QAction *helpAction = new QAction("Hilfe", this);
    QAction *aboutAction = new QAction("Über HousekeeingBook", this);

    QMenu *dataMenu = menuBar()->addMenu("Daten");
    dataMenu->addAction(addAction);
    QMenu *helpMenu = menuBar()->addMenu("Help");
    helpMenu->addAction(helpAction);
    helpMenu->addAction(aboutAction);

    connect(addAction, SIGNAL(triggered(bool)), this, SLOT(addUmsatz()));
}

void HousekeepingBookWindow::addUmsatz()
{
    AddUmsatzDialog *addDialog = new AddUmsatzDialog(model, this);
    int accepted = addDialog->exec();

    if (accepted == 1) {

    }
}
