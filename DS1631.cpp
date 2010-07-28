#include "DS1631.h"

extern "C" {

DS1631Config::DS1631Config()
{
  byte *self = (byte *) this;
  *self = DS1631_CFG_DEFAULT;
}


DS1631Config::DS1631Config(byte config)
{
  byte *self = (byte *) this;
  *self = config;
}


byte DS1631Config::getResolution(void)
{
  return 9 + (R1 << 1) + R0;
}


void DS1631Config::setResolution(const byte val)
{
  byte _val = (val - 9) & 0x03;
  R1 = _val >> 1;
  R0 = _val & 0x01;
}



DS1631Temperature::DS1631Temperature(int _intVal)
{
  negative = _intVal < 0;
  intPart = (_intVal & 0x7F);
  fracPart = 0;
}


/*DS1631Temperature::DS1631Temperature(int _neg, int _intPart, int _fracPart)
{
  
}*/


DS1631Temperature::DS1631Temperature(float _value)
{
  
}


DS1631Temperature::operator int() const
{
  int _val;
  if (negative)
  {
    _val = -(intPart ^ 0x7F);
  }
  else
  {
    _val = intPart;
  }
  return _val;
}


DS1631Temperature::operator float() const
{
  float _val;
  if (negative)
  {
    _val = -(intPart ^ 0x7F);
  }
  else
  {
    _val = intPart;
  }
  ////
}



DS1631::DS1631(byte _addr)
{
  addr = (_addr & DS1631_ADDR_MASK) | DS1631_BASE_ADDR;
}


DS1631::DS1631(byte _addr, DS1631Config _config)
{
  addr = (_addr & DS1631_ADDR_MASK) | DS1631_BASE_ADDR;
  config = _config;
  
}


void DS1631::read(const byte command, byte *data)
{
  write(command);
  Wire.requestFrom(addr, (byte) 1);
  
  if (Wire.available())
  {
    (*data) = Wire.receive();
  }
}


void DS1631::read(const byte command, byte *data, byte len)
{
  write(command);
  Wire.requestFrom(addr, len);
  
  int recd = 0;
  while (recd < len && Wire.available())
  {
    data[recd++] = Wire.receive();
  }
}


void DS1631::write(const byte command)
{
  Wire.beginTransmission(addr);
  Wire.send(command);
  Wire.endTransmission();
}


void DS1631::write(const byte command, byte data)
{
  Wire.beginTransmission(addr);
  Wire.send(command);
  Wire.send(data);
  Wire.endTransmission();
}


void DS1631::write(const byte command, byte *data, byte len)
{
  Wire.beginTransmission(addr);
  Wire.send(command);
  Wire.send(data, len);
  Wire.endTransmission();
}


void DS1631::start(void)
{
  write(DS1631_CMD_START_CONVERT_T);
}


void DS1631::stop(void)
{
  write(DS1631_CMD_STOP_CONVERT_T);
}


void DS1631::readTemp(DS1631Temperature *data)
{
  byte *val = (byte *) data;
  read(DS1631_CMD_READ_TEMPERATURE, val, 2);
}


void DS1631::readTH(DS1631Temperature *data)
{
  byte *val = (byte *) data;
  read(DS1631_CMD_ACCESS_TH, val, 2);
}


void DS1631::readTL(DS1631Temperature *data)
{
  byte *val = (byte *) data;
  read(DS1631_CMD_ACCESS_TL, val, 2);
}


void DS1631::writeTH(DS1631Temperature *data)
{
  write(DS1631_CMD_ACCESS_TH, (byte *) data, 2);
}


void DS1631::writeTL(DS1631Temperature *data)
{
  write(DS1631_CMD_ACCESS_TL, (byte *) data, 2);
}


void DS1631::readConfig(void)
{
  byte *data = (byte *) &config;
  read(DS1631_CMD_ACCESS_CONFIG, data);
}


void DS1631::writeConfig(void)
{
  write(DS1631_CMD_ACCESS_CONFIG, (byte *) &config, 1);
}


void DS1631::softwarePOR(void)
{
  write(DS1631_CMD_SOFTWARE_POR);
}


byte DS1631::getAddress(void)
{
  return (addr & DS1631_ADDR_MASK);
}

}
