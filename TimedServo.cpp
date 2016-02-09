#include "TimedServo.h"
#include "Arduino.h"


/*
 * If we assume that all servo's can move 180degrees in 1/4 second, 2500000ms
 * then we should be able to say when we want the servo to arrive at it's goal
 *
 *
 * Distance = abs(goal - current)
 * TravelTime = Distance * SERVO_DEG_SPEED
 * we want to arrive at a particular time though
 * if (goalTimeFromNow_<TravelTime) // want to arrive sooner then the possible travel time
 *     intermediateGoal = goal;
 * else                             // want to arrive later then the possible travel time
 *     we need to divide up the distance into smaller chunks
 *     intermediateGoalTimeFromNow = goalTimeFromNow_ / SERVO_DEG_SPEED;// eg if traveltime is 2 sec, and goal is 10 sec, then result is 10 /2 = 5 is 5 intermediate goals
 *
 */
void TimedServo::SetAngle(int newGoal, unsigned long thisTime,unsigned long goalTimeFromNow_)
{
  Distance = abs(newGoal - goal);
  unsigned long TravelTime = Distance * SERVO_DEG_SPEED;
  goalTimeFromNow = goalTimeFromNow_;
  goal = newGoal;
  if (goalTimeFromNow_ < TravelTime)    {   // want to arrive sooner then possible travel time, do best that we can
      write(newGoal);   // just update it
      pos = newGoal;
  }
  else {    // want to arrive later then possible travel time
      step = (goalTimeFromNow / Distance);// time between degrees
      intermediatGoal = thisTime + step;
  }
  lastTime = thisTime;
}
bool TimedServo::TimePassed(unsigned long currentMillSec)
{
    return currentMillSec >= intermediatGoal;
}

bool TimedServo::Update(unsigned long currentMillSec)
{
    if (goal==pos) {
        lastTime = currentMillSec;
        return false; // we have arrived
    }

  if (!TimePassed(currentMillSec)) return false; // not due for an update
  // ok update
  if (pos<goal) pos++;
  else pos--;
  write(pos);
  lastTime = currentMillSec;
  intermediatGoal += step;
  return true;
}
