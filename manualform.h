#ifndef MANUALFORM_H
#define MANUALFORM_H

#include <QWidget>
#include "valve.h"

namespace Ui {
class ManualForm;
}

class ManualForm : public QWidget
{
    Q_OBJECT

public:
    explicit ManualForm(QWidget *parent = 0);
    ~ManualForm();

private slots:
    void on_okButton_clicked();

    void on_plus1Button_clicked();

    void on_minus1Button_clicked();

    void on_plus10Button_clicked();

    void on_minus10Button_clicked();

private:
    Ui::ManualForm *ui;
};

#endif // MANUALFORM_H
