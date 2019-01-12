#ifndef VALVEWORKER_H
#define VALVEWORKER_H

#include <QObject>
#include <QThread>
#include "gpio.h"
#include "hd44780.h"

#include <memory>

using std::shared_ptr;

class ValveWorker : public QThread {
    Q_OBJECT


public:

    ValveWorker(shared_ptr<GPIO> gpio);
    ~ValveWorker();

public slots:
    void run() override;
    void setWorkTimeSlot(unsigned int workTime);

signals:
    void updateValveTimeSignal(const HD44780::Valves valve, const unsigned int time, const HD44780::TimeUnit timeUnit);

private:
    unsigned int workTime{0};
    shared_ptr<GPIO> gpio;
    HD44780::Valves mapFromGPIOPinToHD44780Valves(const unsigned int &gpioPin);

};


#endif // VALVEWORKER_H
