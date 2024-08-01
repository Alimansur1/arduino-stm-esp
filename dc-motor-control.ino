const int frPin1 = 5;
const int pwmPin1 = 6; 
const int brakePin1 = 4; 
const int fgPin = 2; 

const int frPin2 = 8; 
const int pwmPin2 = 9; 
const int brakePin2 = 10;

int pulseCounter = 0;
int pulseCounterMax = 0;
int targetLaps = 0;
bool motor2Active = false;

void pulseMotor1() {
  Serial.print("Pulse : ");
  Serial.println(pulseCounter);
  if (pulseCounter >= pulseCounterMax) {
    digitalWrite(pwmPin1, HIGH);
    digitalWrite(brakePin1, LOW); 
    Serial.println("Motor 1 stopped.");
    motor2Active = true; 
    pulseCounterMax = 0;
    pulseCounter = 0;
  }
  pulseCounter++;
}

void dc1Tur(int tur) {
  pulseCounterMax = tur * 250;
  digitalWrite(frPin1, HIGH);
  digitalWrite(pwmPin1, LOW); 
  digitalWrite(brakePin1, HIGH); 
  Serial.println("Motor 1 started.");
}

void dc2Tur() {
  
  Serial.println("Motor 2 starting.");
  digitalWrite(frPin2, HIGH); 
  digitalWrite(brakePin2, HIGH);
  digitalWrite(pwmPin2, LOW);
  delay(5000); 


  Serial.println("Motor 2 stopping.");
  digitalWrite(pwmPin2, HIGH); 
  digitalWrite(brakePin2, LOW); 

  delay(2000); 
  motor2Active  = false ;
}

void setup() {
  Serial.begin(9600);

  // Motor 1 setup
  pinMode(frPin1, OUTPUT);
  pinMode(pwmPin1, OUTPUT);
  pinMode(brakePin1, OUTPUT);
  digitalWrite(brakePin1, HIGH);
  digitalWrite(frPin1, LOW);
  digitalWrite(pwmPin1, HIGH); 
  attachInterrupt(digitalPinToInterrupt(fgPin), pulseMotor1, RISING);

  // Motor 2 setup
  pinMode(frPin2, OUTPUT);
  pinMode(pwmPin2, OUTPUT);
  pinMode(brakePin2, OUTPUT);
  digitalWrite(brakePin2, HIGH); 
  digitalWrite(frPin2, LOW); 
  digitalWrite(pwmPin2, HIGH); 

  Serial.println("Input Desired laps and Press Enter");
}

void loop() {
  if (Serial.available() > 0) {
    String in_char = Serial.readStringUntil('\n');
    int targetLap = in_char.toInt();
    if (targetLap > 0) {
      dc1Tur(targetLap);
    } else {
      Serial.println("Invalid input. Please enter a positive number of laps.");
    }
  }
  if(motor2Active){
    dc2Tur();
  }
}
