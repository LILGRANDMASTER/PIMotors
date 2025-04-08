#ifndef MINO_MOTORS_HPP_
#define MINO_MOTORS_HPP_

#include <cstdint>
#include <string>

namespace motor_interface
{
  class Motor
  {
    public:
    Motor() = default;
    ~Motor() = default;


    void setup(const std::string & name, uint8_t i2c_addr);
    void reset();

    void set_speed(double rpm);
    void set_direction(bool dir);

    double get_speed(void);
    uint32_t get_encoder_ticks(void);
    bool get_direction(void);
    private:

    struct Wheel {
      std::string name_ = "";
      double cmd_ = 0;
      double vel_ = 0;
      double pos_ = 0;
      double eff_ = 0;
    };

    Wheel wheel_;
    int fd_;
  };
}

#endif // MINO_MOTORS_HPP_