#pragma once

#include <Arduino.h>
#include <inttypes.h>

#include "AFMotor.h"

const int MAX_SIZE_OF_QUEUE = 20;

#define TIME_FORWARD 1000
#define TIME_BACKWARD 1000
#define TIME_LEFT 1000
#define TIME_RIGHT 1000
#define TIME_ROTATE_CW_90 1000
#define TIME_ROTATE_CCW_90 1000
#define TIME_PAUSE 1000


class Motor
{
public:
  enum class Direction
  {
    FORWARD,
    LEFT,
    BACKWARD,
    RIGHT,
    ROTATE_CW_90,
    ROTATE_CCW_90,
    ROTATE_CW_180,
    ROTATE_CCW_180,
    PAUSE
  };

  struct Move
  {
    Direction direction;
    uint64_t runTime;
    uint64_t startTime = 0;
  };

public:
  Motor();
  
  void addMove(Motor::Direction direction, uint8_t cells);
  void update();

  void setSpeed(uint8_t speed);

  bool paused();

  void pause();
  void unpause();

  bool finished();
private:
  bool m_Paused = false;
  bool m_WasPaused = false;

  int m_Back  = 0;
  int m_Front = 0;

  static AF_DCMotor m_MotorFL;
  static AF_DCMotor m_MotorFR;
  static AF_DCMotor m_MotorBL;
  static AF_DCMotor m_MotorBR;

  Motor::Move m_Moves[MAX_SIZE_OF_QUEUE];

  bool m_Initial = true;
  bool m_Finished = false;

  uint8_t m_Speed = 255;

private:
  Motor::Move& head();
  bool empty();
  void addElement(Motor::Move move);
  void removeElement();

  void moveMotors(Motor::Direction direction);

  void startMotors();
  void stopMotors();

  void moveForward();
  void moveBackward();
  void moveLeft();
  void moveRight();
  void rotate90CW();
  void rotate90CCW();
};
