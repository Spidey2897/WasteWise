#include <Wire.h>
#include <WiFi.h>
#include <WebServer.h>
#include <WasteWise_inferencing.h> // Edge Impulse model

#define I2C_SLAVE_ADDR 0x08
#define RAIN_SENSOR_PIN 34

const char* ssid = "WasteWise-AP";
const char* password = "wastewise123";

WebServer server(80);

// Global state variables (not volatile)
String lastClassLabel = "Waiting for data...";
int lastClassIndex = 0;
String flapStatus = "Idle";
String stepperStatus = "At home position";

unsigned long lastInferenceTime = 0;
const unsigned long inferenceInterval = 3000; // 3 seconds


float features[4];

void setup() {
Serial.begin(115200);
Wire.begin(); // ESP32 as I2C master

pinMode(RAIN_SENSOR_PIN, INPUT);

WiFi.softAP(ssid, password);
Serial.println("Access Point started");
Serial.print("Connect to WiFi: ");
Serial.println(ssid);

server.on("/", handleRoot);
server.begin();

run_classifier_init(); // Initialize Edge Impulse model
}

void loop() {
server.handleClient();

if (millis() - lastInferenceTime < inferenceInterval) return;
lastInferenceTime = millis();

// Request 6 bytes: metal, ir, color (2 bytes each)
Wire.requestFrom(I2C_SLAVE_ADDR, 6);

int16_t metal = 0, ir = 0, color = 0;
if (Wire.available() >= 6) {
metal = (int16_t)(Wire.read() | (Wire.read() << 8));
ir = (int16_t)(Wire.read() | (Wire.read() << 8));
color = (int16_t)(Wire.read() | (Wire.read() << 8));
} else {
Serial.println("Error: Not enough data from Uno");
return;
}

int rain = analogRead(RAIN_SENSOR_PIN);

// Prepare features: metal, ir, rain, color
features[0] = (float)metal;
features[1] = (float)ir;
features[2] = (float)rain;
features[3] = (float)color;

// Setup signal_t wrapper
signal_t signal;
signal.total_length = 4;
signal.get_data = [](size_t offset, size_t length, float *out_ptr) -> int {
memcpy(out_ptr, features + offset, length * sizeof(float));
return 0;
};

// Run Edge Impulse classifier
ei_impulse_result_t result;
EI_IMPULSE_ERROR res = run_classifier(&signal, &result, false);

if (res != EI_IMPULSE_OK) {
Serial.println("Failed to run classifier");
return;
}

// Get label with highest confidence
int maxIndex = 0;
float maxValue = 0.0f;
for (size_t i = 0; i < EI_CLASSIFIER_LABEL_COUNT; i++) {
if (result.classification[i].value > maxValue) {
maxValue = result.classification[i].value;
maxIndex = i;
}
}

lastClassLabel = String(result.classification[maxIndex].label);
lastClassIndex = maxIndex + 1; // Send 1-based index to Uno

Serial.printf("Prediction: %s (%.2f%%)\n", lastClassLabel.c_str(), maxValue * 100);

stepperStatus = getBinName(lastClassIndex) + " selected";
flapStatus = "Opening flap to drop waste";

// Send classification result to Uno
Wire.beginTransmission(I2C_SLAVE_ADDR);
Wire.write(lastClassIndex);
Wire.endTransmission();

// Simulate flap closing and stepper reset
delay(1500);
flapStatus = "Flap closed";
stepperStatus = "Returning to home position";
delay(1500);
stepperStatus = "At home position";
}

void handleRoot() {
String html = "<!DOCTYPE html><html><head><title>WasteWise</title>";
html += "<meta http-equiv='refresh' content='3'>";
html += "<style>"
"body { font-family: Arial; background:#f4f4f9; color:#333; text-align:center; padding:20px; }"
"h1 { color: #2E8B57; }"
".status { font-size: 1.3em; margin: 10px auto; padding: 10px; background: #e2f0d9; border-radius: 8px; max-width: 500px; }"
".label { font-weight: bold; }"
"</style></head><body>";

html += "<h1>WasteWise Smart Waste Segregator</h1>";
html += "<div class='status'><span class='label'>Latest Detected Waste Type:</span> " + lastClassLabel + "</div>";
html += "<div class='status'><span class='label'>Bin Position:</span> " + getBinName(lastClassIndex) + "</div>";
html += "<div class='status'><span class='label'>Stepper Motor Status:</span> " + stepperStatus + "</div>";
html += "<div class='status'><span class='label'>Flap Status:</span> " + flapStatus + "</div>";
html += "<p>Page auto-refreshes every 3 seconds.</p></body></html>";

server.send(200, "text/html", html);
}

String getBinName(int idx) {
switch (idx) {
case 1: return "Metal Bin (0°)";
case 2: return "Wet Bin (90°)";
case 3: return "Dry Biodegradable Bin (180°)";
case 4: return "Dry Non-Biodegradable Bin (270°)";
default: return "Home position";
}
}
