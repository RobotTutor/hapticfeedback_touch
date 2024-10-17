#include <CapacitiveSensor.h>

// Swap pins if needed: (send pin, receive pin)
CapacitiveSensor capSensor = CapacitiveSensor(4, 2);  // Try swapping pins

void setup() {
  Serial.begin(9600);  // Start serial communication
  capSensor.set_CS_AutocaL_Millis(0xFFFFFFFF);  // Disable auto-calibration
}

void loop() {
  long sensorValue = capSensor.capacitiveSensor(10);  // 10 samples

  // Check for errors
  if (sensorValue == -2) {
    Serial.println("Error: Check wiring or try adjusting sample size.");
  } else {
    Serial.println(sensorValue);  // Print the sensor value

    // Check if touch is detected
    if (sensorValue > 500) {
      Serial.println("Touch detected!");
    }
  }

  delay(100);  // Delay to avoid flooding the serial monitor
}
