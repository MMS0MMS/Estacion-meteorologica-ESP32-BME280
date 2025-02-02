#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>


// Credenciales de la red WiFi
const char* WIFI_SSID = "tu_red_wifi";
const char* WIFI_PASS = "tu_contraseña_wifi";

// Configuración de la API de ThingSpeak
const char* API_KEY = "user_api_key";
const char* THINGSPEAK_URL = "url_channel";

// Objeto del sensor BME280
Adafruit_BME280 bme;

// Función para conectar a la red WiFi con reconexión automática
void conectarWiFi() {
  Serial.print("Conectando a WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado a WiFi");
}

// Función para inicializar el sensor BME280
bool inicializarSensor() {
  if (!bme.begin(0x76)) {
    Serial.println("Error: Sensor BME280 no detectado.");
    return false;
  }
  Serial.println("Sensor BME280 inicializado correctamente.");
  return true;
}

// Función para obtener datos del sensor BME280
void obtenerDatos(float &temp, float &presion, float &humedad) {
  temp = bme.readTemperature();
  presion = bme.readPressure() / 100.0F;
  humedad = bme.readHumidity();
}

// Función para enviar los datos del sensor a ThingSpeak
void enviarDatos(float temp, float presion, float humedad) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Error: No hay conexión WiFi. Reintentando...");
    conectarWiFi();
  }
  
  HTTPClient http;
  String url = String(THINGSPEAK_URL) + "?api_key=" + API_KEY + "&field1=" + String(temp) + "&field2=" + String(presion) + "&field3=" + String(humedad);
  http.begin(url);
  int codigoRespuesta = http.GET();
  
  if (codigoRespuesta > 0) {
    Serial.printf("HTTP %d: Datos enviados con éxito\n", codigoRespuesta);
  } else {
    Serial.printf("Error HTTP: %s\n", http.errorToString(codigoRespuesta).c_str());
  }
  http.end();
}

void setup() {
  Serial.begin(115200);
  conectarWiFi();
  if (!inicializarSensor()) {
    while (true);
  }
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Conexión WiFi perdida. Reintentando...");
    conectarWiFi();
  }

  float temperatura, presion, humedad;
  
  // Obtener datos del sensor
  obtenerDatos(temperatura, presion, humedad);
  
  // Mostrar los valores en el monitor serie
  Serial.printf("Temperatura: %.2f°C, Presión: %.2f hPa, Humedad: %.2f%%\n", temperatura, presion, humedad);
  
  // Enviar los datos a ThingSpeak
  enviarDatos(temperatura, presion, humedad);
  
  // Esperar 15 minutos antes de la siguiente medición
  delay(900000);
}