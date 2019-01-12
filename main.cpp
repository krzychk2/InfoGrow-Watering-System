#include "mainwindow.h"
#include <QApplication>
#include "hd44780.h"

int main(int argc, char *argv[])
{

    /*
     * allValves init
     */

    allValves.reserve(8);
    //V1
    allValves.push_back(new Valve(6));
    //V2
    allValves.push_back(new Valve(12));
    //V3
    allValves.push_back(new Valve(13));
    //V4
    allValves.push_back(new Valve(16));
    //V5
    allValves.push_back(new Valve(19));
    //V6
    allValves.push_back(new Valve(20));
    //V7
    allValves.push_back(new Valve(21));
    //V8
    allValves.push_back(new Valve(26));

    //GPIO port for turn on power for stearing relays
    GPIO gpio(5);
    gpio.setDirection(GPIO::Write);
    gpio.setValue(GPIO::Up);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    int i=a.exec();

    return i;
}
