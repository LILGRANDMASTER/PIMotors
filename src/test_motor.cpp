#include "motor_interface.hpp"
#include <iostream>
#include <unistd.h> // для sleep()

int main()
{
    // Инициализация мотора с адресом 0x0C
    motor_interface::Motor motor;
    motor.setup("test_motor", 0x0C);

    std::cout << "Testing motor interface..." << std::endl;

    motor.reset();

    // Тест скорости
    std::cout << "\nTesting speed control:" << std::endl;
    for(double rpm = 0.0; rpm <= 100.0; rpm += 10.0) {
        motor.set_speed(rpm);
        std::cout << "Set speed: " << rpm << " RPM, Actual speed: " << motor.get_speed() << " RPM" << std::endl;
        sleep(1);
    }

    // Тест энкодера
    std::cout << "\nTesting encoder:" << std::endl;
    for(int i = 0; i < 5; i++) {
        std::cout << "Encoder ticks: " << motor.get_encoder_ticks() << std::endl;
        sleep(1);
    }

    // Остановка
    motor.set_speed(0);

    std::cout << "\nTest completed. Motor stopped." << std::endl;

    return 0;
}