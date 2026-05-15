#include <Servo.h>

Servo myServo;                

int lightPin = A0;  // photoresistor connected to A0
int threshold = 700;  // Normal mode: light above 700 = bright
int torchThreshold = 800; // Modified mode: only torch above 950 triggers

int mode = 1;                 
int lastButtonState = HIGH; // previous button state for debounce

int lastAngle = -1;  // stores last angle to prevent servo jitter

// LED pins for Experiment 4
int led1 = 5;  // red
int led2 = 6;  // yellow
int led3 = 7;  // green

void setup() {
  myServo.attach(9);          
  Serial.begin(9600);         
  myServo.write(0);           
  pinMode(2, INPUT_PULLUP);   // button on pin 2, internal pull-up resistor
  
  // LED pins as outputs
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
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

  // Experiment 4: LEDs indicate light level
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  
  if (light < 470) digitalWrite(led1, HIGH);   // dark: red LED
  if (light > 500) digitalWrite(led2, HIGH);   // normal: yellow LED
  if (light > 650) digitalWrite(led3, HIGH);   // bright: green LED

  // Experiment 1 & 2: Servo control
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
        lastAngle = angle;      // ← теперь не закомментировано
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