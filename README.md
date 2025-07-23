
# ♻️ WasteWise: Smart Waste Segregator for a Sustainable Future

WasteWise is an intelligent, sensor-based waste segregation system designed to classify and sort waste into four categories using affordable electronics and real-time processing. It supports sustainable waste management in homes, schools, retail and commercial spaces by automating initial waste handling and reducing the need for manual sorting.

---

## 🔍 Project Overview

WasteWise identifies and segregates waste into:

- 🟠 Metal Waste  
- ⚪ Dry Biodegradable Waste  
- ⚫ Dry Non-Biodegradable Waste  
- 🔵 Wet Waste  

It uses a combination of simple sensors and motors — no AI or camera required! — to make the process fully automated and cost-effective.

---

## 🧠 Features

- 🧲 Inductive Proximity Sensor for metal detection  
- 📦 IR Sensor + Color Sensor (TCS3200) for dry waste classification  
- 💧 Rain Sensor for detecting wet or moist waste  
- ⚙️ Stepper motor rotates to direct waste into appropriate bin  
- 🧴 Servo motor opens and closes a flap for waste entry  
- 🔔 Buzzer for audio feedback  
- 🔁 Automatically returns to home position after sorting  

---

## 🧰 Hardware Used

| Component                     | Qty | Description                                     |
|------------------------------|-----|-------------------------------------------------|
| Arduino Uno                  | 1   | Microcontroller board                          |
| TCS3200 Color Sensor         | 1   | Detects white/black for dry waste              |
| Inductive Proximity Sensor   | 1   | Detects metal presence                         |
| IR Sensor (or IR Proximity)  | 1   | Detects presence of dry waste                  |
| Rain Drop Sensor (Analog)    | 1   | Detects moisture / wet waste                   |
| 28BYJ-48 Stepper Motor       | 1   | Controls bin rotation via ULN2003 driver       |
| ULN2003 Driver Board         | 1   | Drives the stepper motor                       |
| Servo Motor (SG90 or 5010)   | 1   | Opens/closes the waste flap                    |
| Buzzer                       | 1   | Optional audio alert                           |
| 12V Adapter or USB Power     | 1   | Powers Arduino and components                  |
| Jumper Wires, Breadboard     | —   | For wiring and prototyping                     |

---

## 📌 Circuit Connections

### Color Sensor (TCS3200)

| Pin | Arduino |
|-----|---------|
| S0  | D2      |
| S1  | D3      |
| S2  | D4      |
| S3  | D5      |
| OUT | D6      |
| VCC | 5V      |
| GND | GND     |

### Other Inputs

| Component            | Arduino Pin |
|----------------------|-------------|
| Metal Sensor (OUT)   | D7          |
| IR Sensor (OUT)      | D8          |
| Rain Sensor (Analog) | A4          |

### Outputs

| Component | Arduino Pin |
|-----------|-------------|
| Servo     | D10         |
| Buzzer    | D13         |

### Stepper Motor (ULN2003 Driver Board)

| ULN2003 IN | Arduino Pin |
|------------|-------------|
| IN1        | A0          |
| IN2        | A1          |
| IN3        | A2          |
| IN4        | A3          |

> Power the ULN2003 with 5V and GND from Arduino or an external 5V supply.

---

## 💻 How It Works

1. System detects waste using input sensors (metal, IR, rain, color).
2. Priority of detection:
   - Metal → Dry (white/black) → Wet
3. Stepper motor rotates to correct bin location (0°, 90°, 180°, 270°).
4. Servo flap opens → waste drops → flap closes.
5. Buzzer provides audio alert.
6. Stepper returns to default position after sorting.

---

## 📂 Code Summary

- Written in Arduino (C++)
- Uses `CheapStepper` and `Servo` libraries
- `pulseIn()` used to get color frequencies from TCS3200
- Logical flow ensures correct bin for each waste type
- Fully automated with minimal delay

---

## 🎥 Demo Video

Coming soon!  
Or check out the live working system by cloning the repo and uploading the code to your own setup.

---

## 💡 Why It Matters

- Reduces dependency on human labor for waste sorting  
- Encourages sustainable practices at the grassroots level  
- Can be used in homes, schools, retail shops, offices, and public bins  
- Affordable and beginner-friendly for hobbyists and students  

---

## 🚀 Potential Upgrades

- AI-based classification for mixed or ambiguous waste  
- LCD/OLED display showing waste category  
- IoT-based waste logging and analytics  
- Solar-powered version for off-grid use  

---

## 👥 Credits

- Project Name: WasteWise  
- Designed and built by: Brian Walter and Team Old School  
- Inspired by: The need for better sustainable waste management

---

## 📜 License

This project is open-source under the MIT License.  
Feel free to fork, improve, remix, and deploy it for educational or practical use!
