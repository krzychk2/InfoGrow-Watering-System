#ifndef PROGRAM_H
#define PROGRAM_H

/*
 * Klasa opisująca program do zaworu
 */

#include <vector>

using std::vector;

class Program {

public:
    Program();

    enum WeekDay {Monday=0, Tuesday=1, Wednesday=2, Thursday=3, Friday=4, Saturday=5, Sunday=6};

    void setWeekDayFlag(const WeekDay &weekDay, bool const &flag);
    bool getWeekDayFlag(const WeekDay &weekDay) const;
    bool getWeekDayFlag(const unsigned int &dayNumber) const;

    void setHour(const unsigned int &hour);
    unsigned int getHour(void) const;

    void setMinute(const unsigned int &minute);
    unsigned int getMinute(void) const;

    void setWorkTime(const unsigned int &minutes);
    unsigned int getWorkTime(void) const;


private:
    /*
     * Weekday of active program
     */
    vector<bool> weekDays={false, false, false, false, false, false, false};

    /*
     * Hour and minute, when the program start
     */
    unsigned int hour{0};
    unsigned int minute{0};

    /*
     * Minutes of working time
     */
    unsigned int workTime{0};

};

#endif // PROGRAM_H
