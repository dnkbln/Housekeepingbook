#include "addumsatzdialog.h"

#include <QtGui>
#include <QtSql>
#include <QtDebug>


AddUmsatzDialog::AddUmsatzDialog(QSqlRelationalTableModel *housekeepingbook, QWidget *parent) :
    QDialog(parent)
{
    model = housekeepingbook;

    QGroupBox *inputBox = createInputWidgets();
    QDialogButtonBox *buttonBox = createButtons();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(inputBox);
    layout->addWidget(buttonBox);
    setLayout(layout);

    setWindowTitle(tr("Umsatz hinzufügen"));
}

AddUmsatzDialog::~AddUmsatzDialog()
{
}

void AddUmsatzDialog::submit()
{
    if (!betragEdit->hasAcceptableInput()) {
        QString message(tr("Geben Sie bitte einen sinnvollen Betrag ein."));
        QMessageBox::information(this, tr("Umsatz hinzufügen"), message);
    }
    else {
        addUmsatz();
        accept();
    }
}

void AddUmsatzDialog::revert()
{
    // trage die default-Werte wieder ein
    betragEdit->clear();
    dateEdit->setDate(QDate::currentDate());
}

QGroupBox *AddUmsatzDialog::createInputWidgets()
{
    QGroupBox *addGroup = new QGroupBox(tr("Umsatz hinzufügen"));

    QLabel *datumLabel = new QLabel(tr("Datum"));
    QLabel *betragLabel = new QLabel(tr("Betrag"));
    QLabel *kategorieLabel = new QLabel(tr("Kategorie"));
    QLabel *zahlartLabel = new QLabel(tr("Zahlart"));

    dateEdit = new QDateEdit;
    dateEdit->setDate(QDate::currentDate());
    betragEdit = new QLineEdit;
    betragEdit->setValidator(new QDoubleValidator(0.0, 100000.0, 2, betragEdit));
    waehrungEdit = new QComboBox;
    waehrungEdit->setModel(model->relationModel(3));
    waehrungEdit->setModelColumn(2);
    kategorieEdit = new QComboBox;
    kategorieEdit->setModel(model->relationModel(4));
    kategorieEdit->setModelColumn(2);
    zahlartEdit = new QComboBox;
    zahlartEdit->setModel(model->relationModel(5));
    zahlartEdit->setModelColumn(2);
    bemerkungEdit = new QTextEdit;

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(datumLabel, 0, 0);
    layout->addWidget(dateEdit, 0, 1, 1, 2);
    layout->addWidget(betragLabel, 1, 0);
    layout->addWidget(betragEdit, 1, 1);
    layout->addWidget(waehrungEdit, 1, 2);
    layout->addWidget(kategorieLabel, 2, 0);
    layout->addWidget(kategorieEdit, 2, 1, 1, 2);
    layout->addWidget(zahlartLabel, 3, 0);
    layout->addWidget(zahlartEdit, 3, 1, 1, 2);
    layout->addWidget(bemerkungEdit, 4, 0, 1, 3);

    addGroup->setLayout(layout);

    return addGroup;
}

QDialogButtonBox *AddUmsatzDialog::createButtons()
{
    QPushButton *closeButton = new QPushButton(tr("&Schliessen"));
    QPushButton *revertButton = new QPushButton(tr("&Abbrechen"));
    QPushButton *submitButton = new QPushButton(tr("&Übernehmen"));

    closeButton->setDefault(true);

    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(revertButton, SIGNAL(clicked()), this, SLOT(revert()));
    connect(submitButton, SIGNAL(clicked()), this, SLOT(submit()));

    QDialogButtonBox *buttonBox = new QDialogButtonBox;
    buttonBox->addButton(submitButton, QDialogButtonBox::ResetRole);
    buttonBox->addButton(revertButton, QDialogButtonBox::ResetRole);
    buttonBox->addButton(closeButton, QDialogButtonBox::RejectRole);

    return buttonBox;
}

void AddUmsatzDialog::addUmsatz()
{
    QSqlRecord record;

    QSqlField datum("datum", QVariant::String);
    QSqlField betrag("betrag", QVariant::Double);
    QSqlField waehrung("waehrungid", QVariant::Int);
    QSqlField kategorie("kategorieid", QVariant::Int);
    QSqlField zahlart("zahlartid", QVariant::Int);
    QSqlField bemerkung("bemerkung", QVariant::String);

    datum.setValue(QVariant(dateEdit->date().toString()));
    betrag.setValue(QVariant(betragEdit->text().toDouble()));
    waehrung.setValue(QVariant(waehrungEdit->currentIndex()+1));
    kategorie.setValue(QVariant(kategorieEdit->currentIndex()+1));
    zahlart.setValue(QVariant(zahlartEdit->currentIndex()+1));
    bemerkung.setValue(QVariant(bemerkungEdit->toPlainText()));

    qDebug() << "Date: " << dateEdit->date().toString() << " Betrag: "
             << betragEdit->text().toDouble() << " Währung: "
             << waehrungEdit->currentIndex()+1 << " Kategorie: "
             << kategorieEdit->currentIndex()+1 << " Zahlart: "
             << zahlartEdit->currentIndex()+1 << " Bemerkung: "
             << bemerkungEdit->toPlainText();

    record.append(datum);
    record.append(betrag);
    record.append(waehrung);
    record.append(kategorie);
    record.append(zahlart);
    record.append(bemerkung);

    model->insertRecord(-1, record);
}
