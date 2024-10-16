#include <Wire.h>
#include <Adafruit_DRV2605.h>

Adafruit_DRV2605 drv;

int correctStreak = 0;   // Tracks consecutive correct answers
int incorrectStreak = 0; // Tracks consecutive incorrect answers

void setup() {
  Serial.begin(9600);
  Wire.begin();

  if (!drv.begin()) {
    Serial.println("DRV2605L not detected. Check wiring.");
    while (1);
  }

  Serial.println("DRV2605L connected!");
  drv.selectLibrary(1);  
  drv.setMode(DRV2605_MODE_INTTRIG);  
}

void loop() {
  // Simulate the result of an answer (1 for correct, 0 for incorrect)
  int answer = random(0, 2); // Random answer (1: correct, 0: incorrect)
  
  if (answer == 1) {
    handleCorrectAnswer();
  } else {
    handleIncorrectAnswer();
  }

  delay(4000);  // Wait before the next answer
}

// Handle a correct answer
void handleCorrectAnswer() {
  Serial.println("Answer: Correct");

  correctStreak++;  // Increment correct streak
  incorrectStreak = 0;  // Reset incorrect streak

  if (correctStreak >= 3) {
    Serial.println("Celebrating a correct answer streak!");
    playComplexEmotion(1);  // Play celebratory haptic feedback
  } else {
    playComplexEmotion(3);  // Gentle encouragement
  }
}

// Handle an incorrect answer
void handleIncorrectAnswer() {
  Serial.println("Answer: Incorrect");

  incorrectStreak++;  // Increment incorrect streak
  correctStreak = 0;  // Reset correct streak

  if (incorrectStreak >= 3) {
    Serial.println("A streak of incorrect answers...");
    playComplexEmotion(2);  // Strong feedback for incorrect streak
  } else {
    playComplexEmotion(4);  // Calming presence to encourage
  }
}

// Function to play complex emotional feedback
void playComplexEmotion(int emotion) {
  switch (emotion) {
    case 1:  // Celebratory reaction for correct streak
      Serial.println("Correct Streak Reaction");
      drv.setWaveform(0, 10);  // Double click - Success realization
      drv.setWaveform(1, 21);  // Fast ramp - Excitement builds
      drv.setWaveform(2, 58);  // Rapid pulses - Celebration
      drv.setWaveform(3, 94);  // Strong buzz - Peak excitement
      drv.setWaveform(4, 13);  // Gentle pulse - Warm ending
      drv.setWaveform(5, 0);   // End sequence
      break;

    case 2:  // Strong feedback for incorrect streak
      Serial.println("Incorrect Streak Reaction");
      drv.setWaveform(0, 58);  // Quick bursts - Agitation
      drv.setWaveform(1, 47);  // Strong buzz - Tension builds
      drv.setWaveform(2, 21);  // Fast ramp - Feeling overwhelmed
      drv.setWaveform(3, 87);  // Long buzz - Frustration lingers
      drv.setWaveform(4, 0);   // End sequence
      break;

    case 3:  // Gentle encouragement after a correct answer
      Serial.println("Gentle Encouragement");
      drv.setWaveform(0, 10);  // Light tap - Friendly nudge
      drv.setWaveform(1, 12);  // Medium pulse - Gradual support
      drv.setWaveform(2, 21);  // Fast ramp - Building confidence
      drv.setWaveform(3, 10);  // Light tap - Positive reinforcement
      drv.setWaveform(4, 64);  // Transition hum 1
      drv.setWaveform(5, 68);  // Transition hum 5
      drv.setWaveform(6, 0);   // End sequence
      break;

    case 4:  // Calming presence after an incorrect answer
      Serial.println("Calming Presence");
      drv.setWaveform(0, 52);  // Pulsing strong 1
      drv.setWaveform(1, 65);  // Transition hum
      drv.setWaveform(2, 61);  // Transition click
      drv.setWaveform(3, 9);   // Soft pulse
      drv.setWaveform(4, 83);  // Smooth up ramp long 2
      drv.setWaveform(5, 0);   // End sequence
      break;
  }

  drv.go();  // Execute the haptic sequence
}
