/* TimedSweep
 This example code is in the public domain.
*/

#include <TimedServo.h>

TimedServo myservo[2];  // create servo objects to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

int dest[2];
int speed[2];
void SerialPrintStatus(int i);
{
	Serial.print("servo ");Serial.print(i); Serial.print(" at "); Serial.print(servo[i].pos);
		Serial.print(" going to "); Serial.print(dest[i]); 
			Serial.print(" in "); Serial.print(speed[i]); Serial.println("microsec");
}
void setup() {
  Serial.begin(115200);

	myservo[0].attach(9);  // attaches the servo on pin 9 to the servo object
	myservo[1].attach(10);  // attaches the servo on pin 10 to the servo object
	unsigned long lastTime = micros(); // 1,000 per sec
	for(int i=0;i<2;i++) {	
		myservo[i].SetAngle(0,lastTime,0);// immediatly
		dest[i] = random(0,180);
		speed[i] = random(0,10000);	// between immediate and 10 seconds
		SerialPrintStatus(i);
	}  
}

void loop() {
	unsigned long lastTime = micros(); // 1,000 per sec
	for(int i=0;i<2;i++)
		if (myservo[i].SetAngle(dest1,lastTime,speed[i])) { // take up to 10 seconds to move to new dest
			SerialPrintStatus(i);
			if (myservo[i].pos==dest[i])	{	// have reached destination?
				dest[i] = random(0,180);	// set new destination
				speed[i] = random(0,10000);	// set new speed
				SerialPrintStatus(i);
			}
		}
}



