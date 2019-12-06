#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>

const int milsToDelay = 500;
const int humidityThreshold = 100;

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27,20,4);
Adafruit_BMP085 bmp;


int liquidSensor = A1;
int relayPin = 10;

void setup()
{
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  
  lcd.init();
  lcd.backlight();

  if (!bmp.begin())
  {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1) {}
  }
}


void loop()
{
  const int liquidSensorOutput = analogRead(liquidSensor);
  const double pressure = bmp.readPressure();
  const bool pumpIsOn = (liquidSensorOutput >= humidityThreshold);


  lcd.clear();
  printHumidity(liquidSensorOutput);
  printPressure(pressure);

  lcd.setCursor(10, 0);
  if (pumpIsOn)
  {
    digitalWrite(relayPin, HIGH);
    Serial.println("ON");
    lcd.print("ON");
  }
  else
  {
    digitalWrite(relayPin, LOW);
    Serial.println("OFF");
    lcd.print("OFF");
  }

  delay(milsToDelay);
}

void printHumidity(int sensorValue)
{
  Serial.print("Liquid sensor: ");
  Serial.print(sensorValue);
  Serial.println("");

  lcd.setCursor(0, 0);
  lcd.print("Liquid: ");
  lcd.print(sensorValue);
}

void printPressure(double pressure)
{
  Serial.print("Pressure: ");
  Serial.print(pressure / 1000);
  Serial.print(" KPa");
  Serial.println("");

  lcd.setCursor(0, 1);
  lcd.print("P: ");
  lcd.print(pressure / 1000);
  lcd.print(" KPa");
}
