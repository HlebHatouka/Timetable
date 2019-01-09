#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "flight.h"
#include <QMainWindow>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    string path;
    vector<Flight> timetable;
    void show_timetable(vector<Flight>::const_iterator first, const vector<Flight>::const_iterator last);

private slots:
    void on_showButton_clicked();

    void on_createButton_clicked();

    void on_addButton_clicked();

    void on_saveButton_clicked();

    void on_cleanButton_clicked();

    void on_selectButton_clicked();

    void on_readButton_clicked();

    void on_sortButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
