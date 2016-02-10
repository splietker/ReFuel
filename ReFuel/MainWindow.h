//
// Created by msp on 2/9/16.
//

#ifndef REFUEL_MAINWINDOW_H
#define REFUEL_MAINWINDOW_H


#include <QDialog>
#include <QSystemTrayIcon>

class MainWindow : public QDialog {
Q_OBJECT

public:
    MainWindow();

private:
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    QAction *openAction;
    QAction *quitAction;

    void createTrayIconMenu();

    void createTrayIcon();
};


#endif //REFUEL_MAINWINDOW_H
