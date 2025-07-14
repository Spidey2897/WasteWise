# ♻️ WasteWise: Smart Waste Segregator for a Sustainable Future

WasteWise is an intelligent, sensor-based waste segregation system designed to classify and sort waste into four categories using affordable electronics and real-time processing. It is aimed at supporting sustainable waste management in retail and commercial spaces by automating initial waste handling and reducing manual sorting efforts.

> 🏁 Submitted for the Walmart Hackathon 2025 under the theme “Creating a Sustainable Future.”

---

## 🔍 Project Overview

WasteWise identifies and segregates waste into:
- 🟠 Metal Waste
- ⚪ Dry Biodegradable Waste
- ⚫ Dry Non-Biodegradable Waste
- 🔵 Wet Waste

It leverages a combination of sensors and actuators to detect the type of waste and uses a stepper motor + servo combo to direct it to the appropriate bin — all without the need for AI or a camera!

---

## 🧠 Features

- 🧲 Inductive Proximity Sensor for metal detection
- 📦 IR Sensor + Color Sensor (TCS3200) for dry waste classification
- 💧 Rain Sensor for detecting wet/moist waste
- ⚙️ Stepper motor rotates bins based on type
- 🧴 Servo flap drops waste
- 🔔 Buzzer for audio feedback
- 🔁 Returns to home position automatically

---

## 🧰 Hardware Used

| Component                     | Qty | Description                                     |
|------------------------------|-----|-------------------------------------------------|
| Arduino Uno                  | 1   | Microcontroller board                          |
| TCS3200 Color Sensor         | 1   | For detecting white/black for dry waste         |
| Inductive Proximity Sensor   | 1   | Detects metal presence                          |
| IR Sensor (or IR Proximity)  | 1   | Detects presence of dry waste                   |
| Rain Drop Sensor (Analog)    | 1   | Detects wet/moisture waste                      |
| 28BYJ-48 Stepper Motor       | 1   | Controls bin rotation via ULN2003 driver        |
| ULN2003 Driver Board         | 1   | Drives the stepper motor                        |
| Servo Motor (SG90/5010)      | 1   | Opens and closes the waste flap                 |
| Buzzer                       | 1   | Optional alert feedback                         |
| 12V Adapter or USB Power     | 1   | Powers Arduino and components                   |
| Jumper Wires, Breadboard     | —   | For connections                                 |

---

## 📌 Circuit Connections

### Color Sensor (TCS3200)

| Pin     | Arduino |
|---------|---------|
| S0      | D2      |
| S1      | D3      |
| S2      | D4      |
| S3      | D5      |
| OUT     | D6      |
| VCC     | 5V      |
| GND     | GND     |

### Other Inputs

| Component            | Pin      |
|----------------------|----------|
| Metal Sensor (OUT)   | D7       |
| IR Sensor (OUT)      | D8       |
| Rain Sensor (Analog) | A4       |

### Outputs

| Component            | Pin      |
|----------------------|----------|
| Servo                | D10      |
| Buzzer               | D13      |

### Stepper Motor (ULN2003 Driver)

| ULN2003 IN | Arduino Analog Pin |
|------------|--------------------|
| IN1        | A0                 |
| IN2        | A1                 |
| IN3        | A2                 |
| IN4        | A3                 |

Power ULN2003 with 5V and GND from Arduino or external 5V supply.

---

## 💻 How It Works

1. Reads color value using TCS3200 sensor.
2. Prioritizes detection in the order:
   - Metal → Dry → Wet
3. Based on detection:
   - Rotates stepper motor to designated bin (0°, 90°, 180°, 270°)
   - Opens servo flap
   - Closes flap
   - Returns motor to home position
4. Buzzer gives audio feedback on detection.

---

## 📂 Code Summary

- Includes servo & stepper control via `CheapStepper` and `Servo` libraries
- Uses analog read for wet waste via rain sensor
- Uses `pulseIn()` to determine color from TCS3200
- Logic in loop handles detection and action based on priority

---

## 🎥 Demo Video

A 2-minute demonstration video has been submitted for the Walmart Hackathon.

---

## 💡 Impact

By automating waste segregation at the initial point of collection, WasteWise:
- Reduces manual labor
- Promotes sustainable practices
- Can be scaled to retail outlets, schools, offices, and urban smart bins
- Is low-cost and beginner-friendly for IoT makers and eco-innovators

---

## 🚀 Future Improvements

- AI-based detection for mixed waste
- LCD/OLED Display for waste category
- Wireless data logging of waste type count
- Solar-powered model

---

## 👥 Credits

- Project Name: WasteWise
- Built by: [Your Team Name]
- For: Walmart Hackathon 2025
- Track: “Creating a Sustainable Future”

---

## 📜 License

Open-source under MIT License. Feel free to fork, improve and deploy in your own way.

