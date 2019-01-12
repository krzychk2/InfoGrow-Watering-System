#include "program.h"

Program::Program()
{

}

unsigned int Program::getHour() const {
    return hour;
}

unsigned int Program::getMinute() const {
    return minute;
}

bool Program::getWeekDayFlag(WeekDay const &weekDay) const{
    return weekDays.at(weekDay);
}

unsigned int Program::getWorkTime() const {
    return workTime;
}

void Program::setHour(unsigned int const &hour){
    if(hour <=23)
        this->hour = hour;
}

void Program::setMinute(const unsigned int &minute){
    if(minute <= 59)
        this->minute = minute;
}

void Program::setWorkTime(const unsigned int &minutes){
    this->workTime = minutes;
}


bool Program::getWeekDayFlag(const unsigned int &dayNumber) const {
    return weekDays.at(dayNumber);
}

void Program::setWeekDayFlag(const WeekDay &weekDay, const bool &flag) {
    this->weekDays.at(weekDay) = flag;
}

