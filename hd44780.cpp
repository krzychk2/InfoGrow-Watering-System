#include "hd44780.h"

HD44780 hd44780("/dev/i2c-1");

HD44780::HD44780(const string &i2cDevice) : i2cDevice(i2cDevice)
{
    /*
     * Open I2C port
     */
    cout << "Try to open i2c port " << endl;
    openI2C();

    HD44780_Initialize();
    /*
     * Sends initial screen
     */

    generateBaseScreen();
}

HD44780::~HD44780(){

    //generateEndScreen();
    closeI2C();

}

void HD44780::generateBaseScreen() {

    HD44780_GoTo_XY(0, 0);
    usleep(1000);
    HD44780_Send_String("V1: __m V5: __m");
    usleep(1000);
    HD44780_GoTo_XY(0, 1);
    usleep(1000);
    HD44780_Send_String("V2: __m V6: __m");
    usleep(1000);
    HD44780_GoTo_XY(0, 2);
    usleep(1000);
    HD44780_Send_String("V3: __m V7: __m");
    usleep(1000);
    HD44780_GoTo_XY(0, 3);
    usleep(1000);
    HD44780_Send_String("V4: __m V8: __m");
    usleep(1000);

}

void HD44780::generateEndScreen(){
    HD44780_Send_Cmd(HD44780_CLEAR);
    HD44780_GoTo_XY(0, 0);
    HD44780_Send_String("   Infogrow");
    HD44780_GoTo_XY(0, 1);
    HD44780_Send_String("  Program End");
}

void HD44780::updateValveTimeSlot(const Valves &valve, const unsigned int &time, const TimeUnit &timeUnit){
    /*
     * Position matrix
     */
    unsigned int x=0, y=0;
    switch(valve){
    case Valves::V1:
        x=4; y=0;
        break;
    case Valves::V2:
        x=4; y=1;
        break;
    case Valves::V3:
        x=4; y=2;
        break;
    case Valves::V4:
        x=4; y=3;
        break;
    case Valves::V5:
        x=12; y=0;
        break;
    case Valves::V6:
        x=12; y=1;
        break;
    case Valves::V7:
        x=12; y=2;
        break;
    case Valves::V8:
        x=12; y=3;
        break;
    }

    string s;
    if(time<10){
        if(time==0){
            s="__";
        }
        else {
            s="_"+to_string(time);
        }
    }
    else {
        s=to_string(time);
    }

    /*
     * Detect if time unit changes
     */
     if(timeUnit == TimeUnit::Minutes){
            s+='m';
        }
     if(timeUnit == TimeUnit::Seconds){
            s+='s';
        }

    HD44780_GoTo_XY(x, y);
    usleep(1000);
    HD44780_Send_String(s.c_str());
    usleep(1000);

}

void HD44780::openI2C(){
    char *filename = (char*)"/dev/i2c-1";
    //if ((file_i2c = open(i2cDevice.c_str(), O_RDWR)) < 0)
    cout << "Step 1" << endl;
    if ((file_i2c = open(filename, O_RDWR)) < 0)
        {
            //ERROR HANDLING: you can check errno to see what went wrong
            printf("Failed to open the i2c bus");
            return;
        }
    int addr = I2C_PCF8574_WRITE_ADDRESS;          //<<<<<The I2C address of the slave
    cout << "Step 2" << endl;
    if (ioctl(file_i2c, I2C_SLAVE, addr) < 0)
        {
            printf("Failed to acquire bus access and/or talk to slave.\n");
            //ERROR HANDLING; you can check errno to see what went wrong
            return;
        }
}

void HD44780::closeI2C(){
    cout << "Close I2C" << endl;
    if(close(file_i2c) < 0){
         printf("Failed to close the i2c bus");
    }
}

void HD44780::writeI2C(vector<unsigned char> &buffer){
    if (write(file_i2c, static_cast<void*>(buffer.data()), buffer.size()) != buffer.size())		//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
        {
            /* ERROR HANDLING: i2c transaction failed */
            printf("Failed to write to the i2c bus.\n");
        }
}

void HD44780::I2C_WriteByte(uint8_t &sendByte){
    if (write(file_i2c, &sendByte, 1) != 1)		//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
        {
            /* ERROR HANDLING: i2c transaction failed */
            printf("Failed to write to the i2c bus.\n");
        }

}

/**
  * Initialize HD44780 on I2C
  */
void HD44780::HD44780_Initialize(){
        HD44780_Send_4LowBits(0x03, true, true);
        usleep(1000);
        HD44780_Send_4LowBits(0x03, true, true);
        usleep(1000);
        HD44780_Send_4LowBits(0x03, true, true);
        usleep(1000);

        HD44780_Send_4LowBits(0x02, true, true);
        usleep(1000);



        HD44780_Send_Cmd(HD44780_FUNCTION_SET | HD44780_FONT5x7 | HD44780_TWO_LINE | HD44780_4_BIT); /* interfejs 4-bity, 2-linie, znak 5x7 */
        usleep(1000);
        HD44780_Send_Cmd(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_OFF); /* wylaczenie wyswietlacza */
        usleep(1000);
        HD44780_Send_Cmd(HD44780_CLEAR); /* czyszczenie zawartosci pamieci DDRAM */
        usleep(1000);
        HD44780_Send_Cmd(HD44780_ENTRY_MODE | HD44780_EM_SHIFT_CURSOR | HD44780_EM_INCREMENT);/* inkrementaja adresu i przesuwanie kursora */
        usleep(1000);
        usleep(1000);
        HD44780_Send_Cmd(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_OFF | HD44780_CURSOR_NOBLINK); /* wlacz LCD, bez kursora i mrugania        */
        usleep(1000);
        HD44780_Send_Cmd(HD44780_HOME); /* Powrot kursora do pozycji 0,0 */
        usleep(1000);

}

/**
  * HD44780 Send Char
  */

void HD44780::HD44780_Send_Char(char ch){
    /**
      * Send 4 high bits
      */
    HD44780_Send_4HighBits(ch, false, true);
     /**
       * Send 4 low bits
       */
    HD44780_Send_4LowBits(ch, false, true);


}

/**
  * HD44780 Send Command
  */

void HD44780::HD44780_Send_Cmd(uint8_t sendByte){
    HD44780_Send_4HighBits(sendByte, true, true);
    HD44780_Send_4LowBits(sendByte, true, true);
}

/**
  * HD44780 Send Byte
  */

void HD44780::HD44780_Send_4LowBits(uint8_t sendByte, bool isCmd, bool setLedOn){
        uint8_t LcdByte;
        /*
         * This function always sends only 4 low bits.
         */

        /**
          * Send 4 low bits
          */
        LcdByte = 0x00; /* Clear the sending bit */
        if(!isCmd)      /* If we send Command RS is LOW, in data RS is High */
                        LcdByte |= PCF8574_TO_HD44780_RS;
        if(setLedOn) /* Set LED state */
                        LcdByte |= PCF8574_TO_HD44780_LED;
        else
                        LcdByte &= ~PCF8574_TO_HD44780_LED;
        LcdByte |= (sendByte & 0x0F) << 4; /* Send 4 lower bits. Mask 4 high bits to 0 and make OR */
        I2C_WriteByte(LcdByte); /* Send to I2C */
        LcdByte |= PCF8574_TO_HD44780_EN; /* Set Enable byte */
        I2C_WriteByte(LcdByte); /* Send to I2C */
        LcdByte &= ~PCF8574_TO_HD44780_EN; /* UnSet Enable byte */
        I2C_WriteByte(LcdByte); /* Send to I2C */

}

void HD44780::HD44780_Send_4HighBits(uint8_t sendByte, bool isCmd, bool setLedOn){
    uint8_t LcdByte;
    /*
     * This function always sends only 4 high bits.
     */
    /**
      * Send 4 high bits
      */
    LcdByte = 0x00; /* Clear the sending bit */
    if(!isCmd) /* If we send Command RS is LOW, in data RS is High */
                    LcdByte |= PCF8574_TO_HD44780_RS;
    if(setLedOn) /* Set LED state */
                    LcdByte |= PCF8574_TO_HD44780_LED;
    else
                    LcdByte &= ~PCF8574_TO_HD44780_LED;
    LcdByte |= sendByte & 0xF0; /* Send 4 higher bits. Mask 4 High bits, and 0 4 lover bits and move 4 positions to left and make OR*/
    I2C_WriteByte(LcdByte); /* Send to I2C */
    LcdByte |= PCF8574_TO_HD44780_EN; /* Set Enable byte */
    I2C_WriteByte(LcdByte); /* Send to I2C */
    LcdByte &= ~PCF8574_TO_HD44780_EN; /* UnSet Enable byte */
    I2C_WriteByte(LcdByte); /* Send to I2C */
}

void HD44780::HDD44780_SendLed(bool setLedOn){
    uint8_t LcdByte;
    /*
     * This function always sends only 4 high bits.
     */
    /**
      * Send 4 high bits
      */
    LcdByte = 0x00; /* Clear the sending bit */

    if(setLedOn) /* Set LED state */
                    LcdByte |= PCF8574_TO_HD44780_LED;
    else
                    LcdByte &= ~PCF8574_TO_HD44780_LED;
    I2C_WriteByte(LcdByte); /* Send to I2C */
}

/**
  * LCD Delay
  */
void HD44780::LcdDelay(){
;
}

/**
  * Read the HD44780 RS State
  */
uint8_t HD44780::HD44780_Get_Busy_State(void){
        return 1;
}

/**
  * HD44780 Send String
  */

void HD44780::HD44780_Send_String(const char *s){
        int i=0;
        for(i=0; s[i] != '\0'; i++)
                HD44780_Send_Char(s[i]);
}

/**
  * Initialize HD44780 Cursor to X Y position
  */

void HD44780::HD44780_GoTo_XY (uint8_t x, uint8_t y){
        if(y==0 || y==1)
                HD44780_Send_Cmd(HD44780_DDRAM_SET | (x + (0x40 * y)));
        if(y==2 || y==3)
                HD44780_Send_Cmd(HD44780_DDRAM_SET | (x + HD44780_MAX_X_SIZE + (0x40 * y)));

}
