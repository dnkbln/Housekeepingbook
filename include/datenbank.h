#ifndef DATENBANK_H
#define DATENBANK_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

/** Create database connection and check the exists the tables

    Tables: umsatz, kategorien, waehrung, zahlart

    create table waehrung ( id INTEGER primary key autoincrement, beschreibung text, zeichen text )

    create table kategorie ( id INTEGER primary key autoincrement, info text, kurzinfo text )

    create table zahlart ( id INTEGER primary key autoincrement, info text, kutzinfo text )

    create table umsatz ( id INTEGER primary key autoincrement, datum text, betrag real,
                          waehrungid INTEGER, kategorieid INTEGER, zahlartid INTEGER,
                          bemerkung TEXT, FOREIGN KEY(waehrungid) REFERENCES waehrung(id),
                          FOREIGN KEY(kategorieid) REFERENCES kategorie(id) )

  */
static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("housekeepingbook.db");

    if (db.open()) {
        // table exists ?
        if (db.tables().indexOf("waehrung") == -1) {
            QSqlQuery query(db);
            query.exec("create table waehrung (id INTEGER primary key autoincrement,"
                       "beschreibung TEXT, zeichen TEXT)");
            query.exec("insert into waehrung (beschreibung, zeichen) VALUES ('Euro','€')");
            query.exec("insert into waehrung (beschreibung, zeichen) VALUES ('Dolar','$')");
        }
        if (db.tables().indexOf("kategorie") == -1) {
            QSqlQuery query(db);
            query.exec("create table kategorie (id INTEGER primary key autoincrement,"
                       "beschreibung TEXT, kurzinfo TEXT)");
            query.exec("insert into kategorie (beschreibung, kurzinfo) VALUES ('Lebensmittel','Lebensmittel')");
            query.exec("insert into kategorie (beschreibung, kurzinfo) VALUES ('Kino','Kino')");
            query.exec("insert into kategorie (beschreibung, kurzinfo) VALUES ('Mittagessen','Mittagessen')");
            query.exec("insert into kategorie (beschreibung, kurzinfo) VALUES ('Bier trinken','Bier')");
        }
        if (db.tables().indexOf("zahlart") == -1) {
            QSqlQuery query(db);
            query.exec("create table zahlart (id INTEGER primary key autoincrement,"
                       "beschreibung TEXT, kurzinfo TEXT)");
            query.exec("insert into zahlart (beschreibung, kurzinfo) VALUES ('Bargeld','bar')");
            query.exec("insert into zahlart (beschreibung, kurzinfo) VALUES ('EC-Card','EC')");
            query.exec("insert into zahlart (beschreibung, kurzinfo) VALUES ('VISA-Card','Visa')");
        }
        if (db.tables().indexOf("umsatz") == -1) {
            QSqlQuery query(db);
            query.exec("create table umsatz (id INTEGER primary key autoincrement,"
                       "datum TEXT, betrag REAL, waehrungid INTEGER, kategorieid INTEGER,"
                       "zahlartid INTEGER, bemerkung TEXT, FOREIGN KEY(waehrungid) REFERENCES waehrung(id),"
                       "FOREIGN KEY(kategorieid) REFERENCES kategorie(id),"
                       "FOREIGN KEY(zahlartid) REFERENCES zahlart(id))");
        }
    } else {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection.\n"
                     "This example needs SQLite support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }

    return true;
}

#endif // DATENBANK_H
