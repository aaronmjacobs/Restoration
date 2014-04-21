#include "Audio.h"
#include "../engine/FancyAssert.h"

void Audio::ERRCHECK(FMOD_RESULT result)
{
   ASSERT(result == FMOD_OK, "FMod Broke");
}

/*Initialize System*/
int Audio::systemInit() {
   FMOD_RESULT      result;
   unsigned int     version;
   void            *extradriverdata = 0;
   sounds.resize(10);  //TODO: arbitrary, change this

   result = FMOD::System_Create(&system);
   ERRCHECK(result);

   result = system->getVersion(&version);
   ERRCHECK(result);

   if (version < FMOD_VERSION)
   {
      //std::cout << "FMOD lib version " << version << " doesn't match header version " << FMOD_VERSION;
   }

   result = system->init(100, FMOD_INIT_NORMAL | FMOD_INIT_PROFILE_ENABLE, extradriverdata);
   ERRCHECK(result);

   return 0;
}

int Audio::loadSound(char* soundFile, bool loop, int sampleNum) {
   FMOD_RESULT      result;
   
   Sample sample;
   sample.loop = loop;

   result = system->createSound(soundFile, FMOD_2D, 0, &(sample.sound));
   ERRCHECK(result);

   if (loop) {
      result = (sample.sound)->setMode(FMOD_LOOP_NORMAL);
      ERRCHECK(result);
   }

   result = system->playSound(sample.sound, 0, true, &(sample.channel));
   ERRCHECK(result);

   sounds[sampleNum] = sample;

   return 0;
}


int Audio::signalSound(int sampleNum) {
   FMOD_RESULT      result;
   Sample sample = sounds[sampleNum];
   if (sample.loop) { //play/pause music
      bool paused;
      (sample.channel)->getPaused(&paused);
      (sample.channel)->setPaused(!paused);
   }
   else { //play sound
      result = system->playSound(sample.sound, 0, false, &(sample.channel));
      ERRCHECK(result);
   }

   return 0;
}

