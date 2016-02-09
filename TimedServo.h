#ifndef TIMEDSERVO_H
#define TIMEDSERVO_H

#include <Servo.h>

#ifndef SERVO_SEEED
// SERVOSPEED is time to travel 180 degrees in millisecs (1000 per sec) (my guess)
#define SERVO_SPEED  250.0
#endif
#define SERVO_DEG_SPEED (SERVO_SPEED / 180)

class TimedServo: public Servo
{
public:
  int goal;
  int pos;
  int Distance;
  unsigned long goalTimeFromNow;
  unsigned long intermediatGoal;
  unsigned long step;
  unsigned long lastTime;
public:
  TimedServo() : Servo() {}
  void SetAngle(int newGoal, unsigned long thisTime, unsigned long goalTimeFromNow_);
  bool Update(unsigned long currentMillSec);
  void SetLastTime(unsigned long lt) { lastTime = lt; }
  bool TimePassed(unsigned long currentMillSec);
};

#endif // TIMEDSERVO_H
