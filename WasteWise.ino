#include <Servo.h>
#include <CheapStepper.h>

// TCS3200 Color Sensor Pins
#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6

// Other Sensors
#define metalPin 7
#define irPin 8
#define servoPin 10
#define buzzerPin 13
#define rainAnalogPin A4   // NEW: Analog pin for rain sensor

// Stepper motor pins via ULN2003
#define IN1 A0
#define IN2 A1
#define IN3 A2
#define IN4 A3

CheapStepper stepper(IN1, IN2, IN3, IN4);
Servo flap;

int wasteType = 0;
int currentPosition = 0;
int colorVal = 0;
int rainThreshold = 500;  // You can adjust this based on your sensor's readings

void setup() {
  Serial.begin(9600);

  // TCS3200 Setup
  pinMode(S0, OUTPUT); digitalWrite(S0, HIGH);
  pinMode(S1, OUTPUT); digitalWrite(S1, LOW);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Inputs
  pinMode(metalPin, INPUT);
  pinMode(irPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(rainAnalogPin, INPUT);  // Analog rain input

  // Stepper
  stepper.setRpm(10);

  // Servo
  flap.attach(servoPin);
  flap.write(90);  // Closed position
}

void loop() {
  // Read color value continuously
  colorVal = readColor();
  Serial.print("🎨 Color Value: "); Serial.println(colorVal);

  // Priority 1: Metal
  if (digitalRead(metalPin) == LOW) {
    Serial.println("🟠 Metal Waste Detected");
    wasteType = 1;
    buzz(1000, 700);
    rotateToBin(wasteType);
    dropWaste();
    returnToHome();
    delay(2000);
    return;
  }

  // Priority 2: Dry Waste
  if (digitalRead(irPin) == LOW) {
    Serial.println("🟡 Dry Waste Detected");

    if (colorVal > 112) {
      Serial.println("⚫ Dry Non-Biodegradable");
      wasteType = 4;
      buzz(1800, 300);
    } else if (colorVal < 40) {
      Serial.println("⚪ Dry Biodegradable");
      wasteType = 3;
      buzz(1500, 300);
    } else {
      Serial.println("❌ Unrecognized Color - No Action");
      return;
    }

    rotateToBin(wasteType);
    dropWaste();
    returnToHome();
    delay(2000);
    return;
  }

  // Priority 3: Wet Waste using analog threshold
  int rainValue = analogRead(rainAnalogPin);
  Serial.print("💧 Rain Sensor Value: "); Serial.println(rainValue);

  if (rainValue < rainThreshold) {
    Serial.println("🔵 Wet Waste Detected");
    wasteType = 2;
    buzz(1200, 500);
    rotateToBin(wasteType);
    dropWaste();
    returnToHome();
    delay(2000);
    return;
  }
}

// TCS3200 color reading
int readColor() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  delay(100);
  return pulseIn(sensorOut, LOW);
}

// Rotate stepper to correct bin
void rotateToBin(int type) {
  int degrees = 0;
  switch (type) {
    case 1: degrees = 0; break;      // Metal
    case 2: degrees = 90; break;     // Wet
    case 3: degrees = 180; break;    // Dry Biodegradable
    case 4: degrees = 270; break;    // Dry Non-Biodegradable
    default: degrees = 0; break;
  }

  if (degrees > 0) {
    stepper.moveDegreesCW(degrees);
    currentPosition = degrees;
  }
}

// Return to home
void returnToHome() {
  if (currentPosition > 0) {
    Serial.println("↩️ Returning to Home");
    stepper.moveDegreesCCW(currentPosition);
    currentPosition = 0;
  }
}

// Open and close servo
void dropWaste() {
  Serial.println("🟢 Dropping Waste...");
  flap.write(0); delay(1000);
  flap.write(90);
}

// Buzzer alert
void buzz(int freq, int duration) {
  tone(buzzerPin, freq, duration);
  delay(duration + 100);
  noTone(buzzerPin);
}
