#include "schedulerworker.h"


SchedulerWorker::SchedulerWorker(const Program &program) : program(program){

}

SchedulerWorker::~SchedulerWorker(){

}

void SchedulerWorker::setProgram(const Program &program){
    this->program = program;
}

Program SchedulerWorker::getProgram() const {
    return program;
}

void SchedulerWorker::run() {

    bool isSignalEmited(false);
    unsigned int weekDay(0);
    unsigned int hour(0);
    unsigned int minute(0);
    QDateTime local;


    //Infinite loop for constant time checking
    while(true) {
        //Get date and time
        local = QDateTime::currentDateTime();
        //Get week Day (-1 because in QT 1 is monday and for us 0 i Monday)
        weekDay = local.date().dayOfWeek() - 1;
        //Get time
        hour = local.time().hour();
        minute = local.time().minute();

        //Check if current day is an active day week
        if(program.getWeekDayFlag(weekDay)){
            //We are in active day so start work
            if(isSignalEmited == false && hour == program.getHour() && minute == program.getMinute()){
                emit setWorkSignal(program.getWorkTime());
                isSignalEmited = true;
            }
            //We have to switch back to non emited signal after hour and minute
            if(!(hour == program.getHour() && minute == program.getMinute())){
                isSignalEmited = false;
            }

        }
        //Sleep for 1 second
        QThread::sleep(1);
        //cout << "Scheduler"<<endl;
    }
}

