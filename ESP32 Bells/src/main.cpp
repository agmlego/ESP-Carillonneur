#include <Arduino.h>
#include "bells.h"

uint8_t BELL;

void setup()
{
  Serial.begin(115200);
  Serial.println("Setting up bells!");
  for (BELL = 0; BELL < NUM_BELLS; ++BELL)
  {
    pinMode(bells[BELL], OUTPUT);
    Serial.print(bell_notes[BELL]);
    Serial.print(" ");
  }
  Serial.println(" Done!");
  BELL = 0;
}

void loop()
{
  Serial.print("Ringing ");
  Serial.print(bell_notes[BELL]);
  Serial.print("! ");
  ringBell(BELL++);
  Serial.println("DONE");
  delayMicroseconds(1000 * 1000);
  if (BELL >= NUM_BELLS)
  {
    Serial.println("Resetting bells!");
    BELL = 0;
  }
}