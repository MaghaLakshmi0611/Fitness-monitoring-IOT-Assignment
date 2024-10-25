#include <LiquidCrystal.h> // Include the library for LCD

// Define pin connections
#define TMP36_PIN A0         // Temperature sensor pin
#define LDR_PIN A1           // Photoresistor pin (simulated oxygen level)
#define HEART_RATE_PIN A2    // Simulated heart rate pin (potentiometer)
#define BUZZER_PIN 5         // Buzzer pin
#define TRIG_PIN 6           // HC-SR04 Trigger pin
#define ECHO_PIN 7           // HC-SR04 Echo pin

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Modify pins as needed for your LCD

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  lcd.begin(16, 2); // Set up the LCD's number of columns and rows
  lcd.print("Fitness Monitor");
}

void loop() {
  // Measure distance using HC-SR04
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW); // Wait for a second
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); // Send a 10us pulse
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH); // Read the echo time
  distance = (duration * 0.034) / 2; // Calculate distance in cm

  // Read body temperature
  float tempVoltage = analogRead(TMP36_PIN);
  float temperature = (tempVoltage * 5.0 * 100.0) / 1024.0;

  // Read oxygen saturation (simulated with LDR)
  int oxygenLevel = analogRead(LDR_PIN);
  
  // Simulate heart rate
  int heartRate = analogRead(HEART_RATE_PIN);
  
  // Print values to Serial Monitor
  Serial.print("Body Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");
  
  Serial.print("Simulated Heart Rate: ");
  Serial.println(heartRate);
  
  Serial.print("Oxygen Level: ");
  Serial.println(oxygenLevel);
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Display values on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(temperature);
  lcd.setCursor(0, 1);
  lcd.print("Dist:");
  lcd.print(distance);
  
  // Buzzer Alert for High Body Temperature
  if (temperature > 37.5) { // Alert if temperature is above normal
      digitalWrite(BUZZER_PIN, HIGH); // Turn on buzzer
  } else {
      digitalWrite(BUZZER_PIN, LOW); // Turn off buzzer
  }

  delay(2000); // Wait before the next reading
}
