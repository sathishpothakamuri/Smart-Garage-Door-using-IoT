#include <Stepper.h>

const int pingPin = 2;
const int motorPin = 13;
void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
}

void loop() {
  // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  int duration, cm;

  // The Sonar is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the Sonar: a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);

  // Print the distance
  Serial.print("Distance: ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  // Turn on the motor when the object is in range
  if(cm < 329) {
    digitalWrite(motorPin, HIGH);
    delay(4000); // The time it takes for the garage door to reach the top or bottom
  }
  else {
    digitalWrite(motorPin, HIGH);
  }
  digitalWrite(motorPin, LOW);
  delay(1000); 
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}


 
