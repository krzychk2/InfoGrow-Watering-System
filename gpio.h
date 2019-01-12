#ifndef GPIO_H
#define GPIO_H


#include <QObject>

#include <QDebug>
#include <QString>
#include <QFile>
#include <QTextStream>


class GPIO : public QObject {

public:
    GPIO(const unsigned int &pinNumber);
    ~GPIO();

    enum GPIODirection { Read=false, Write=true};
    enum GPIOState {Up=true, Down=false};

    //! Set the direction (read/write)
    bool setDirection(const GPIODirection &read);
    //! Write to the port
    bool setValue(const GPIOState &value );
    //! Read from the port
    bool getValue(GPIOState &value );

    unsigned int getPinNumber(void) const {
        return pinNumber;
    }

private:
    unsigned int pinNumber;

    //! Export Port for using
    bool exportGPIO(void);
    //! Unexport Port
    bool unexportGPIO(void);

    //! Port directory and file constants
    const QString baseGPIOPath_ = "/sys/class/gpio/";
    const QString gpioExport_ = "export";
    const QString gpioUnexport_ = "unexport";
    const QString gpioDirection_ = "direction";
    const QString gpioValue_ = "value";

    //! Helper function for writing to the GPIO directory
    bool writeToGPIOFile(const QString file, const QString outputData);

    //! Helper function for reading from the GPIO directory
    bool readFromGPIOFile(const QString file, QString &inputData);
};


#endif // GPIO_H
