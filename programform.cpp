#include "programform.h"
#include "ui_programform.h"

ProgramForm::ProgramForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgramForm)
{
    ui->setupUi(this);
    setProgramToScreen(allValves.at(valveNumber)->getProgram(programNumber));
}

ProgramForm::~ProgramForm()
{
    delete ui;
}

void ProgramForm::on_saveButton_clicked()
{
    allValves.at(valveNumber)->setProgram(programNumber, getProgramFromScreen());

    /*
     * Program save logic
     */
    for(unsigned int i=0; i<allValves.size(); i++)
        for(unsigned int j=0; j<allValves.at(i)->getProgramsCount(); j++){
            allValves.at(i)->saveProgramToFile(j);
        }
}

void ProgramForm::on_programButton_1_clicked()
{
    allValves.at(valveNumber)->setProgram(programNumber, getProgramFromScreen());
    programNumber=0;
    setProgramToScreen(allValves.at(valveNumber)->getProgram(programNumber));
}

void ProgramForm::on_programButton_2_clicked()
{
    allValves.at(valveNumber)->setProgram(programNumber, getProgramFromScreen());
    programNumber=1;
    setProgramToScreen(allValves.at(valveNumber)->getProgram(programNumber));
}

void ProgramForm::on_programButton_3_clicked()
{
    allValves.at(valveNumber)->setProgram(programNumber, getProgramFromScreen());
    programNumber=2;
    setProgramToScreen(allValves.at(valveNumber)->getProgram(programNumber));
}

void ProgramForm::on_programButton_4_clicked()
{
    allValves.at(valveNumber)->setProgram(programNumber, getProgramFromScreen());
    programNumber=3;
    setProgramToScreen(allValves.at(valveNumber)->getProgram(programNumber));
}

void ProgramForm::on_v1Button_clicked()
{
    allValves.at(valveNumber)->setProgram(programNumber, getProgramFromScreen());
    valveNumber=0;
    setProgramToScreen(allValves.at(valveNumber)->getProgram(programNumber));
}

void ProgramForm::on_v2Button_clicked()
{
    allValves.at(valveNumber)->setProgram(programNumber, getProgramFromScreen());
    valveNumber=1;
    setProgramToScreen(allValves.at(valveNumber)->getProgram(programNumber));
}

void ProgramForm::on_v3Button_clicked()
{
    allValves.at(valveNumber)->setProgram(programNumber, getProgramFromScreen());
    valveNumber=2;
    setProgramToScreen(allValves.at(valveNumber)->getProgram(programNumber));
}

void ProgramForm::on_v4Button_clicked()
{
    allValves.at(valveNumber)->setProgram(programNumber, getProgramFromScreen());
    valveNumber=3;
    setProgramToScreen(allValves.at(valveNumber)->getProgram(programNumber));
}

void ProgramForm::on_v5Button_clicked()
{
    allValves.at(valveNumber)->setProgram(programNumber, getProgramFromScreen());
    valveNumber=4;
    setProgramToScreen(allValves.at(valveNumber)->getProgram(programNumber));
}

void ProgramForm::on_v6Button_clicked()
{
    allValves.at(valveNumber)->setProgram(programNumber, getProgramFromScreen());
    valveNumber=5;
    setProgramToScreen(allValves.at(valveNumber)->getProgram(programNumber));
}

void ProgramForm::on_v7Button_clicked()
{
    allValves.at(valveNumber)->setProgram(programNumber, getProgramFromScreen());
    valveNumber=6;
    setProgramToScreen(allValves.at(valveNumber)->getProgram(programNumber));
}

void ProgramForm::on_v8Button_clicked()
{
    allValves.at(valveNumber)->setProgram(programNumber, getProgramFromScreen());
    valveNumber=7;
    setProgramToScreen(allValves.at(valveNumber)->getProgram(programNumber));
}

Program ProgramForm::getProgramFromScreen() const {
    Program program;

    program.setWeekDayFlag(Program::Monday,   ui->checkBox_1->isChecked());
    program.setWeekDayFlag(Program::Tuesday,  ui->checkBox_2->isChecked());
    program.setWeekDayFlag(Program::Wednesday,ui->checkBox_3->isChecked());
    program.setWeekDayFlag(Program::Thursday, ui->checkBox_4->isChecked());
    program.setWeekDayFlag(Program::Friday,   ui->checkBox_5->isChecked());
    program.setWeekDayFlag(Program::Saturday, ui->checkBox_6->isChecked());
    program.setWeekDayFlag(Program::Sunday,   ui->checkBox_7->isChecked());

    program.setHour(ui->hourLCDNumber->value());
    program.setMinute(ui->minLCDNumber->value());
    program.setWorkTime(ui->workMinsLCDNumber->value());

    return program;

}

void ProgramForm::setProgramToScreen(const Program &program){

    ui->checkBox_1->setChecked(program.getWeekDayFlag(Program::Monday));
    ui->checkBox_2->setChecked(program.getWeekDayFlag(Program::Tuesday));
    ui->checkBox_3->setChecked(program.getWeekDayFlag(Program::Wednesday));
    ui->checkBox_4->setChecked(program.getWeekDayFlag(Program::Thursday));
    ui->checkBox_5->setChecked(program.getWeekDayFlag(Program::Friday));
    ui->checkBox_6->setChecked(program.getWeekDayFlag(Program::Saturday));
    ui->checkBox_7->setChecked(program.getWeekDayFlag(Program::Sunday));

    ui->hourLCDNumber->display(static_cast<int>(program.getHour()));
    ui->minLCDNumber->display(static_cast<int>(program.getMinute()));
    ui->workMinsLCDNumber->display(static_cast<int>(program.getWorkTime()));

}


void ProgramForm::on_hourPlus1Button_clicked()
{
    if(ui->hourLCDNumber->value() <=22)
        ui->hourLCDNumber->display(ui->hourLCDNumber->value() + 1);
}

void ProgramForm::on_hourMinus1Button_clicked()
{
    if(ui->hourLCDNumber->value() >= 1)
        ui->hourLCDNumber->display(ui->hourLCDNumber->value() - 1);
}

void ProgramForm::on_hourPlus10Button_clicked()
{
    if(ui->hourLCDNumber->value() <= 12)
        ui->hourLCDNumber->display(ui->hourLCDNumber->value() + 10);
}

void ProgramForm::on_hourMinus10Button_clicked()
{
    if(ui->hourLCDNumber->value() >= 10)
        ui->hourLCDNumber->display(ui->hourLCDNumber->value() - 10);
}

void ProgramForm::on_minPlus1Button_clicked()
{
    if(ui->minLCDNumber->value() <= 58)
        ui->minLCDNumber->display(ui->minLCDNumber->value() + 1);
}

void ProgramForm::on_minMinus1Button_clicked()
{
    if(ui->minLCDNumber->value() >= 1)
        ui->minLCDNumber->display(ui->minLCDNumber->value() - 1);
}

void ProgramForm::on_minPlus10Button_clicked()
{
    if(ui->minLCDNumber->value() <= 48)
        ui->minLCDNumber->display(ui->minLCDNumber->value() + 10);
}

void ProgramForm::on_minMinus10Button_clicked()
{
    if(ui->minLCDNumber->value() >= 10)
        ui->minLCDNumber->display(ui->minLCDNumber->value() - 10);
}

void ProgramForm::on_workTimePlus1Button_clicked()
{
    if(ui->workMinsLCDNumber->value() <= 98)
        ui->workMinsLCDNumber->display(ui->workMinsLCDNumber->value() + 1);
}

void ProgramForm::on_workTimeMinus1Button_clicked()
{
    if(ui->workMinsLCDNumber->value() >= 1)
        ui->workMinsLCDNumber->display(ui->workMinsLCDNumber->value() - 1);
}

void ProgramForm::on_workTimePlus10Button_clicked()
{
    ui->workMinsLCDNumber->display(ui->workMinsLCDNumber->value() + 10);
}

void ProgramForm::on_workTimeMinus10Button_clicked()
{
    if(ui->workMinsLCDNumber->value() >= 10)
        ui->workMinsLCDNumber->display(ui->workMinsLCDNumber->value() - 10);
}
