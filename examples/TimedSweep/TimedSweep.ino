/* TimedSweep
 This example code is in the public domain.
*/

#include <TimedServo.h>

TimedServo myservo[2];  // create servo objects to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

int dest[2];
int speed[2];
void SerialPrintStatus(int i)
{
  if (i) Serial.print("\t\t\t\t\t");
	Serial.print("servo ");Serial.print(i); Serial.print(" at "); Serial.print(myservo[i].pos);
		Serial.print(" going to "); Serial.print(dest[i]); 
			Serial.print(" in "); Serial.print(speed[i] / 1000.0); Serial.println(" seconds");
}
void setup() {
  Serial.begin(115200);

	myservo[0].attach(9);  // attaches the servo on pin 9 to the servo object
	myservo[1].attach(10);  // attaches the servo on pin 10 to the servo object
	unsigned long lastTime = millis(); // 1,000 per sec
	for(int i=0;i<2;i++) {			
		dest[i] = random(0,180);
		speed[i] = random(15,10000);	// between immediate and 10 seconds
    myservo[i].SetAngle(dest[i],lastTime,speed[i]); // set new angle and destination
		SerialPrintStatus(i);
	}  
}

void loop() {
  
	unsigned long lastTime = millis(); // 1,000 per sec
	for(int i=0;i<2;i++)
		if (myservo[i].Update(lastTime)) { // take up to 10 seconds to move to new dest    
			//SerialPrintStatus(i);
			if (myservo[i].pos==dest[i])	{	// have reached destination?
				dest[i] = random(0,180);	// set new destination
				speed[i] = random(15,10000);	// set new speed
				SerialPrintStatus(i);
        myservo[i].SetAngle(dest[i],lastTime,speed[i]); // set servo with new destination and speed
			}      
		}
}



