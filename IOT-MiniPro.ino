//©  IoT-Based Smart Irrigation System- Dasitha Dinith Dilshan Dissanayaka

#include <WiFi.h>
#include <FirebaseESP32.h>
#include <DHT.h>

// WiFi Credentials
#define WIFI_SSID "Infinix SMART 7 HD DINITH"
#define WIFI_PASSWORD "dinith123"

// Firebase Credentials
#define WIFI_SSID "your_wifi_ssid"
#define WIFI_PASSWORD "your_wifi_password"

// Define Firebase Data Object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// DHT11 Sensor
#define DHTPIN 4      // DHT11 connected to GPIO4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Moisture Sensor Pins
#define MOISTURE1_PIN 34
#define MOISTURE2_PIN 35
#define MOISTURE3_PIN 32

// Relay Pins
#define RELAY1 26  // Water pump for Block 1
#define RELAY2 27  // Water pump for Block 2
#define RELAY3 14  // Water pump for Block 3
#define FAN1 25    // Fan for temperature control
#define FAN2 33    // Fan for humidity control

// Moisture Threshold
#define MOISTURE_THRESHOLD 20
#define TEMP_THRESHOLD 30   // Turn fan on if temp > 30°C
#define HUMIDITY_THRESHOLD 80 // Turn fan on if humidity > 80%

void setup() {
    Serial.begin(115200);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println("\nConnected to WiFi!");

    config.api_key = API_KEY;
    config.database_url = DATABASE_URL;

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

    if (Firebase.signUp(&config, &auth, "", "")) {
        Serial.println("Firebase signed in anonymously");
    } else {
        Serial.printf("Firebase sign-in failed: %s\n", config.signer.signupError.message.c_str());
    }

    dht.begin();

    pinMode(RELAY1, OUTPUT);
    pinMode(RELAY2, OUTPUT);
    pinMode(RELAY3, OUTPUT);
    pinMode(FAN1, OUTPUT);
    pinMode(FAN2, OUTPUT);

    digitalWrite(RELAY1, LOW);
    digitalWrite(RELAY2, LOW);
    digitalWrite(RELAY3, LOW);
    digitalWrite(FAN1, LOW);
    digitalWrite(FAN2, LOW);
}


void loop() {
  // Read sensor values
  int moisture1 = analogRead(MOISTURE1_PIN);
  int moisture2 = analogRead(MOISTURE2_PIN);
  int moisture3 = analogRead(MOISTURE3_PIN);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Convert raw sensor values to percentage (0-100)
  moisture1 = map(moisture1, 4095, 0, 0, 100);
  moisture2 = map(moisture2, 4095, 0, 0, 100);
  moisture3 = map(moisture3, 4095, 0, 0, 100);

    // Print values to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.print("% \n Soil Moisture 1: ");
  Serial.print(moisture1);
  Serial.print("% | Soil Moisture 2: ");
  Serial.print(moisture2);
  Serial.print("% | Soil Moisture 3: ");
  Serial.print(moisture3);
  Serial.print("%");

    // Send data to Firebase
  Firebase.setInt(fbdo, "/Moisture/Block1", moisture1);
  Firebase.setInt(fbdo, "/Moisture/Block2", moisture2);
  Firebase.setInt(fbdo, "/Moisture/Block3", moisture3);
  Firebase.setFloat(fbdo, "/Environment/Temperature", temperature);
  Firebase.setFloat(fbdo, "/Environment/Humidity", humidity);



    // Check manual/auto mode
    String mode;
    if (Firebase.getString(fbdo, "/Mode")) {
        mode = fbdo.stringData();
    }

    if (mode == "auto") {
        // Automatic Mode
        digitalWrite(RELAY1, (moisture1 < MOISTURE_THRESHOLD) ? LOW : HIGH);
        digitalWrite(RELAY2, (moisture2 < MOISTURE_THRESHOLD) ? LOW : HIGH);
        digitalWrite(RELAY3, (moisture3 < MOISTURE_THRESHOLD) ? LOW : HIGH);
    } else if (mode == "manual") {
        // Manual Mode (Control relays via Firebase)
        int relay1_state, relay2_state, relay3_state;
        Firebase.getInt(fbdo, "/Control/Relay1", &relay1_state);
        Firebase.getInt(fbdo, "/Control/Relay2", &relay2_state);
        Firebase.getInt(fbdo, "/Control/Relay3", &relay3_state);
        
        digitalWrite(RELAY1, relay1_state ? LOW : HIGH);
        digitalWrite(RELAY2, relay2_state ? LOW : HIGH);
        digitalWrite(RELAY3, relay3_state ? LOW : HIGH);
    }

    // Temperature and Humidity Based Fan Control
    digitalWrite(FAN1, (temperature > TEMP_THRESHOLD) ? LOW : HIGH);
    digitalWrite(FAN2, (humidity > HUMIDITY_THRESHOLD) ? LOW : HIGH);

    Serial.println("\n Data updated to Firebase.");
    delay(2000); // Wait for 2 seconds before next update
}
