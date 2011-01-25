#ifndef ADDUMSATZDIALOG_H
#define ADDUMSATZDIALOG_H

#include <QDialog>

class QSqlRelationalTableModel;
class QGroupBox;
class QDialogButtonBox;
class QDateEdit;
class QLineEdit;
class QComboBox;
class QTextEdit;
class QDate;

class AddUmsatzDialog : public QDialog
{
    Q_OBJECT
public:
    AddUmsatzDialog(QSqlRelationalTableModel *housekeepingbook, QWidget *parent = 0);
    virtual ~AddUmsatzDialog();

private slots:
    void revert();
    void submit();

private:

    QGroupBox* createInputWidgets();
    QDialogButtonBox* createButtons();

    void addUmsatz();

    QDateEdit *dateEdit;
    QLineEdit *betragEdit;
    QComboBox *waehrungEdit;
    QComboBox *kategorieEdit;
    QComboBox *zahlartEdit;
    QTextEdit *bemerkungEdit;

    QSqlRelationalTableModel *model;
};

#endif // ADDUMSATZDIALOG_H
