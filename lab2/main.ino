#include "DHT.h"

#define DHTPIN 8
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  Serial.write("DHTxx test!\n");

  dht.begin();
}

void loop()
{
  delay(2000);

  displayTheDhtStuff();
  displayTheWaterSensorStuff();
  Serial.print("\n");
}

void displayTheDhtStuff()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%  Temperature: ");
  Serial.print(t);
  Serial.print("°C ");
  Serial.print(hic);
  Serial.print("°C ");
}


void displayTheWaterSensorStuff()
{
  int waterSensor = analogRead(A1);
  Serial.print("Water sensor: ");
  Serial.print(waterSensor);
}
