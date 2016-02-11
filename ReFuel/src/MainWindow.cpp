//
// Created by msp on 2/9/16.
//

#include "MainWindow.h"
#include <QApplication>
#include <QMenu>

MainWindow::MainWindow() {

    createTrayIconMenu();
    createTrayIcon();
    trayIcon->show();

    setWindowTitle(tr("ReFuel"));
    resize(400, 300);
}

void MainWindow::createTrayIconMenu() {
    openAction = new QAction(tr("&Open"), this);
    connect(openAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(openAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
}

void MainWindow::createTrayIcon() {
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);

    // When left-clicking the icon, toggle visibility of the window.
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wincompatible-pointer-types"
    connect(trayIcon, &QSystemTrayIcon::activated, this,
            [=](QSystemTrayIcon::ActivationReason activationReason) {
                if (activationReason == QSystemTrayIcon::Context) {
                    return;
                }
                if (isVisible()) {
                    hide();
                } else {
                    showNormal();
                }
            });
#pragma clang diagnostic pop

    QIcon icon = QIcon(":/resources/icon.png");
    trayIcon->setIcon(icon);
    setWindowIcon(icon);

    trayIcon->setToolTip(tr("ReFuel"));
}
