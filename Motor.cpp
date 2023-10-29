#include "Motor.h"

AF_DCMotor Motor::m_MotorFL = AF_DCMotor(2);
AF_DCMotor Motor::m_MotorFR = AF_DCMotor(4);
AF_DCMotor Motor::m_MotorBL = AF_DCMotor(1);
AF_DCMotor Motor::m_MotorBR = AF_DCMotor(3);

Motor::Motor()
{

}

void Motor::addMove(Direction direction, uint8_t cells)
{
  Move move;

  move.direction = direction;
  if (direction == Direction::ROTATE_CW_180)
  {
    move.direction = Direction::ROTATE_CW_90;
  }
  else if (direction == Direction::ROTATE_CCW_180)
  {
    move.direction = Direction::ROTATE_CCW_90;
  }

  uint64_t t = 0; // Calculate time

  switch (direction)
  {
    case Direction::FORWARD:
      t = cells * TIME_FORWARD; break;
    case Direction::BACKWARD:
      t = cells * TIME_BACKWARD; break;
    case Direction::LEFT:
      t = cells * TIME_LEFT; break;
    case Direction::RIGHT:
      t = cells * TIME_RIGHT; break;
    case Direction::ROTATE_CW_90:
      t = cells * TIME_ROTATE_CW_90; break;
    case Direction::ROTATE_CCW_90:
      t = cells * TIME_ROTATE_CCW_90; break;
    case Direction::ROTATE_CW_180:
      t = cells * TIME_ROTATE_CW_90 * 2; break;
    case Direction::ROTATE_CCW_180:
      t = cells * TIME_ROTATE_CCW_90 * 2; break;
    case Direction::PAUSE:
      t = cells * TIME_PAUSE; break;
  }

  move.runTime = t;

  addElement(move);
}

void Motor::update()
{
  if (empty())
  {
    m_Finished = true;
    m_Initial = true ;

    return;
  }

  m_Finished = false;

  if (m_Initial)
  {
    head().startTime = millis();
    m_Initial = false;

    moveMotors(head().direction);

    return;
  }

  Motor::Move& current = head();
  uint64_t duration = millis() - current.startTime;

  if (duration >= current.runTime)
  {
    stopMotors();
    removeElement();

    if (empty())
      return;

    head().startTime = millis();

    moveMotors(head().direction);
  }
}

void Motor::setSpeed(uint8_t speed)
{
  m_Speed = speed;
}

bool Motor::finished()
{
  return m_Finished;
}

Motor::Move& Motor::head()
{
  return m_Moves[m_Front];
}

bool Motor::empty()
{
  return m_Front == m_Back;
}

void Motor::addElement(Motor::Move move)
{
  m_Moves[m_Back] = move;
  m_Back = (m_Back + 1) % MAX_SIZE_OF_QUEUE;
}
void Motor::removeElement()
{
  m_Front = (m_Front + 1) % MAX_SIZE_OF_QUEUE;
}

void Motor::startMotors()
{
  m_MotorFL.setSpeed(m_Speed);
  m_MotorFR.setSpeed(m_Speed);
  m_MotorBL.setSpeed(m_Speed);
  m_MotorBR.setSpeed(m_Speed);
}

void Motor::stopMotors()
{
  m_MotorFL.setSpeed(0);
  m_MotorBL.setSpeed(0);
  m_MotorFR.setSpeed(0);
  m_MotorBR.setSpeed(0);

  m_MotorFL.run(MOTOR_RELEASE); 
  m_MotorFR.run(MOTOR_RELEASE); 
  m_MotorBL.run(MOTOR_RELEASE); 
  m_MotorBR.run(MOTOR_RELEASE); 
}

void Motor::moveMotors(Motor::Direction direction)
{
  switch (direction)
  {
    case Direction::FORWARD:
      moveForward(); break;
    case Direction::BACKWARD:
      moveBackward(); break;
    case Direction::LEFT:
      moveLeft(); break;
    case Direction::RIGHT:
      moveRight(); break;
    case Direction::ROTATE_CW_90:
      rotate90CW(); break;
    case Direction::ROTATE_CCW_90:
      rotate90CCW(); break;

    default:
      break;
  }
  if (direction != Direction::PAUSE)
  {
    startMotors();
  }
}

void Motor::moveForward()
{
  m_MotorFL.run(MOTOR_FORWARD);
  m_MotorFR.run(MOTOR_FORWARD);
  m_MotorBL.run(MOTOR_FORWARD);
  m_MotorBR.run(MOTOR_FORWARD);
}

void Motor::moveBackward()
{
  m_MotorFL.run(MOTOR_BACKWARD);
  m_MotorFR.run(MOTOR_BACKWARD);
  m_MotorBL.run(MOTOR_BACKWARD);
  m_MotorBR.run(MOTOR_BACKWARD);
}

void Motor::moveLeft()
{
  m_MotorFL.run(MOTOR_BACKWARD);
  m_MotorFR.run(MOTOR_FORWARD);
  m_MotorBL.run(MOTOR_FORWARD);
  m_MotorBR.run(MOTOR_BACKWARD);
}

void Motor::moveRight()
{
  m_MotorFL.run(MOTOR_FORWARD);
  m_MotorFR.run(MOTOR_BACKWARD);
  m_MotorBL.run(MOTOR_BACKWARD);
  m_MotorBR.run(MOTOR_FORWARD);
}

void Motor::rotate90CW()
{
  m_MotorFL.run(MOTOR_FORWARD);
  m_MotorFR.run(MOTOR_BACKWARD);
  m_MotorBL.run(MOTOR_FORWARD);
  m_MotorBR.run(MOTOR_BACKWARD);
}

void Motor::rotate90CCW()
{
  m_MotorFL.run(MOTOR_BACKWARD);
  m_MotorFR.run(MOTOR_FORWARD);
  m_MotorBL.run(MOTOR_BACKWARD);
  m_MotorBR.run(MOTOR_FORWARD);
}
