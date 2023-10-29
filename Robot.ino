#include "Motor.h"

Motor motor;

void setup() {
  Serial.begin(9600);

  motor.setSpeed(127);

  motor.addMove(Motor::Direction::FORWARD, 1);
  motor.addMove(Motor::Direction::BACKWARD, 1);
  motor.addMove(Motor::Direction::PAUSE, 1);

  motor.addMove(Motor::Direction::LEFT, 1);
  motor.addMove(Motor::Direction::RIGHT, 1);
  motor.addMove(Motor::Direction::PAUSE, 1);

  motor.addMove(Motor::Direction::ROTATE_CW_90, 1);
  motor.addMove(Motor::Direction::ROTATE_CCW_90, 1);
  motor.addMove(Motor::Direction::PAUSE, 1);

  motor.addMove(Motor::Direction::ROTATE_CW_180, 1);
  motor.addMove(Motor::Direction::PAUSE, 1);
  motor.addMove(Motor::Direction::ROTATE_CCW_180, 1);
  motor.addMove(Motor::Direction::PAUSE, 1);
}

void loop() {
  motor.update();

  if (motor.finished())
  {
    motor.addMove(Motor::Direction::FORWARD, 1);
    motor.addMove(Motor::Direction::BACKWARD, 1);
    motor.addMove(Motor::Direction::PAUSE, 1);

    motor.addMove(Motor::Direction::LEFT, 1);
    motor.addMove(Motor::Direction::RIGHT, 1);
    motor.addMove(Motor::Direction::PAUSE, 1);

    motor.addMove(Motor::Direction::ROTATE_CW_90, 1);
    motor.addMove(Motor::Direction::ROTATE_CCW_90, 1);
    motor.addMove(Motor::Direction::PAUSE, 1);

    motor.addMove(Motor::Direction::ROTATE_CW_180, 1);
    motor.addMove(Motor::Direction::PAUSE, 1);
    motor.addMove(Motor::Direction::ROTATE_CCW_180, 1);
    motor.addMove(Motor::Direction::PAUSE, 1);
  }
}
