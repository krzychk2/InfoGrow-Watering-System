#ifndef HD44780_H
#define HD44780_H

/*
 * HD 44780 Display stearing class
 */

/*
 * Implementation for 16x4 display with PFC I2C and 8th Valve Display.
 */

/* Screen project
V1: __m V5: __m
V2: __m V6: __m
V3: __m V7: __m
V4: __m V8: __m
*/

//#include <QObject>

#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::string;
using std::to_string;
using std::cout;
using std::endl;

/*
 * Needed for I2C
 */

#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port

#define T_INIT1  4100
#define T_INIT2  100

/* PFC8574 Address ----------------------------------------------------------------*/

#define I2C_PCF8574_READ_ADDRESS        0x27 /* 0x4F for reading */
#define I2C_PCF8574_WRITE_ADDRESS       0x27 /* 0x4E for writing */

/* PFC8574 Masks -----------------------------------------------------------------*/
#define RS     0x01
#define RW     0x02
#define EN     0x04
#define BL     0x08

#define PCF8574_TO_HD44780_RS           0x01 /* 0b00000001 */
#define PCF8574_TO_HD44780_RW           0x02 /* 0b00000010 */
#define PCF8574_TO_HD44780_EN           0x04 /* 0b00000100 */
#define PCF8574_TO_HD44780_LED          0x08 /* 0b00001000 */
#define PCF8574_TO_HD44780_D4           0x10 /* 0b00010000 */
#define PCF8574_TO_HD44780_D5           0x20 /* 0b00100000 */
#define PCF8574_TO_HD44780_D6           0x40 /* 0b01000000 */
#define PCF8574_TO_HD44780_D7           0x80 /* 0b10000000 */

/* HD44780 commands -----------------------------------------------------------*/

#define HD44780_MAX_X_SIZE                16
#define HD44780_MAX_Y_SIZE                 4

#define HD44780_CLEAR                   0x01
#define HD44780_HOME                    0x02

#define HD44780_ENTRY_MODE              0x04
#define HD44780_EM_SHIFT_CURSOR            0
#define HD44780_EM_SHIFT_DISPLAY           1
#define HD44780_EM_DECREMENT               0
#define HD44780_EM_INCREMENT               2

#define HD44780_DISPLAY_ONOFF           0x08
#define HD44780_DISPLAY_OFF                0
#define HD44780_DISPLAY_ON                 4
#define HD44780_CURSOR_OFF                 0
#define HD44780_CURSOR_ON                  2
#define HD44780_CURSOR_NOBLINK             0
#define HD44780_CURSOR_BLINK               1

#define HD44780_DISPLAY_CURSOR_SHIFT    0x10
#define HD44780_SHIFT_CURSOR               0
#define HD44780_SHIFT_DISPLAY              8
#define HD44780_SHIFT_LEFT                 0
#define HD44780_SHIFT_RIGHT                4

#define HD44780_FUNCTION_SET            0x20
#define HD44780_FONT5x7                    0
#define HD44780_FONT5x10                   4
#define HD44780_ONE_LINE                   0
#define HD44780_TWO_LINE                   8
#define HD44780_4_BIT                      0
#define HD44780_8_BIT                     16

#define HD44780_CGRAM_SET               0x40
#define HD44780_DDRAM_SET               0x80

class HD44780
{

public:
    HD44780(const string &i2cDevice);
    ~HD44780();

    enum Valves{V1=0, V2=1, V3=2, V4=3, V5=4, V6=5, V7=6, V8=7};
    enum TimeUnit{Minutes=0, Seconds=1};

public:
    void updateValveTimeSlot(const Valves &valve, const unsigned int &time, const TimeUnit &timeUnit);

private:

    vector<TimeUnit> valveTimeUnits = {Minutes, Minutes, Minutes, Minutes, Minutes, Minutes, Minutes};

    /*
     * Common functions
     */
    void generateBaseScreen(void);
    void generateEndScreen(void);


    /*
     * I2C specific functions
     */

    string i2cDevice; //File in dev, ex: "/dev/i2c-1"

    int file_i2c;

    void openI2C();
    void closeI2C();
    void writeI2C(vector<unsigned char> &buffer);
    void I2C_WriteByte(uint8_t &sendByte);


    /*
     * HD 44780 specific functions
     */
    void HD44780_Initialize(void);
    void HD44780_Send_Char(char ch);
    void HD44780_Send_Cmd(uint8_t b);
    void HD44780_Send_4HighBits(uint8_t b, bool isCmd, bool setLedOn);
    void HD44780_Send_4LowBits(uint8_t b, bool isCmd, bool setLedOn);
    void HDD44780_SendLed(bool setLedOn);
    uint8_t HD44780_Get_Busy_State(void);
    void HD44780_Send_String(const char *s);
    void HD44780_GoTo_XY(uint8_t x, uint8_t y);

    void LcdDelay();


};


/*
 * Bardzo, bardzo brzydka definicja ale rozwiązuje kilka problemów
 */

//Init LCD display
extern HD44780 hd44780;


#endif // HD44780_H
