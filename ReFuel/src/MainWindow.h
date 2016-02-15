/*
 * Copyright 2016 Malte Splietker
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 *         limitations under the License.
 */

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
