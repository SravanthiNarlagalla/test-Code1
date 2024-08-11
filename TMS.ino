#include <LiquidCrystal.h>
#include <DHT.h>

// Pin Definitions
#define TEMP_PIN A0
#define VOLT_PIN A1
#define CURR_PIN A2
#define BUZZER_PIN 3
#define DHT_PIN 2

// LCD pinout
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Constants for sensors
#define DHTTYPE DHT11
DHT dht(DHT_PIN, DHTTYPE);

void setup() {
  lcd.begin(16, 2);           // Start the LCD display
  Serial.begin(9600);         // Start serial communication
  pinMode(BUZZER_PIN, OUTPUT);
  dht.begin();                // Start the humidity sensor
}

void loop() {
  // Read temperature
  float temperature = analogRead(TEMP_PIN) * (5.0 / 1023.0) * 100.0;
  
  // Read voltage
  float voltage = analogRead(VOLT_PIN) * (5.0 / 1023.0) * 100.0;

  // Read current
  float current = analogRead(CURR_PIN) * (5.0 / 1023.0) * 30.0;

  // Read humidity
  float humidity = dht.readHumidity();

  // Display on Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");

  Serial.print("Current: ");
  Serial.print(current);
  Serial.println(" A");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Display on LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Volt: ");
  lcd.print(voltage);
  lcd.print(" V");

  // Alarm condition (e.g., high temperature)
  if (temperature > 75) {     // Change threshold as needed
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(1000);  // Wait for a second before repeating
}
