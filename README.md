# 🚀 ESP32 GPS Live Tracker with Web Map (Leaflet.js)

A compact and efficient live GPS tracker built using **ESP32-WROOM-32** and the **u-blox NEO-6M** GPS module. This project displays GPS status on a **16x2 LCD** and serves a live map through **Leaflet.js**, hosted locally on the ESP32 over Wi-Fi. With ~6-meter accuracy, it's an ideal fit for portable and self-contained GPS tracking applications.

---

## 🛠 Features

- ✅ Real-time location tracking with u-blox NEO-6M
- ✅ Local web server hosted on the ESP32
- ✅ Interactive and responsive map powered by [Leaflet.js](https://leafletjs.com)
- ✅ LCD display with live GPS status messages
- ✅ Auto-updating map every 3 seconds
- ✅ Typical GPS accuracy: ~6 meters
- ✅ Works entirely offline—no cloud or third-party APIs

---

## 🔌 Hardware Required

| Component          | Description                     |
|-------------------|---------------------------------|
| ESP32-WROOM-32     | Main microcontroller             |
| u-blox NEO-6M GPS | GPS module (UART interface)     |
| 16x2 LCD (I2C)     | Status display                  |
| Breadboard + wires | Standard jumper wires           |
| Power source       | 5V via USB or battery            |

---

## ⚙ Pin Connections

| ESP32 Pin    | GPS NEO-6M | LCD (I2C) |
|--------------|------------|-----------|
| RX (GPIO16)  | TX         | —         |
| TX (GPIO17)  | Not used   | —         |
| 3.3V or 5V   | VCC        | VCC       |
| GND          | GND        | GND       |
| SDA (GPIO21) | —          | SDA       |
| SCL (GPIO22) | —          | SCL       |

> 💡 Libraries used: `TinyGPS++` for GPS data parsing and `LiquidCrystal_I2C` for LCD control.

---

## 🌐 How It Works

1. The ESP32 communicates with the NEO-6M via UART to receive GPS coordinates.
2. The LCD screen displays:
   - **"Waiting for GPS"** until a fix is acquired.
   - **"GPS is ready"** once the location is locked.
3. ESP32 connects to your Wi-Fi network and shows the IP address in the Serial Monitor.
4. Open a web browser and visit `http://<ESP32_IP>/` to access the live map.
5. The map updates the current position every 3 seconds using JavaScript and Leaflet.

---

## 📺 Demo Video

🎬 **Project Preview**  
Watch the real-time GPS tracking in action, featuring LCD status updates and live map refreshes:

[▶ Watch Demo Video](https://github.com/MarawanGhazy/ESP32-GPS_Live_Tracking_Device_with_Web_Map/blob/main/assets/VIDEO.mp4)

<video src="https://github.com/MarawanGhazy/ESP32-GPS_Live_Tracking_Device_with_Web_Map/raw/main/assets/VIDEO.mp4" controls style="width:100%; max-width:600px; border-radius:8px;"></video>

---

## 📸 Demo Screenshot

A snapshot of the Leaflet map interface running from the ESP32:

![Leaflet Map Screenshot](https://github.com/MarawanGhazy/ESP32-GPS_Live_Tracking_Device_with_Web_Map/blob/main/assets/MAP.jpg)

---

## 🔧 Libraries Used

Install via **Arduino Library Manager**:

- [TinyGPS++](https://github.com/mikalhart/TinyGPSPlus)
- [LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C)
- `WiFi.h` – For network access
- `WebServer.h` – For hosting the local web page

---

## 🧱 3D-Printed Housing

To enhance portability and protection, the project is enclosed in a custom 3D-printed case designed to fit all components snugly. The housing includes dedicated slots and cutouts for:

- 10x10cm PCB
- u-blox NEO-6M GPS module (with antenna clearance)
- 16x2 LCD (front-facing)
- Power supply access

This enclosure makes the device compact, reliable, and suitable for mobile use—such as mounting on a bike, backpack, or drone.


🖼️ **Full Housing Preview:**

![3D Housing Preview](https://github.com/MarawanGhazy/ESP32-GPS_Live_Tracking_Device_with_Web_Map/raw/main/assets/FULL%20BOX%20PREVIEW.png)

> STL files can be sliced using Cura or PrusaSlicer. Recommended material: PLA+ for indoor use or PETG for outdoor environments.


---


## 🚀 Getting Started

### 1. Hardware Setup
- Wire the GPS and LCD to the ESP32 as per the table above.
- Ensure your GPS antenna has a clear view of the sky for faster satellite lock.

### 2. Arduino IDE Setup
- Install the latest **Arduino IDE**
- Add ESP32 support by adding this to **Preferences > Additional Board URLs**:  
  `https://raw.githubusercontent.com/espressif/arduino-esp32/master/package_esp32_index.json`
- Install the ESP32 board via **Boards Manager**
- Install all required libraries listed above

### 3. Clone & Configure
git clone https://github.com/MarawanGhazy/ESP32-GPS_Live_Tracking_Device_with_Web_Map.git
- Open the .ino file in Arduino IDE
- Edit Wi-Fi credentials:
 const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
Confirm that pin definitions match your wiring.

4. Upload & Run
Connect ESP32 via USB

Select the board: ESP32 Dev Module

Select the correct COM port

Upload the sketch and open Serial Monitor (115200 baud)

Once powered:

LCD will show GPS status

Serial Monitor will display the ESP32's IP

Open a browser → http://<ESP32_IP>/ → Watch the map update in real-time!

📡 Notes
First GPS fix might take a couple of minutes when used outdoors for the first time.

Leaflet.js is fully hosted locally by the ESP32—no external dependencies required.

If you're storing media assets (video/image) on the ESP32, consider using SPIFFS.

🙌 Credits
Developed by Marawan Ghazy X Anas Wagih
This project is open-source and available under the MIT license.

---


