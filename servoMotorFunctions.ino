#include <Servo.h>

Servo myservo;  // create servo object to control a servo
int servoPin = 10;    //  pin

void servoSetup() {
  myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object
  myservo.write(80);
}

void servoTest() {
  Serial.println("Servo Test");
  myservo.write(0);                  // sets the servo position according to the scaled value
  delay(400);  
  myservo.write(80); 
  delay(200); 
  myservo.write(0);
  delay(400);  
  myservo.write(80);                          // waits for the servo to get there
}
