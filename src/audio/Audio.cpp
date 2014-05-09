#include "Audio.h"
#include "../FancyAssert.h"

void Audio::ERRCHECK(FMOD_RESULT result) {
   ASSERT(result == FMOD_OK, "FMod Broke");
}

void Audio::systemInit() {
   FMOD_RESULT result;
   unsigned int version;

   result = FMOD::System_Create(&system);
   ERRCHECK(result);

   result = system->getVersion(&version);
   ERRCHECK(result);

   ASSERT(version >= FMOD_VERSION, "FMod Version Error");

   result = system->init(100, FMOD_INIT_NORMAL | FMOD_INIT_PROFILE_ENABLE, NULL);
   ERRCHECK(result);

   result = system->createChannelGroup("Group Loop", &groupL);
   ERRCHECK(result);
   result = system->createChannelGroup("Group Effects", &groupE);
   ERRCHECK(result);
}

void Audio::loadSound(const std::string &name, bool loop) {
   ASSERT(samples.find(name) == samples.end(), "Sound already loaded: %s", name.c_str());

   FMOD_RESULT result;
   static bool musicLoaded = false;
   SPtr<Sample> sample = std::make_shared<Sample>();
   sample->loop = loop;

   std::string filePath = SOUND_PATH + name;
   result = system->createSound(filePath.c_str(), FMOD_2D, 0, &(sample->sound));
   ERRCHECK(result);

   if (loop) {
      result = (sample->sound)->setMode(FMOD_LOOP_NORMAL);
      ERRCHECK(result);
      result = system->playSound(sample->sound, groupL, false, &(sample->channel));
      ERRCHECK(result);

      if (!musicLoaded) {
         result = (sample->channel)->setMute(false);
         ERRCHECK(result);
         curMusic = name;
         musicLoaded = true;
      }
      else {
         result = (sample->channel)->setMute(true);
         ERRCHECK(result);
      }
      result = (sample->channel)->setChannelGroup(groupL);
   }
   else {
      result = system->playSound(sample->sound, groupE, true, &(sample->channel));
      ERRCHECK(result);
      result = (sample->channel)->setChannelGroup(groupE);
   }

   ERRCHECK(result);
   samples[name] = sample;
}

void Audio::signalSound(const std::string &name) {
   ASSERT(samples.find(name) != samples.end(), "Sound not loaded: %s", name.c_str());

   FMOD_RESULT      result;
   SPtr<Sample> sample = samples[name];
   if (!(sample->loop)) { //play sound
      result = system->playSound(sample->sound, groupE, false, &(sample->channel));
      ERRCHECK(result);
   }
   system->update();
}

void Audio::swapMusicTrack(const std::string &name) {
   if (name != curMusic) {
      FMOD_RESULT      result;
      SPtr<Sample> sample = samples[curMusic];
      if (sample->loop) {
         bool mute;
         result = (sample->channel)->getMute(&mute);
         result = (sample->channel)->setMute(!mute);
         ERRCHECK(result);
      }

      sample = samples[name];
      if (sample->loop) {
         bool mute;
         result = (sample->channel)->getMute(&mute);
         result = (sample->channel)->setMute(!mute);
         ERRCHECK(result);
      }
      curMusic = name;
      system->update();
   }
}

void Audio::setVolume(bool isLoop, float volume) {
   FMOD_RESULT      result;
   if (isLoop) {
      result = (groupL)->setVolume(volume);
      ERRCHECK(result);
   }
   else {
      result = (groupE)->setVolume(volume);
      ERRCHECK(result);
   }

   system->update();
}

/* Assumes NUM_SOUNDS entries in sounds*/
void Audio::cleanUp() {
   FMOD_RESULT      result;

   for (std::pair<const std::string, SPtr<Sample>> sample : samples) {
      result = sample.second->sound->release();
      ERRCHECK(result);
   }
   samples.clear();

   result = system->close();
   ERRCHECK(result);
   result = system->release();
   ERRCHECK(result);
}
