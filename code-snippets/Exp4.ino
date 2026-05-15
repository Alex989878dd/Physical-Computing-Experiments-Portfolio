int lightPin = A0;
int led1 = 5;
int led2 = 6;
int led3 = 7;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int light = analogRead(lightPin);
  Serial.println(light);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

  if (light < 470) digitalWrite(led1, HIGH); //Dark: red LED on
  if (light > 500) digitalWrite(led2, HIGH); //Normal light: yellow LED on
  if (light > 650) digitalWrite(led3, HIGH); //Bright light: green LED on

  delay(200);
}