#include <QtGui/QApplication>

#include "housekeepingbookwindow.h"
#include "datenbank.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    if (!createConnection())
        return 1;

    HousekeepingBookWindow window;
    window.show();

    return app.exec();
}
