#include <LiquidCrystal.h> 

const int sensorPin = 2;
volatile int pulseCount = 0; 
const int slots = 20; 
const float diameter = 0.026; 
const float pi = 3.141592653589793; 
unsigned long lastTime = 0; 
float rpm = 0; 
float speed_kmh = 0; 
const float correctionFactor = 1.9; 


LiquidCrystal LCD(10, 9, 8, 5, 4, 3, 13);

void setup() {
  pinMode(sensorPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(sensorPin), countPulse, RISING); 
  Serial.begin(9600);


  LCD.begin(16, 2);
  LCD.setCursor(0, 0);
  LCD.print("RPM: ");
  LCD.setCursor(0, 1);
  LCD.print("Speed(km/h):");
}

void loop() {
  unsigned long currentTime = millis();

 
  if (currentTime - lastTime >= 1000) {
    detachInterrupt(digitalPinToInterrupt(sensorPin));
    rpm = (pulseCount / (float)slots) * 60.0 / correctionFactor; 
    float circumference = pi * diameter; 
    speed_kmh = (rpm * circumference * 60.0) / 1000.0;
    pulseCount = 0; 
    lastTime = currentTime; 

    Serial.print("RPM: ");
    Serial.print(rpm);
    Serial.print("Speed (km/h):");
    Serial.println(speed_kmh);


    LCD.setCursor(5, 0);
    LCD.print("          ");
    LCD.setCursor(5, 0);
    LCD.print(rpm);
    LCD.setCursor(13, 1);
    LCD.print("          ");
    LCD.setCursor(13, 1);
    LCD.print(speed_kmh);

    attachInterrupt(digitalPinToInterrupt(sensorPin), countPulse, RISING);
  }
}

void countPulse() {
  pulseCount++; 
}
