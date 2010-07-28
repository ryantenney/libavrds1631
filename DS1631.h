// http://www.mil.ufl.edu/~chrisarnold/components/microcontrollerBoard/AVR/avrlib/docs/html/ds1631_8c-source.html
// http://www.arduino.cc/playground/Code/I2CEEPROM

#ifndef _DS1631_H
#define _DS1631_H

#define DS1631_BASE_ADDR             (0x48)
#define DS1631_ADDR_MASK             (0x07)

#define DS1631_CMD_START_CONVERT_T   (0x51)
#define DS1631_CMD_STOP_CONVERT_T    (0x22)
#define DS1631_CMD_READ_TEMPERATURE  (0xAA)
#define DS1631_CMD_ACCESS_TH         (0xA1)
#define DS1631_CMD_ACCESS_TL         (0xA2)
#define DS1631_CMD_ACCESS_CONFIG     (0xAC)
#define DS1631_CMD_SOFTWARE_POR      (0x54)

#define DS1631_CFG_DONE              (0x80)
#define DS1631_CFG_THF               (0x40)
#define DS1631_CFG_TLF               (0x20)
#define DS1631_CFG_NVB               (0x10)
#define DS1631_CFG_R1                (0x08)
#define DS1631_CFG_R0                (0x04)
#define DS1631_CFG_POL               (0x02)
#define DS1631_CFG_ONESHOT           (0x01)

#define DS1631_CFG_DEFAULT           (0x8C)
#define DS1631_CFG_WRITE_MASK        (0x6F)
#define DS1631_CFG_NV_MASK           (0x03)

#define DS1631_TEMP_MIN              (-55)
#define DS1631_TEMP_MAX              (125)

// {0.5, 0.25, 0.125, 0.0625}

#include <Wire.h>

typedef uint8_t byte;
typedef unsigned int size_t;

class DS1631Config
{

  public:

    int DONE    : 1;
    int THF     : 1;
    int TLF     : 1;
    int NVB     : 1;
    int R1      : 1;
    int R0      : 1;
    int POL     : 1;
    int ONESHOT : 1;

    DS1631Config();
    DS1631Config(byte val);

    byte getResolution(void);
    void setResolution(byte val);

};


class DS1631Temperature
{

  public:

    int negative  : 1;
    int intPart   : 7;
    int fracPart  : 4;
    //int __padding : 4;

    DS1631Temperature(int _intPart);
    DS1631Temperature(int _intPart, int _fracPart);
    DS1631Temperature(float _value);

    operator int() const;
    operator float() const;

};


class DS1631
{

  public:

    DS1631Config config;

    DS1631(byte addr);
    DS1631(byte addr, DS1631Config cfg);

    void start(void);
    void stop(void);

    void readTemp(DS1631Temperature *val);

    void readTH(DS1631Temperature *val);
    void readTL(DS1631Temperature *val);
    
    void writeTH(DS1631Temperature *val);
    void writeTL(DS1631Temperature *val);

    void softwarePOR(void);

    void readConfig(void);
    void writeConfig(void);
    
    byte getAddress(void);

  private:

    byte addr;

    void read(const byte command, byte *data);
    void read(const byte command, byte *data, byte len);

    void write(const byte command);
    void write(const byte command, byte data);
    void write(const byte command, byte *data, byte len);

};


#endif
