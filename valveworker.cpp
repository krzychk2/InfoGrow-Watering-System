#include "valveworker.h"


ValveWorker::ValveWorker(shared_ptr<GPIO> gpio): gpio(gpio) {

}

ValveWorker::~ValveWorker(){
    gpio->setValue(GPIO::Down);
}

void ValveWorker::setWorkTimeSlot(unsigned int workTime){
    this->workTime = workTime;
}

void ValveWorker::run(){
    //workTime in minutes

    while(true){
        if(workTime>0){
            gpio->setValue(GPIO::Up);

            //The main loop decrements time
            for(unsigned int i=workTime*60; i !=0 && workTime>0; --i){
                //emit updateDurationTimeSignal(i);
                if(i >= 99) {
                    //Time in minutes
                    emit updateValveTimeSignal(
                                mapFromGPIOPinToHD44780Valves(gpio->getPinNumber()),
                                static_cast<unsigned int>(i/60),
                                HD44780::Minutes);
                } else {
                    //Time in seconds
                    emit updateValveTimeSignal(
                                mapFromGPIOPinToHD44780Valves(gpio->getPinNumber()),
                                i,
                                HD44780::Seconds);

                }
                //cout << "Tick: " << i << "s" << endl;
                QThread::sleep(1);
            }
            gpio->setValue(GPIO::Down);
            workTime=0;
            emit updateValveTimeSignal(
                        mapFromGPIOPinToHD44780Valves(gpio->getPinNumber()),
                        0,
                        HD44780::Minutes);
        }
        else {
            //cout << "Nothing to do" << endl;
            QThread::sleep(1);
        }
    }
}

HD44780::Valves ValveWorker::mapFromGPIOPinToHD44780Valves(const unsigned int &gpioPin){
        switch(gpioPin){
        case 6:
            return HD44780::V1;
            break;
        case 12:
            return HD44780::V2;
            break;
        case 13:
            return HD44780::V3;
            break;
        case 16:
            return HD44780::V4;
            break;
        case 19:
            return HD44780::V5;
            break;
        case 20:
            return HD44780::V6;
            break;
        case 21:
            return HD44780::V7;
            break;
        case 26:
            return HD44780::V8;
            break;
        default:
            return HD44780::V1;
    }
}

