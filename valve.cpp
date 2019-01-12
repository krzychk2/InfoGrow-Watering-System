#include "valve.h"

vector< Valve*> allValves;

Valve::Valve(const unsigned int &gpioPin)
{
    /*
     * Init programs vector with empty values
     */

    Program p1,p2,p3,p4; 

    /*
     * Init GPIO
     */

    gpio = make_shared<GPIO>(gpioPin);
    gpio->setDirection(GPIO::Write);
    gpio->setValue(GPIO::Down);

    /*
     * Starting Valve Worker Thread
     */

    valveWorker = new ValveWorker(gpio);
    valveWorker->start();

    /*
     * Connect valveWorker update siganl to this updateSlot that forward emit
     */

    qRegisterMetaType<HD44780::Valves>("HD44780::Valves");
    qRegisterMetaType<HD44780::TimeUnit>("HD44780::TimeUnit");

    connect(valveWorker, &ValveWorker::updateValveTimeSignal, this, &Valve::updateValveTimeSlot);

    /*
     * Program load function
     */
    p1=readProgramFromFile(0);
    p2=readProgramFromFile(1);
    p3=readProgramFromFile(2);
    p4=readProgramFromFile(3);


    /*
     * Starting schedulers
     */

    schedulerWorkers.reserve(4);

    schedulerWorkers.push_back(new SchedulerWorker(p1));
    schedulerWorkers.push_back(new SchedulerWorker(p2));
    schedulerWorkers.push_back(new SchedulerWorker(p3));
    schedulerWorkers.push_back(new SchedulerWorker(p4));

    /*
     * Connecting scheduler workers to Valve Worker Thread.
     */


    connect(schedulerWorkers[0], &SchedulerWorker::setWorkSignal, valveWorker, &ValveWorker::setWorkTimeSlot);
    connect(schedulerWorkers[1], &SchedulerWorker::setWorkSignal, valveWorker, &ValveWorker::setWorkTimeSlot);
    connect(schedulerWorkers[2], &SchedulerWorker::setWorkSignal, valveWorker, &ValveWorker::setWorkTimeSlot);
    connect(schedulerWorkers[3], &SchedulerWorker::setWorkSignal, valveWorker, &ValveWorker::setWorkTimeSlot);

    schedulerWorkers.at(0)->start();
    schedulerWorkers.at(1)->start();
    schedulerWorkers.at(2)->start();
    schedulerWorkers.at(3)->start();

}

Valve::~Valve()
{
    manualStopValve();

    /*
     * Program save function on destruct
     */

    saveProgramToFile(schedulerWorkers.at(0)->getProgram(), 0);
    saveProgramToFile(schedulerWorkers.at(1)->getProgram(), 1);
    saveProgramToFile(schedulerWorkers.at(2)->getProgram(), 2);
    saveProgramToFile(schedulerWorkers.at(3)->getProgram(), 3);

    /*
     * Terminate schedulers
     */
    schedulerWorkers.at(0)->terminate();
    schedulerWorkers.at(1)->terminate();
    schedulerWorkers.at(2)->terminate();
    schedulerWorkers.at(3)->terminate();

    schedulerWorkers.at(0)->quit();
    schedulerWorkers.at(1)->quit();
    schedulerWorkers.at(2)->quit();
    schedulerWorkers.at(3)->quit();

    schedulerWorkers.at(0)->wait();
    schedulerWorkers.at(1)->wait();
    schedulerWorkers.at(2)->wait();
    schedulerWorkers.at(3)->wait();

    /*
     * Terminate valve worker thread
     */

    valveWorker->terminate();
    valveWorker->quit();
    valveWorker->wait();
}

Program Valve::getProgram(const unsigned int &programID) const {
    return schedulerWorkers.at(programID)->getProgram();
}

void Valve::setProgram(const unsigned int &programID, const Program &program) {
    schedulerWorkers.at(programID)->setProgram(program);
}


void Valve::manualStartValve(const unsigned int workTime){
    valveWorker->setWorkTimeSlot(workTime);
}

void Valve::manualStopValve(){
    valveWorker->setWorkTimeSlot(0);
    gpio->setValue(GPIO::Down);
}

void Valve::saveProgramToFile(const unsigned int &programID){
    saveProgramToFile(schedulerWorkers.at(programID)->getProgram(), programID);
}

Program Valve::readProgramFromFile(const unsigned int &programID){
    Program program;

    bool tempBool{false};
    unsigned int tempInt{0};

    ifstream in(constructFileName(gpio, programID));

    if(in.is_open()){
        streambuf *cinbuf = std::cin.rdbuf();
        cin.rdbuf(in.rdbuf());

        cin >> tempBool; program.setWeekDayFlag(Program::Monday, tempBool);
        cin >> tempBool; program.setWeekDayFlag(Program::Tuesday, tempBool);
        cin >> tempBool; program.setWeekDayFlag(Program::Wednesday, tempBool);
        cin >> tempBool; program.setWeekDayFlag(Program::Thursday, tempBool);
        cin >> tempBool; program.setWeekDayFlag(Program::Friday, tempBool);
        cin >> tempBool; program.setWeekDayFlag(Program::Saturday, tempBool);
        cin >> tempBool; program.setWeekDayFlag(Program::Sunday, tempBool);
        cin >> tempInt; program.setHour(tempInt);
        cin >> tempInt; program.setMinute(tempInt);
        cin >> tempInt; program.setWorkTime(tempInt);


        std::cin.rdbuf(cinbuf);
        in.close();
    }

    return program;
}

void Valve::saveProgramToFile(const Program &program, const unsigned int &programID){

    ofstream out(constructFileName(gpio,programID));

    if(out.is_open()){
        streambuf *coutbuf = std::cout.rdbuf();
        cout.rdbuf(out.rdbuf());

        cout << program.getWeekDayFlag(Program::Monday) << endl;
        cout << program.getWeekDayFlag(Program::Tuesday) << endl;
        cout << program.getWeekDayFlag(Program::Wednesday) << endl;
        cout << program.getWeekDayFlag(Program::Thursday) << endl;
        cout << program.getWeekDayFlag(Program::Friday) << endl;
        cout << program.getWeekDayFlag(Program::Saturday) << endl;
        cout << program.getWeekDayFlag(Program::Sunday) << endl;
        cout << program.getHour() << endl;
        cout << program.getMinute() << endl;
        cout << program.getWorkTime() << endl;

        std::cout.rdbuf(coutbuf);
        out.close();

    }

}

string Valve::constructFileName(shared_ptr<GPIO> gpio, const unsigned int &programID){
    string fileName;
    fileName = to_string(gpio->getPinNumber()) + "-" + to_string(programID) + ".txt";
    return fileName;
}

unsigned int Valve::getProgramsCount() const {
    return schedulerWorkers.size();
}

void Valve::updateValveTimeSlot(const HD44780::Valves valve, const unsigned int time, const HD44780::TimeUnit timeUnit){
    emit updateValveTimeSignal(valve, time, timeUnit);
}
