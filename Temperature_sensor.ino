#include <elapsedMillis.h>

#define sensorPin A0

elapsedMillis temperatureTimer;
elapsedMillis ledBlinkTimer;

bool ledOn = false;
unsigned long ledBlinkInterval = 500; // Initial LED blink interval in milliseconds

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  if (temperatureTimer >= 1000)
  {
    temperatureTimer = 0;

    int reading = analogRead(sensorPin);
    float voltage = reading * (5.0 / 1024.0);
    float temperatureC = voltage * 100;

    Serial.print("Temperature:");
    Serial.print(temperatureC);
    Serial.print("\xC2\xB0");
    Serial.print("C ");
    Serial.println(".");

    if (temperatureC < 30)
    {
      ledBlinkInterval = 250; // Set the LED blink interval to 250 ms if temperature is below 30°C
    }
    else
    {
      ledBlinkInterval = 500; // Set the LED blink interval to 500 ms if temperature is 30°C or higher
    }
  }

  if (ledBlinkTimer >= ledBlinkInterval) {
    ledBlinkTimer = 0;
    ledOn = !ledOn;
    digitalWrite(LED_BUILTIN, ledOn ? HIGH : LOW);
  }
}
