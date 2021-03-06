/*
This is a test for ultrasound sensor from NewPing
7 is Trig
6 is Echo
3 is ledPin
9 is servo pin
It is normal for servo to act "jumpy" in crowded environment. Remember, the purpose is to avoid object in the air, 
so no need to have a slow-acting servo to counteract a collision. For smooth transition, you can take the average using:
int n = 1;
float distAvg;
pastValues[n] = sonar.ping_cm(); 
for (int i = 0; i < 4; ++i)
{
  distAvg += pastValues[i];
}
distAvg = distAvg/4; 
servoWrite = distAvg * 0.389;
for example, which takes the past 4 inputs and averages them to create smooth motion. This is not as fast-reacting for flight, however. 
*/

#include <NewPing.h>
#include <Servo.h>

NewPing sonar (7 , 6 , 400);
int servoPin = 9;
int servoWrite = 0;
Servo Mort;

int ledPin = 3;
int brightness = 5;
int fade = 0;

void setup() {
    Serial.begin(9600);
    delay(500);
Mort.attach(servoPin);
pinMode(ledPin , OUTPUT);

}

void loop() {
  delay(50);
    Serial.print("Ping: ");
    Serial.print(sonar.ping_cm ());
    Serial.println("cm");
if (sonar.ping_cm() == 0)
  Serial.println("Null");
else
//Max range is 400cm. 175 is servo range. 
//175/400 is our adjusted Servo range.  
servoWrite = sonar.ping_cm()*0.437; 
constrain(servoWrite , 1 , 175);

Mort.write(servoWrite);

  // set the brightness of pin 9:
  analogWrite(ledPin, brightness);

brightness = brightness / sonar.ping_cm();


/* Or alternatively you can set the brightness as, for example:
 if (sonar.ping_cm() > 70) 
  brightness = 0; 
    analogWrite(ledPin, brightness); 
 */

}
