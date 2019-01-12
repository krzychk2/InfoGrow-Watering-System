#ifndef VALVE_H
#define VALVE_H

#include "program.h"
#include <vector>
#include <QThread>
#include "gpio.h"
#include <memory>
#include <fstream>
#include "valveworker.h"
#include "schedulerworker.h"
#include "hd44780.h"

/*
 * Klasa opisująca zawór
 */

using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::ifstream;
using std::ofstream;
using std::streambuf;
using std::cin;
using std::cout;


class Valve : public QObject
{
     Q_OBJECT

public:

    Valve(const unsigned int &gpioPin);
    ~Valve();

    void manualStartValve(const unsigned int workTime); //workTime in minutes
    void manualStopValve();


    Program getProgram(const unsigned int &programID) const;
    void setProgram(const unsigned int &programID, const Program &program);
    unsigned int getProgramsCount() const; 
    void saveProgramToFile(const unsigned int &programID);

signals:
    void updateValveTimeSignal(const HD44780::Valves valve, const unsigned int time, const HD44780::TimeUnit timeUnit);

public slots:
    void updateValveTimeSlot(const HD44780::Valves valve, const unsigned int time, const HD44780::TimeUnit timeUnit);

private:
    /*
     * GPIO Port
     */

    shared_ptr<GPIO> gpio;

    ValveWorker* valveWorker;

    vector< SchedulerWorker* > schedulerWorkers;

    void saveProgramToFile(const Program &program, const unsigned int &programID);
    Program readProgramFromFile(const unsigned int &programID);

    string constructFileName(shared_ptr<GPIO> gpio, const unsigned int &programID);


};

/*
 * Bardzo, bardzo brzydka definicja ale rozwiązuje kilka problemów
 */

extern vector< Valve*> allValves;

#endif // VALVE_H
