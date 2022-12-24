#include <Arduino.h>
#include "bells.h"

uint8_t bell;

void setup()
{
  Serial.begin(115200);
  Serial.println("Setting up bells!");
  for (bell = 0; bell < NUM_bellS; ++bell)
  {
    pinMode(bells[bell], OUTPUT);
    Serial.print(bell_notes[bell]);
    Serial.print(" ");
  }
  Serial.println(" Done!");
  bell = 0;
}

void loop()
{
  Serial.print("Ringing ");
  Serial.print(bell_notes[bell]);
  Serial.print("! ");
  ringbell(bell++);
  Serial.println("DONE");
  delayMicroseconds(1000 * 1000);
  if (bell >= NUM_bellS)
  {
    Serial.println("Resetting bells!");
    bell = 0;
  }
}