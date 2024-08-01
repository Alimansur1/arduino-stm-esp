const int frPin1 = 5;
const int pwmPin1 = 6; 
const int brakePin1 = 4; 
const int fgPin = 2; 

const int frPin2 = 8; 
const int pwmPin2 = 9; 
const int brakePin2 = 10;

int pulseCounter = 0;
int pulseCounterMax = 0;

void pulseMotor1() {
  Serial.print("Pulse : ");
  Serial.println(pulseCounter);
  if (pulseCounter >= pulseCounterMax) {
    digitalWrite(pwmPin1, HIGH); // Motor 1 kapalı
    digitalWrite(brakePin1, LOW); // Motor 1 frenle
    Serial.println("Motor 1 durdu. Motor 2 çalışacak.");
    dc2Tur();
    pulseCounterMax = 0;
    pulseCounter = 0;
  }
  pulseCounter++;
}

void dc1Tur(int tur) {
  pulseCounterMax = tur * 250;
  digitalWrite(frPin1, HIGH); // Motor 1 yönü
  digitalWrite(pwmPin1, LOW); // Motor 1 aç
  digitalWrite(brakePin1, HIGH); // Motor 1 serbest bırak
  Serial.println("Motor 1 çalışmaya başladı.");
}

void dc2Tur() {
  Serial.println("Motor 2 çalışmaya başladı.");
  digitalWrite(frPin2, HIGH); // Motor 2 yönü
  digitalWrite(pwmPin2, LOW); // Motor 2 aç
  digitalWrite(brakePin2, HIGH); // Motor 2 serbest bırak
  delay(5000);

  Serial.println("Motor 2 durduruluyor.");
  digitalWrite(pwmPin2, HIGH); // Motor 2 kapalı
  digitalWrite(brakePin2, LOW); // Motor 2 frenle

  delay(2000); // Motorların durduğundan emin olmak için 2 saniye bekle
}

void setup() {
  Serial.begin(9600);

  // Motor 1 ayarları
  pinMode(frPin1, OUTPUT);
  pinMode(pwmPin1, OUTPUT);
  pinMode(brakePin1, OUTPUT);
  digitalWrite(brakePin1, HIGH);
  digitalWrite(frPin1, LOW);
  digitalWrite(pwmPin1, HIGH); 
  attachInterrupt(digitalPinToInterrupt(fgPin), pulseMotor1, RISING);

  // Motor 2 ayarları
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
}
