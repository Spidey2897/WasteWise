#include <Wire.h>
#include <Servo.h>
#include <CheapStepper.h>

#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6
#define metalPin 7
#define irPin 8
#define servoPin 10
#define buzzerPin 13

#define IN1 A0
#define IN2 A1
#define IN3 A2
#define IN4 A3

CheapStepper stepper(IN1, IN2, IN3, IN4);
Servo flap;

volatile int wasteType = 0;
int currentPosition = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin(0x08);  // I2C slave address
  Wire.onRequest(sendSensorData);
  Wire.onReceive(receiveWasteType);

  pinMode(S0, OUTPUT); digitalWrite(S0, HIGH);
  pinMode(S1, OUTPUT); digitalWrite(S1, LOW);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  pinMode(metalPin, INPUT);
  pinMode(irPin, INPUT);

  pinMode(buzzerPin, OUTPUT);

  stepper.setRpm(10);
  flap.attach(servoPin);
  flap.write(90);  // Closed position

  Serial.println("🟢 Arduino Ready");
}

void loop() {
  if (wasteType != 0) {
    Serial.print("📦 Waste Type received: ");
    Serial.println(wasteType);

    buzzForType(wasteType);
    rotateToBin(wasteType);
    dropWaste();
    returnToHome();

    wasteType = 0; // Reset
  }
  delay(50);
}

void sendSensorData() {
  int metal = digitalRead(metalPin) == LOW ? 1 : 0;
  int ir = digitalRead(irPin) == LOW ? 1 : 0;

  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  delay(10);
  int color = pulseIn(sensorOut, LOW);

  // Send three int16 values (metal, ir, color)
  Wire.write(lowByte(metal));
  Wire.write(highByte(metal));

  Wire.write(lowByte(ir));
  Wire.write(highByte(ir));

  Wire.write(lowByte(color));
  Wire.write(highByte(color));
}

void receiveWasteType(int byteCount) {
  if (Wire.available()) {
    wasteType = Wire.read();  // 1=metal, 2=wet, 3=dry bio, 4=dry non bio
  }
}

void buzzForType(int type) {
  int freq = 1000;
  switch (type) {
    case 1: freq = 900; break;
    case 2: freq = 1100; break;
    case 3: freq = 1300; break;
    case 4: freq = 1500; break;
  }
  tone(buzzerPin, freq, 500);
  delay(600);
  noTone(buzzerPin);
}

void rotateToBin(int type) {
  int degrees = 0;
  switch (type) {
    case 1: degrees = 0; break;
    case 2: degrees = 90; break;
    case 3: degrees = 180; break;
    case 4: degrees = 270; break;
  }
  if (degrees > 0) {
    stepper.moveDegreesCW(degrees);
    currentPosition = degrees;
  }
}

void returnToHome() {
  if (currentPosition > 0) {
    Serial.println("↩ Returning to home");
    stepper.moveDegreesCCW(currentPosition);
    currentPosition = 0;
  }
}

void dropWaste() {
  Serial.println("🟢 Dropping waste...");
  flap.write(0);
  delay(1000);
  flap.write(90);
}