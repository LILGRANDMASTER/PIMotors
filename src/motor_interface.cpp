#include "motor_interface.hpp"
#include "mot_reg.hpp"

#include <wiringPiI2C.h>

namespace motor_interface
{
  void Motor::setup(const std::string & name, uint8_t i2c_addr)
  {
    this->wheel_.name_ = name;
    this->wheel_.cmd_ = 0.0;
    this->wheel_.vel_ = 0.0;
    this->wheel_.eff_ = 0.0;

    this->fd_ = wiringPiI2CSetup(i2c_addr);
  }


  void Motor::set_speed(double rpm)
  {
    uint8_t reg = static_cast<uint8_t>(REG_MOT_SET_RPM_L);
    uint8_t data[2] = {0};

    data[0] = static_cast<uint8_t>(static_cast<int16_t>(rpm) & 0xFF);
    data[1] = static_cast<uint8_t>((static_cast<int16_t>(rpm) >> 8) & 0xFF);

    wiringPiI2CWriteBlockData(fd_, reg, data, 2);
  }

  double Motor::get_speed(void)
  {
    uint8_t reg = static_cast<uint8_t>(REG_MOT_GET_RPM_L);
    uint8_t data[2] = {0};
    double vel = 0.0;

    wiringPiI2CReadBlockData(fd_, reg, data, 2);
    vel = static_cast<double>((static_cast<int16_t>(data[1]) << 8) | static_cast<int16_t>(data[0]));
    return vel;
  }

  uint32_t Motor::get_encoder_ticks(void)
  {
    uint8_t reg = REG_MOT_GET_REV_L;
    uint8_t data[3] = {0};

    wiringPiI2CReadBlockData(fd_, reg, data, 3);

    return (static_cast<uint32_t>(data[2]) << 16) | (static_cast<uint32_t>(data[1]) << 8) | (static_cast<uint32_t>(data[0]));
  }

  void Motor::set_direction(bool dir)
  {
    uint8_t reg = REG_BITS_2;
    uint8_t data = 0;

    wiringPiI2CReadBlockData(fd_, reg, &data, 1);

    data = (dir ? BIT_DIR_CKW : 0) | data & (~BIT_DIR_CKW);
    
    wiringPiI2CWriteBlockData(fd_, reg, &data, 1);
  }

  bool Motor::get_direction(void)
  {
    uint8_t reg = REG_BITS_2;
    uint8_t data = 0;

    wiringPiI2CReadBlockData(fd_, reg, &data, 1);

    return (data & BIT_DIR_CKW);
  }
}