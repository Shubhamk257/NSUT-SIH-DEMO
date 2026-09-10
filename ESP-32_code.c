#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

// 1. IMPORT YOUR AI BRAIN HERE
#include <SIH_Forest_Fire_AI_inferencing.h> 

// 2. NETWORK & SUPABASE SETTINGS
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
const char* supabaseUrl = "PASTE_YOUR_PROJECT_URL_HERE/rest/v1/sensor_data"; 
const char* supabaseKey = "PASTE_YOUR_API_KEY_HERE";

// 3. HARDWARE PINS (Configured for ESP32-S3)
#define DHTPIN 6          // Connect DHT11 data to GPIO 6
#define DHTTYPE DHT11     
#define SMOKE_PIN 4       // Connect MQ-2 analog to GPIO 4 (ADC1 safe)

DHT dht(DHTPIN, DHTTYPE);

// Variables to store the fetched location
float nodeLat = 28.6091; // Fallbacks
float nodeLng = 77.0411; 

void setup() {
  Serial.begin(115200);
  dht.begin();
  delay(1000);

  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ Wi-Fi Connected!");

  // --- AUTOMATIC IP GEOLOCATION ---
  Serial.println("Fetching GPS Coordinates via IP...");
  HTTPClient http;
  
  // We use a simple CSV API endpoint so we don't have to parse complex JSON on the ESP32
  http.begin("http://ip-api.com/csv/?fields=lat,lon"); 
  int httpCode = http.GET();
  
  if (httpCode == 200) {
    String payload = http.getString(); // Returns something like: "28.6139,77.2090"
    int commaIndex = payload.indexOf(',');
    if (commaIndex > 0) {
      nodeLat = payload.substring(0, commaIndex).toFloat();
      nodeLng = payload.substring(commaIndex + 1).toFloat();
      Serial.printf("✅ Location Acquired: %.4f, %.4f\n", nodeLat, nodeLng);
    }
  } else {
    Serial.println("❌ Failed to fetch location. Using defaults.");
  }
  http.end();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    
    // --- READ PHYSICAL SENSORS ---
    float temp = dht.readTemperature();
    float humidity = dht.readHumidity();
    float smoke = analogRead(SMOKE_PIN);

    if (isnan(temp) || isnan(humidity)) {
      Serial.println("Failed to read from DHT sensor!");
      delay(2000);
      return;
    }

    Serial.printf("Sensors -> Temp: %.1f°C | Humidity: %.1f%% | Smoke: %.0f\n", temp, humidity, smoke);

    // --- RUN THE EDGE AI MODEL ---
    float features[3] = {temp, humidity, smoke}; 
    signal_t features_signal;
    numpy::signal_from_buffer(features, EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, &features_signal);
    
    ei_impulse_result_t result = { 0 };
    run_classifier(&features_signal, &result, false);

    bool isDanger = false;
    float fire_confidence = result.classification[0].value; 
    
    if (fire_confidence > 0.80) { 
      isDanger = true;
      Serial.println("🚨 AI ALERT: Fire conditions detected! 🚨");
    } else {
      Serial.println("✅ AI Status: Normal.");
    }

    // --- SEND ALL DATA TO SUPABASE ---
    HTTPClient http;
    http.begin(supabaseUrl);
    
    http.addHeader("Content-Type", "application/json");
    http.addHeader("apikey", supabaseKey);
    http.addHeader("Authorization", String("Bearer ") + supabaseKey);

    String dangerString = isDanger ? "true" : "false";
    
    // The JSON payload now includes the lat and lng variables
    String jsonPayload = "{\"temperature\":" + String(temp) + 
                         ",\"smoke_level\":" + String(smoke) + 
                         ",\"ai_alert\":" + dangerString + 
                         ",\"lat\":" + String(nodeLat, 4) + 
                         ",\"lng\":" + String(nodeLng, 4) + "}";

    int httpResponseCode = http.POST(jsonPayload);
    
    if (httpResponseCode > 0) {
      Serial.println("✅ Data & Location logged to Supabase!");
    } else {
      Serial.printf("❌ Error sending data: %s\n", http.errorToString(httpResponseCode).c_str());
    }
    
    http.end(); 
  } else {
    Serial.println("Wi-Fi Disconnected!");
  }

  // Wait 10 seconds before next cycle
  delay(10000);
}