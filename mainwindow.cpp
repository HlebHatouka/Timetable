#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::show_timetable(vector<Flight>::const_iterator first, vector<Flight>::const_iterator last)
{
    ui->table_text->clear();

    for (auto i = first; i != last; ++i)
        ui->table_text->append(QString::number(i->number)+ "\t"
                               + QString::fromStdString(i->destination) + "\t"
                               + QString::number(i->start.hour)+":" + QString::number(i->start.min) + "\t"
                               + QString::number(i->finish.hour)+":" + QString::number(i->finish.min));
}

void MainWindow::on_readButton_clicked()
{
     path = ui->path_line->text().toUtf8().constData();
     read_timetable(path, timetable);
}

void MainWindow::on_showButton_clicked()
{
    show_timetable(timetable.cbegin(), timetable.cend());
}

void MainWindow::on_createButton_clicked()
{
     path = ui->path_line->text().toUtf8().constData();
     write_timetable(path, timetable);
}

void MainWindow::on_addButton_clicked()
{
    Flight temp( ui->number_line->text().toUShort(),
                 ui->destination_line->text().toStdString(),
                 ui->start_hour_line->text().toUShort(),
                 ui->start_min_line->text().toUShort(),
                 ui->finish_hour_line->text().toUShort(),
                 ui->finish_min_line->text().toUShort());
    add_flight(timetable, temp);
}

void MainWindow::on_saveButton_clicked()
{
    write_timetable(path, timetable);
}

void MainWindow::on_cleanButton_clicked()
{
    ui->table_text->clear();
    timetable.clear();
}

void MainWindow::on_selectButton_clicked()
{
    vector<Flight> temp = timetable;
    Flight::Time key(ui->sel_hour_line->text().toUShort(), ui->sel_min_line->text().toUShort());
    selectionSort(temp);
    auto last = std::find_if(temp.cbegin(), temp.cend(), [&key](Flight comp){
        return comp.finish > key;
    });
    show_timetable(temp.cbegin(), last);

}

void MainWindow::on_sortButton_clicked()
{
    quickSort(timetable, NULL, timetable.size()-1);
    show_timetable(timetable.cbegin(), timetable.cend());
}

MainWindow::~MainWindow()
{
    delete ui;
}
