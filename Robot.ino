#include "Motor.h"

Motor motor;

const int TRIG_LEFT = 9;
const int ECHO_LEFT = 10;

const int TRIG_RIGHT = 7;
const int ECHO_RIGHT = 6;

float getDistance(int trigger, int echo)
{
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  long duration = pulseIn(echo, HIGH);
  float distance = duration * 0.034 / 2;
  return distance;
}

void setup() {
  Serial.begin(9600);

  motor.setSpeed(255);

  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT);

  pinMode(TRIG_RIGHT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT);

  /* motor.addMove(Motor::Direction::FORWARD, 1); */
  /* motor.addMove(Motor::Direction::BACKWARD, 1); */
  /* motor.addMove(Motor::Direction::PAUSE, 1); */
  /**/
  /* motor.addMove(Motor::Direction::LEFT, 1); */
  /* motor.addMove(Motor::Direction::RIGHT, 1); */
  /* motor.addMove(Motor::Direction::PAUSE, 1); */
  /**/
   motor.addMove(Motor::Direction::ROTATE_CW_90, 1);
  /* motor.addMove(Motor::Direction::ROTATE_CCW_90, 1); */
  /* motor.addMove(Motor::Direction::PAUSE, 1); */
  /**/
  /* motor.addMove(Motor::Direction::ROTATE_CW_180, 1); */
  /* motor.addMove(Motor::Direction::PAUSE, 1); */
  /* motor.addMove(Motor::Direction::ROTATE_CCW_180, 1); */
  /* motor.addMove(Motor::Direction::PAUSE, 1); */
}

void loop() {
  motor.update();

  Serial.print("Distance Left: ");
  Serial.print(getDistance(TRIG_LEFT, ECHO_LEFT));
  Serial.print(" Distance Right: ");
  Serial.println(getDistance(TRIG_RIGHT, ECHO_RIGHT));

  Serial.print(" ");
  float leftDistance = getDistance(TRIG_LEFT, ECHO_LEFT);

  if (leftDistance < 20.0)
  {
    motor.pause();
  Serial.print("PAUSED");
  }
  else if (motor.paused())
  {
    motor.unpause();
  Serial.print("MOVING");
  }
  Serial.println("");

  if (motor.finished())
  {
    motor.addMove(Motor::Direction::FORWARD, 1);
    /* motor.addMove(Motor::Direction::FORWARD, 1); */
    /* motor.addMove(Motor::Direction::BACKWARD, 1); */
    /* motor.addMove(Motor::Direction::PAUSE, 1); */
    /**/
    /* motor.addMove(Motor::Direction::LEFT, 1); */
    /* motor.addMove(Motor::Direction::RIGHT, 1); */
    /* motor.addMove(Motor::Direction::PAUSE, 1); */
    /**/
    motor.addMove(Motor::Direction::ROTATE_CW_90, 1);
    /* motor.addMove(Motor::Direction::ROTATE_CCW_90, 1); */
    /* motor.addMove(Motor::Direction::PAUSE, 1); */
    /**/
    /* motor.addMove(Motor::Direction::ROTATE_CW_180, 1); */
    /* motor.addMove(Motor::Direction::PAUSE, 1); */
    /* motor.addMove(Motor::Direction::ROTATE_CCW_180, 1); */
    /* motor.addMove(Motor::Direction::PAUSE, 1); */
  }
}
