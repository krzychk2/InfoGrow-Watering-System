#ifndef SCHEDULERWORKER_H
#define SCHEDULERWORKER_H

#include "program.h"

#include <QThread>
#include <QDateTime>
#include <iostream>

using std::cout;
using std::endl;

/*
 * This class is a scheduler classl
 */

class SchedulerWorker : public QThread {
    Q_OBJECT

public:
    SchedulerWorker(const Program &program);
    ~SchedulerWorker();

    void setProgram(const Program &program);
    Program getProgram(void) const;

signals:
    void setWorkSignal(unsigned int workTime); //workTime in minutes

private:
    Program program;

    void run(void) override;


};


#endif // SCHEDULERWORKER_H
