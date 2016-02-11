#include <QApplication>
#include <QMessageBox>
#include "MainWindow.h"

using namespace std;

int main(int argc, char *argv[]) {
    //Q_INIT_RESOURCE(refuel);

    QApplication app(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("ReFuel"),
                              QObject::tr("I couldn't detect any system tray on this system."));
        return 1;
    }
    QApplication::setQuitOnLastWindowClosed(false);

    MainWindow window;
    return app.exec();
}