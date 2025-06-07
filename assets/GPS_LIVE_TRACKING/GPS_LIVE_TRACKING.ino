
#include <WiFi.h>                    // Wi-Fi support
#include <WebServer.h>              // Web server for serving HTML content
#include <LiquidCrystal_I2C.h>      // LCD I2C display library

// Define GPS UART pins
#define GPS_RX_PIN 16
#define GPS_TX_PIN 17

// Wi-Fi credentials
const char* ssid = "Mi";
const char* password = "123456789";

// Create a web server on port 80
WebServer server(80);

// Use Serial2 for GPS communication
HardwareSerial gpsSerial(2);

// Initialize 16x2 LCD (I2C address 0x27)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Global variables to hold GPS data
String latitude = "0.0";
String longitude = "0.0";
String altitude = "0.0";
String satellites = "00";
bool gpsConnected = false;  // Flag to track GPS lock status

// Convert GPS NMEA format (ddmm.mmmm) to decimal degrees
String convertToDecimal(String raw, String dir) {
  if (raw.length() < 6) return "0.0";
  int dot = raw.indexOf('.');
  int degLen = dot - 2;
  float deg = raw.substring(0, degLen).toFloat();      // Extract degrees
  float min = raw.substring(degLen).toFloat();         // Extract minutes
  float decimal = deg + (min / 60.0);                  // Convert to decimal degrees
  if (dir == "S" || dir == "W") decimal *= -1;         // Handle hemisphere
  return String(decimal, 6);
}

// Read GPS data and parse GPGGA sentence
void readGPS() {
  static String line = "";
  
  // Read characters from GPS serial
  while (gpsSerial.available()) {
    char c = gpsSerial.read();
    
    if (c == '\n') {  // End of sentence
      if (line.startsWith("$GPGGA")) {
        // Split GPGGA line into fields
        int idx = 0;
        String parts[15];
        for (int i = 0; i < 15; i++) parts[i] = "";
        for (int i = 0; i < line.length(); i++) {
          if (line[i] == ',') {
            if (idx < 14) idx++;
          } else {
            if (idx < 15) parts[idx] += line[i];
          }
        }

        // Check if valid latitude and longitude are available
        if (parts[2].length() > 0 && parts[4].length() > 0) {
          latitude = convertToDecimal(parts[2], parts[3]);     // Convert latitude
          longitude = convertToDecimal(parts[4], parts[5]);    // Convert longitude
          altitude = parts[9];                                 // Altitude in meters
          satellites = parts[7];                               // Number of satellites

          // Update LCD when GPS is connected for the first time
          if (!gpsConnected) {
            gpsConnected = true;
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("GPS Connected");
          }
        }
      }
      line = "";  // Reset for next line
    } else {
      line += c;  // Append char to line
    }
  }
}

// Generate and return dynamic HTML page with GPS data and map
String buildHTML() {
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <meta http-equiv="refresh" content="5"> <!-- Auto-refresh every 5s -->
      <title>ESP32 GPS Live Map</title>
      <style>
        body { font-family: Arial; background: #ccc; text-align: center; }
        #map { height: 400px; margin: 10px auto; width: 90%; }
        .info { background: #eee; padding: 10px; border-radius: 10px; display: inline-block; }
      </style>
      <link rel="stylesheet" href="https://unpkg.com/leaflet@1.9.4/dist/leaflet.css" />
      <script src="https://unpkg.com/leaflet@1.9.4/dist/leaflet.js"></script>
    </head>
    <body>
      <h2>ESP32 GPS Live Map</h2>
      <div class="info">
        <p><strong>Latitude:</strong> )rawliteral" + latitude + R"rawliteral(</p>
        <p><strong>Longitude:</strong> )rawliteral" + longitude + R"rawliteral(</p>
        <p><strong>Altitude:</strong> )rawliteral" + altitude + R"rawliteral( m</p>
        <p><strong>Satellites:</strong> )rawliteral" + satellites + R"rawliteral(</p>
      </div>
      <div id="map"></div>
      <script>
        // Initialize Leaflet map
        var map = L.map('map').setView([)rawliteral" + latitude + R"rawliteral(, )rawliteral" + longitude + R"rawliteral(], 15);
        L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
          maxZoom: 19
        }).addTo(map);
        // Add GPS marker
        L.marker([)rawliteral" + latitude + R"rawliteral(, )rawliteral" + longitude + R"rawliteral(]).addTo(map);
      </script>
    </body>
    </html>
  )rawliteral";

  return html;
}

// Handle root web page "/"
void handleRoot() {
  server.send(200, "text/html", buildHTML());  // Serve generated HTML
}

void setup() {
  Serial.begin(115200);                        // Start Serial Monitor
  gpsSerial.begin(9600, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);  // Init GPS serial

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Waiting for GPS");

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected. IP: " + WiFi.localIP().toString());

  // Setup web server
  server.on("/", handleRoot);  // Serve HTML on root path
  server.begin();              // Start server
}

void loop() {
  readGPS();           // Continuously read and parse GPS data
  server.handleClient(); // Handle incoming web requests
}
