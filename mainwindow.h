#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "valve.h"
#include "hd44780.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_manualButton_clicked();

    void on_programButton_clicked();

    void on_statusButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
