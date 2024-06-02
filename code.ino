#define BLYNK_TEMPLATE_ID "TMPL3e8CyBq9l"
#define BLYNK_TEMPLATE_NAME "Temperature and Humidity Sensor"
#define BLYNK_AUTH_TOKEN "cuyVCEpjZG5uXJ5nQcssAgIpdzNaQGqj"
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

int LED_PIN = 5;
DHT dht(2, DHT11);

BlynkTimer timer;

void sendSensor()
{
  int value = analogRead(4);
  value = map(value, 400, 1023, 100, 0);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (t > 20 && h > 60) { 
    digitalWrite(LED_PIN, HIGH);  // Turn ON the LED
  } else {
    digitalWrite(LED_PIN, LOW);   // Turn OFF the LED
  }

  Blynk.virtualWrite(V4, digitalRead(LED_PIN));
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V2, value);

  Serial.print("Soil Moisture: ");
  Serial.println(value);
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print("    Humidity: ");
  Serial.println(h);
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, "rpi", "Neelsg@6586");

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  dht.begin();
  delay(3000);
  timer.setInterval(100L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}

BLYNK_WRITE(V4)
{
  int value = param.asInt();
}