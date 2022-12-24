#ifndef __BELLS__
#define __BELLS__

#define NUM_BELLS 12
const uint8_t bells[] = {16, 17, 18, 19, 21, 22, 33, 32, 27, 26, 25, 23};
const char *bell_notes[] = {"E7", "C7", "B6", "A#6", "A6", "G#6", "C6", "C#6", "D6", "B5/C6", "G#5", "F#6"};

const uint32_t STRIKE_DURATION = 25 * 1000;

void ringBell(uint8_t bell)
{
    digitalWrite(bells[bell], HIGH);
    delayMicroseconds(STRIKE_DURATION);
    digitalWrite(bells[bell], LOW);
}

#endif