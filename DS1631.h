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

#include <stdint.h>
#include "Wire.h"

typedef unsigned int uint_t, size_t;

class DS1631Config
{

  public:

    uint_t ONESHOT : 1;  // 0x01
    uint_t POL     : 1;  // 0x02
    uint_t R0      : 1;  // 0x04
    uint_t R1      : 1;  // 0x08
    uint_t NVB     : 1;  // 0x10
    uint_t TLF     : 1;  // 0x20
    uint_t THF     : 1;  // 0x40
    uint_t DONE    : 1;  // 0x80

    DS1631Config();
    DS1631Config(uint8_t val);

    uint8_t getResolution(void);
    void setResolution(uint8_t val);

} __attribute__((__packed__));


class DS1631Temperature
{

  public:

    uint_t __padding : 4;  // 0x000F
    uint_t fracPart  : 4;  // 0x00F0
    uint_t intPart   : 7;  // 0x7F00
    uint_t negative  : 1;  // 0x8000

    DS1631Temperature(int _intPart);
    DS1631Temperature(int _intPart, int _fracPart);
    DS1631Temperature(float _value);
	DS1631Temperature(byte[2] _value);

    operator int() const;
    operator float() const;

} __attribute__((__packed__));


class DS1631
{

  public:

    DS1631Config config;

    DS1631(uint8_t addr);
    DS1631(uint8_t addr, DS1631Config cfg);

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

    uint8_t getAddress(void);

  private:

    uint8_t addr;

    void read(const uint8_t command, uint8_t *data);
    void read(const uint8_t command, uint8_t *data, uint8_t len);

    void write(const uint8_t command);
    void write(const uint8_t command, uint8_t data);
    void write(const uint8_t command, uint8_t *data, uint8_t len);

};


#endif
