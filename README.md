# 🌱 IoT-Based Smart Irrigation System

This project is a smart irrigation system built for our IoT mini project at Rajarata University of Sri Lanka.

## 🔧 Features
- ESP32 + 3 Soil Moisture Sensors + DHT11
- Automatic irrigation when moisture < 20%
- Real-time temperature and humidity monitoring
- Manual/Automatic mode switching via Firebase
- Responsive Web Dashboard for control and monitoring

## 📂 Project Structure
- `firmware/IOT-MiniPro.ino`: ESP32 Arduino code
- `web-dashboard/Dashboard.html`: HTML + CSS Web UI

## 🧠 Technologies Used
- ESP32 Dev Kit
- Firebase Realtime Database & Authentication
- HTML, CSS, JavaScript
- DHT11 & Soil Moisture Sensors
- Relays & Fans for control

## 🛠️ Hardware Components

| Component            | Quantity | Purpose                                |
|---------------------|----------|----------------------------------------|
| ESP32 Dev Kit        | 1        | Main controller                        |
| Soil Moisture Sensor | 3        | To measure soil moisture in 3 blocks   |
| DHT11 Sensor         | 1        | To monitor temperature and humidity    |
| Relay Module         | 3        | Control water pump for each block      |
| Fan (for cooling)    | 2        | Activated by high temp/humidity        |
| Power Supply         | 1        | Stable power for ESP32 and relays      |
| Jumper Wires, Breadboard | as needed | For circuit wiring               |

## 🔌 Wiring Guide

### 🧠 ESP32 Pin Connections

| Sensor / Component    | ESP32 Pin      |
|------------------------|----------------|
| Soil Moisture 1        | GPIO 34 (Analog) |
| Soil Moisture 2        | GPIO 35 (Analog) |
| Soil Moisture 3        | GPIO 32 (Analog) |
| DHT11 Sensor           | GPIO 4         |
| Relay Block 1 (Pump 1) | GPIO 26        |
| Relay Block 2 (Pump 2) | GPIO 27        |
| Relay Block 3 (Pump 3) | GPIO 14        |
| Fan (Temp Control)     | GPIO 25        |
| Fan (Humidity Control) | GPIO 33        |
| VCC                    | 3.3V or 5V (as required) |
| GND                    | GND            |

> 💡 Use a multimeter to calibrate sensor voltage and check thresholds.

---

## ☁️ Firebase Setup Guide

1. Go to [Firebase Console](https://console.firebase.google.com/).
2. Create a new project.
3. Enable **Realtime Database** and set rules:
   ```json
   {
     "rules": {
       ".read": true,
       ".write": true
     }
   }

4. Enable Authentication → Email/Password.
5. Go to Project Settings → General → Web App, get your Firebase Config.
6. Replace firebaseConfig in your web app or Arduino file.
---
  
## 📄 Database Structure

{
  "Mode": "auto",
  "Moisture": {
    "Block1": 55,
    "Block2": 42,
    "Block3": 60
  },
  "Environment": {
    "Temperature": 29,
    "Humidity": 75
  },
  "Control": {
    "Relay1": 0,
    "Relay2": 1,
    "Relay3": 0
  }
}

---

## 🚀 Running the Arduino File
🧾 Requirements:
  -Arduino IDE

Libraries:

  - Firebase_ESP_Client
  - DHT
  - ArduinoJson

✅ Steps:
1. Open IOT-MiniPro.ino in Arduino IDE.
2. Install required libraries (via Library Manager).
3. Replace:
  #define WIFI_SSID "your_wifi"
  #define WIFI_PASSWORD "your_password"
  #define API_KEY "your_firebase_api_key"
  #define DATABASE_URL "your_firebase_database_url"
  
4. Connect your ESP32 board.
5. Select correct Board & Port.
6. Click Upload.

## 💻 Running the Dashboard (HTML + JS)
✅ Steps:
1. Open Dashboard.html in a browser (with Firebase config linked).
2. Login or register using Firebase Authentication.
3. View live:
  - Temperature & Humidity
  - Moisture Level Blocks (Color-coded)
  - Mode Toggle (Auto/Manual)
  - Relay Control in Manual Mode

You can also deploy it with Firebase Hosting, Netlify, or use VS Code + Live Server locally.

## 🚀 Live Demo
Web dashboard not deployed yet.

## 📜 License
MIT license

## 👨‍💻 Authors
Built by Dasitha Dinith Dilshan Dissanayaka

