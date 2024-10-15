#include <Wire.h>
#include <Adafruit_DRV2605.h>

Adafruit_DRV2605 drv;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  if (!drv.begin()) {
    Serial.println("DRV2605L not detected. Check wiring.");
    while (1);
  }

  Serial.println("DRV2605L connected!");
  drv.selectLibrary(1);  // Use haptic library 1
  drv.setMode(DRV2605_MODE_INTTRIG);  // Internal trigger mode
}

void loop() {
  playComplexEmotion(1);  // correct
  delay(6000);
  playComplexEmotion(2);  // incorrect
  delay(6000);
  playComplexEmotion(3);  // Gentle Encouragement 
  delay(6000);
  playComplexEmotion(4);  //  Calming Presence 
  delay(6000);
}

// Function to play complex emotional feedback
void playComplexEmotion(int emotion) {
  switch (emotion) {
    case 1:  // correct answer
      Serial.println("Correct Answer");
      drv.setWaveform(0, 10);  // Double click - Soft realization of success
      drv.setWaveform(1, 21);  // Fast ramp up - Building excitement
      drv.setWaveform(2, 58);  // Rapid pulses - Energetic celebration
      drv.setWaveform(3, 94);  // Strong buzz - Peak excitement
      drv.setWaveform(4, 13);  // Gentle pulse - Warmth at the end
      drv.setWaveform(5, 0);   // End sequence
      break;

    case 2:  // Incorrect answer
      Serial.println("Incorrect Answer");
      drv.setWaveform(0, 58);  // Quick bursts - Initial agitation
      drv.setWaveform(1, 47);  // Strong buzz - Rising tension
      drv.setWaveform(2, 21);  // Fast ramp - Overwhelmed feeling
      drv.setWaveform(3, 87);  // Long buzz - Lingering frustration
      drv.setWaveform(4, 0);   // End sequence
      break;

    case 3:  // Gentle Encouragement
      Serial.println("Gentle Encouragement");
      drv.setWaveform(0, 10);  // Light tap - Friendly nudge
      drv.setWaveform(1, 12);  // Medium pulse - Gradual support
      drv.setWaveform(2, 21);  // Fast ramp - Building confidence
      drv.setWaveform(3, 10);  // Light tap - Positive reinforcement
      drv.setWaveform(4, 64); //transition hum 1
      drv.setWaveform(5, 68); //transmition hum 5
      drv.setWaveform(6, 0);   // End sequence
      break;

    case 4:  // Calming Presence
      Serial.println("Calming Presence");
      drv.setWaveform(0, 52);  // pusing strong 1
      drv.setWaveform(1, 65);  // transition hum
      drv.setWaveform(2, 61);  // transition click
       drv.setWaveform(3, 9);
        drv.setWaveform(4, 83); //smooth up ramp long 2
      drv.setWaveform(5, 0);   // End sequence
      break;
  }

  drv.go();  // Execute the haptic sequence
}
