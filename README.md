♻️ WasteWise: Smart Waste Segregator for a Sustainable Future
WasteWise is an intelligent, sensor-based waste segregation system designed to classify and sort waste into four categories using affordable electronics and real-time processing. It supports sustainable waste management in retail and commercial spaces by automating initial waste handling and reducing manual sorting efforts.

🏁 Submitted for the Walmart Hackathon 2025 under the theme “Creating a Sustainable Future.”

🔍 Project Overview
WasteWise identifies and segregates waste into:

🟠 Metal Waste

⚪ Dry Biodegradable Waste

⚫ Dry Non-Biodegradable Waste

🔵 Wet Waste

It uses a machine learning model trained with Edge Impulse to classify sensor readings into one of the four categories. The ESP32 acts as the master device running the model, while the Arduino UNO collects sensor data and handles actuation.

🧠 Features
🧲 Inductive Proximity Sensor for metal detection

📦 IR Sensor + Color Sensor (TCS3200) for dry waste classification

💧 Rain Sensor (on ESP32) for detecting wet/moist waste

🤖 Machine learning model (.zip from Edge Impulse) for real-time waste classification

⚙️ Stepper motor rotates bins based on detected category

🧴 Servo flap drops waste into selected bin

🔔 Buzzer for audio feedback

🔁 Automatically resets to home position

📡 I2C communication between ESP32 (master) and Arduino UNO (slave)

🧰 Hardware Used
Component	Qty	Description
ESP32	1	Runs ML model, receives sensor data, controls logic
Arduino Uno	1	Collects sensor data, receives bin commands, actuates hardware
TCS3200 Color Sensor	1	For detecting white/black surface for dry waste
Inductive Proximity Sensor	1	Detects metal presence
IR Sensor (or IR Proximity)	1	Detects dry waste presence
Rain Drop Sensor (Analog)	1	Connected to ESP32 to detect wet/moisture waste
28BYJ-48 Stepper Motor	1	Rotates bin platform
ULN2003 Driver Board	1	Drives the stepper motor
Servo Motor (SG90/5010)	1	Opens/closes waste flap
Buzzer	1	Plays tone per waste type
Jumper Wires, Breadboard	—	For wiring

🔗 Connections
UNO (Slave – Sensors + Actuators)
Color Sensor (TCS3200):

Pin	Arduino
S0	D2
S1	D3
S2	D4
S3	D5
OUT	D6
VCC	5V
GND	GND

Other Sensors (UNO Side):

Component	Pin
Metal Sensor (OUT)	D7
IR Sensor (OUT)	D8

Outputs:

Component	Pin
Servo	D10
Buzzer	D13

Stepper Motor via ULN2003:

ULN2003 IN	Arduino Analog Pin
IN1	A0
IN2	A1
IN3	A2
IN4	A3

I2C Connection:

Line	ESP32 Pin	UNO Pin
SDA	21	A4
SCL	22	A5
GND	GND	GND

Rain Sensor:

Signal	ESP32 Pin
AOUT	GPIO 34

💻 How It Works
Arduino UNO reads sensor values (metal, IR, color).

ESP32 requests data from UNO via I2C and appends rain sensor value locally.

ESP32 runs the Edge Impulse ML model to classify the waste type (Metal / Wet / Dry Bio / Dry Non-Bio).

ESP32 sends the bin class number (0–3) back to UNO via I2C.

UNO:

Rotates stepper motor to correct bin angle

Opens/closes servo flap

Plays buzzer tone

Returns motor to 0° position

📂 Code Summary
Master: ESP32 runs Edge Impulse model and handles I2C communication.

Slave: Arduino UNO reads sensors and performs actuation on classification signal.

No manual thresholds; waste type is classified via trained ML model from sensor patterns.

🎥 Demo Video
A 2-minute demonstration video has been submitted for the Walmart Hackathon.

💡 Impact
By automating waste segregation at the point of disposal, WasteWise:

Reduces need for manual sorting

Encourages waste stream separation at source

Is scalable to smart retail, school, campus, and city bins

Demonstrates how affordable sensors + edge ML can solve real-world sustainability problems

🚀 Future Improvements
Use a camera with TensorFlow Lite for mixed object recognition

Add OLED screen to show waste type or status

Log waste types via SD card or cloud

Solar-powered upgrade

BLE app for remote monitoring

👥 Credits
Project Name: WasteWise

Built by: Old School

For: Walmart Hackathon 2025

Track: “Creating a Sustainable Future”

📜 License
Open-source under MIT License. Fork, improve, or deploy your own smart bin today.
