#include <Servo.h>

Servo myServo;                

int lightPin = A0;  // photoresistor connected to A0
int threshold = 700;  // Normal mode: light above 700 = bright
int torchThreshold = 950; // Modified mode: only torch above 950 triggers

int mode = 1;                 
int lastButtonState = HIGH; // previous button state for debounce

int lastAngle = -1;  // stores last angle to prevent servo jitter

void setup() {
  myServo.attach(9);          
  Serial.begin(9600);         
  myServo.write(0);           
  pinMode(2, INPUT_PULLUP);  // button on pin 2, internal pull-up resistor
}

void loop() {
  int buttonState = digitalRead(2);   // read button (LOW = pressed)
  
  // toggle mode on button press (HIGH -> LOW transition)
  if (lastButtonState == HIGH && buttonState == LOW) {
    mode = (mode == 1) ? 2 : 1;       // switch between 1 and 2
    delay(200);                       // debounce delay
  }
  lastButtonState = buttonState;      // save current state for next loop
  
  int light = analogRead(lightPin);   // read light value (0-1023)
  Serial.print("Mode: ");
  Serial.print(mode);
  Serial.print("  Light: ");
  Serial.println(light);              // print to Serial Monitor

  if (mode == 1) {
    // NORMAL MODE (Exp 1): two positions only
    if (light > threshold) {
      myServo.write(90);              // bright light -> 90 degrees
    } else {
      myServo.write(0);               // dark -> 0 degrees
    }
  } 
  else {  // mode == 2
    // MODIFIED MODE (Exp 2): torch seeker, smooth movement
    if (light > torchThreshold) {
      // convert torch brightness (950-1023) to angle (0-180)
      int angle = map(light, torchThreshold, 1023, 0, 180);
      
      // only move if angle changed significantly (prevents jitter)
      if (abs(angle - lastAngle) > 3) {
        myServo.write(angle);
        // lastAngle = angle;  // commented - you can uncomment if needed
        delay(30);              // brief delay after movement
      }
    } else {
      // light is below torch threshold
      if (lastAngle != 0) {
        myServo.write(0);       // return to 0 degrees
        lastAngle = 0;
        delay(330);             // delay before accepting new light readings
      }
    }
  }
  
  delay(120);   // main loop stability delay
}