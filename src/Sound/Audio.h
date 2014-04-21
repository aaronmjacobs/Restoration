#ifndef AUDIO_H
#define AUDIO_H

// FMOD
#include "fmod.hpp"
#include "fmod_errors.h"
#include <vector>

#define SAMPLE_JUMP 0
#define SAMPLE_SHOOT 1
#define SAMPLE_WIN 2
#define SAMPLE_LOSE 3
#define SAMPLE_OW 4
#define SAMPLE_MUSIC 5

struct Sample;

class Audio {

   FMOD::System    *system;
   std::vector<Sample> sounds;

   void ERRCHECK(FMOD_RESULT result);

public:
   /* Initialize Audio System*/
   int systemInit();

   /* Load in a media file. Spesificy if it is to loop as well. */
   int loadSound(char* soundFile, bool loop, int sampleNum);

   /* Starts a non-loop sound. Pauses or unpauses a loop sound*/
   int signalSound(int sampleNum);
};

struct Sample {
   FMOD::Sound     *sound;
   FMOD::Channel   *channel = 0;
   bool loop;
};

#endif
