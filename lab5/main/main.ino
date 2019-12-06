#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

#define DHTPIN 32
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const int liquidSensor = A5;

String url_request = "https://api.thingspeak.com/update?api_key=S3U89UWTTT2HPIT7&";
const char* ssid = "PBLMD";
const char* password = "vemWjibl";

const char* liquidSensorFieldName = "field2";
const char* temperatureSensorFieldName = "field1";
 
void connectToWifi()
{
  delay(4000);
 
  WiFi.begin(ssid, password); 
 
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
 
  Serial.println("Connected to the WiFi network");
}
 
void write_to_cloud(int value, const char* fieldName) {
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;   
    http.begin(url_request + fieldName + "=" + String(value));

    int httpResponseCode = http.GET();
    if (httpResponseCode > 0)
    {
      String response = http.getString();

      Serial.println(httpResponseCode);
      Serial.println(response);
    }
    else
    {
      Serial.print("Error on sending GET: ");
      Serial.println(httpResponseCode);
    }
    
    http.end();
  }
  else
  {
      Serial.println("Error in WiFi connection");   
  }
  
  Serial.print("Sent on ");
  Serial.print(fieldName);
  Serial.print(" - value: ");
  Serial.println(value);
}

// -----------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  connectToWifi();
}

void loop() {
  const int liquidSensorOutput = analogRead(liquidSensor);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);


  if (isnan(h) || isnan(t) || isnan(f))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

    if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;   
    http.begin(url_request
      + liquidSensorFieldName + "=" + String(liquidSensorOutput)
      + temperatureSensorFieldName + "=" + String(t));

    int httpResponseCode = http.GET();
    if (httpResponseCode > 0)
    {
      String response = http.getString();

      Serial.println(httpResponseCode);
      Serial.println(response);
    }
    else
    {
      Serial.print("Error on sending GET: ");
      Serial.println(httpResponseCode);
    }
    
    http.end();
  }
  else
  {
      Serial.println("Error in WiFi connection");   
  }
  delay(20000);
}
