#include <Servo.h>

Servo myServo;            // create servo object

int lightPin = A0;        // photoresistor connected to A0
int threshold = 700;      // if light > threshold -> bright, else dark

void setup() {
  myServo.attach(9);      // servo signal from pin 9
  Serial.begin(9600);     // start serial for debugging
  myServo.write(0);       // starting position - at 0 deg
}

void loop() {
  int light = analogRead(lightPin);  // read voltage from photoresistor
  Serial.println(light);             // send value (0-1023) to Serial Monitor

  if (light > threshold) {           // bright - servo to 90 degrees
    myServo.write(90);
  } else {                           // dark - servo to 0 degrees
    myServo.write(0);
  }

  delay(100);                        // small delay for stability
}