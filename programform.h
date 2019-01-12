#ifndef PROGRAMFORM_H
#define PROGRAMFORM_H

#include <QWidget>
#include "valve.h"

namespace Ui {
class ProgramForm;
}

class ProgramForm : public QWidget
{
    Q_OBJECT

public:
    explicit ProgramForm(QWidget *parent = 0);
    ~ProgramForm();

private slots:
    void on_saveButton_clicked();

    void on_programButton_1_clicked();

    void on_programButton_2_clicked();

    void on_programButton_3_clicked();

    void on_programButton_4_clicked();

    void on_v1Button_clicked();

    void on_v2Button_clicked();

    void on_v3Button_clicked();

    void on_v4Button_clicked();

    void on_v5Button_clicked();

    void on_v6Button_clicked();

    void on_v7Button_clicked();

    void on_v8Button_clicked();

    void on_hourPlus1Button_clicked();

    void on_hourMinus1Button_clicked();

    void on_hourPlus10Button_clicked();

    void on_hourMinus10Button_clicked();

    void on_minPlus1Button_clicked();

    void on_minMinus1Button_clicked();

    void on_minPlus10Button_clicked();

    void on_minMinus10Button_clicked();

    void on_workTimePlus1Button_clicked();

    void on_workTimeMinus1Button_clicked();

    void on_workTimePlus10Button_clicked();

    void on_workTimeMinus10Button_clicked();

private:
    Ui::ProgramForm *ui;

    unsigned int valveNumber{0};
    unsigned int programNumber{0};

    Program getProgramFromScreen(void) const;
    void setProgramToScreen(const Program &program);

};

#endif // PROGRAMFORM_H
