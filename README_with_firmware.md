
# ESP32 Water Pump Automation

This project implements a secure, robust, and efficient ESP32-based web server to remotely control and monitor a water pump. It includes detailed logging, secure authentication, real-time updates via WebSocket, and an intuitive frontend UI.

## 🚀 Functionalities Implemented

### Core Pump Control
- User-defined timer for pump activation.
- Default runtime: 20 mins (adjustable), Maximum runtime: 30 mins.
- Manual stop anytime with automatic timeout protection.

### Secure Authentication System
- Password hashing with SHA-256.
- Session timeout after 3 minutes of inactivity.
- Role-based access (Admin/User).

### Admin Panel & User Management
- Add, delete, and change user passwords.
- Real-time status updates of the pump.
- Quick navigation links.

### Real-Time UI Updates
- Real-time pump status and remaining timer via WebSocket.

### Enhanced Logging & Usage Tracking
- Activity logs with timestamps, actions, and user details.
- Daily usage summaries with run count and total duration.
- Logs filterable by weekday.

### Responsive Frontend UI
- User-friendly and responsive web interface.
- Modular pages: Dashboard, Pump Control, Logs, and Admin Panel.

## 📁 Project File Structure
```
ESP32_Water_Pump_Automation/
├── ESP32_Water_Pump_Automation.ino
├── variables.h
├── filesystem.h
├── authentication.h
├── pump_control.h
├── logs.h
├── websocket.h
├── ui.h
└── README.md
```

## 🌐 Deployment Guide (Dynamic DNS & Port Forwarding)

### Step 1: Dynamic DNS Setup
- Register at No-IP or DuckDNS and set your hostname (e.g., `mypump.ddns.net`).

### Step 2: ESP32 Static IP Configuration
```cpp
IPAddress local_IP(192,168,1,150);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
WiFi.config(local_IP, gateway, subnet);
```

### Step 3: Router Port Forwarding

Configure your router as follows:

| Service   | Protocol | External Port | Internal IP   | Internal Port |
|-----------|----------|---------------|---------------|---------------|
| HTTP      | TCP      | 8080          | 192.168.1.150 | 80            |
| WebSocket | TCP      | 81            | 192.168.1.150 | 81            |

### Step 4: Security Recommendations
- Always use strong and unique passwords.
- Regularly check and update firmware.

### Step 5: Test Public Access
- Access your web interface via:
```
http://mypump.ddns.net:8080
```
- WebSocket URL:
```
ws://mypump.ddns.net:81/ws
```

## 🛠️ Getting Started

- Upload code using Arduino IDE with the necessary libraries:
  - `ESPAsyncWebServer`
  - `AsyncTCP`
  - `SPIFFS`
  - `ArduinoJson`

- Initial Admin Login:
```
Username: admin
Password: admin123
```
(Change password immediately after first login)

## 📌 Important Notes
- Ensure stable internet connectivity for NTP and DDNS.
- Regularly backup user and log files.

## 🎯 Further Enhancements
- HTTPS implementation for secure access.
- Email or push notifications on critical events.
- MQTT integration for smart-home automation.

🎉 **Your ESP32 Water Pump Automation is ready!**

## 🛠️ Step-by-Step Guide to Generate `.bin` Firmware:

### Step 1: Setup Arduino IDE
- Install Arduino IDE: [Arduino IDE](https://www.arduino.cc/en/software)
- Add ESP32 support URL:
  ```
  https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
  ```
- Install "ESP32 by Espressif Systems" via Board Manager.

### Step 2: Install Required Libraries
From Arduino IDE:
```
Sketch → Include Library → Manage Libraries
```
Install:
- `ESPAsyncWebServer`
- `AsyncTCP`
- `ArduinoJson`
- `SPIFFS`

### Step 3: Open and Configure Project
- Open `ESP32_Water_Pump_Automation.ino`.
- Configure WiFi and pins in `variables.h`.

### Step 4: Generate `.bin` Firmware
- Select ESP32 board and COM port.
- Export binary via:
```
Sketch → Export compiled Binary
```
- Find `.bin` file in the project directory.

### Step 5: Flash `.bin` (optional via CLI)
Use [esptool.py](https://github.com/espressif/esptool):
```bash
esptool.py --chip esp32 --port COM3 --baud 921600 write_flash -z 0x1000 firmware.bin
```

# ESP32 Water Pump Automation – Safe Testing Guide

## 🚀 Testing ESP32 Water Pump Automation Without Relay/Motor

### ✅ Step-by-Step Instructions:

### Step 1: Hardware Preparation

**Option A: Onboard LED (Recommended for Simplicity)**  
- ESP32 DevKit boards typically use GPIO2 for onboard LED.  
- No additional wiring required.

**Option B: External LED**  
- Connect an external LED through a 220Ω resistor to ESP32 GPIO pin and ground (GND):
```
ESP32 GPIO → 220Ω Resistor → LED (+) Anode → LED (-) Cathode → ESP32 GND
```

---

### Step 2: GPIO Pin Update

Update `variables.h` to reflect your test setup:

```cpp
const int PUMP_RELAY_PIN = 2;  // Use GPIO2 for onboard LED (or your chosen GPIO)
```

---

### Step 3: Uploading Code

- Connect ESP32 via USB.
- Open Arduino IDE:
  - Select your ESP32 board: `Tools → Board → ESP32 Arduino → [Your ESP32 Board]`
  - Select port: `Tools → Port → [ESP32 COM Port]`
- Upload your sketch.

---

### Step 4: Testing Pump Logic

- Open ESP32 web interface:
```
http://<ESP32_IP_ADDRESS>/
```
- Login (default credentials `admin/admin123` or your own).
- Start pump via web UI:
  - LED should turn **ON**, simulating relay activation.
- Stop pump manually or let the timer expire:
  - LED should turn **OFF**, simulating relay deactivation.

---

### Step 5: Verify Real-Time WebSocket Updates

- Open multiple browser tabs/devices to ESP32 UI.
- Observe synchronized real-time status and countdown timer updates across tabs/devices.

---

### Step 6: Logging and Session Validation

- Review logs (`/logs/activity` and `/logs/daily`) for accurate event recording.
- Test multi-user login and session management.

---

## 🛠️ Troubleshooting Tips:

- **LED not responding?** Check GPIO pin and polarity (external LED).
- **WiFi Connection Issues?** Verify WiFi credentials and network status.
- **Web interface issues?** Confirm IP address, device connectivity, and network.

This approach safely verifies software logic and functionality without high-voltage equipment.