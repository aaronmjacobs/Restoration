#ifndef AUDIO_H
#define AUDIO_H

#include "../Types.h"

// FMOD
#include "fmod.hpp"
#include "fmod_errors.h"
#include <map>

//remove
#include <cerrno>
#include <iostream>
#include <fstream>
#include <string>

struct Sample {
   FMOD::Sound *sound;
   FMOD::Channel *channel;
   bool loop;
};

class Audio {
private:
   const std::string SOUND_PATH = "data/sounds/";

   FMOD::System *system;
   std::map<std::string, SPtr<Sample>> samples;
   FMOD::ChannelGroup *groupL, *groupE; //loop and effects
   std::string curMusic;

   void ERRCHECK(FMOD_RESULT result);

public:
   /* Initialize Audio System*/
   int systemInit();

   /* Load in a media file. The first loop track loaded will auto start playing */
   void loadSound(const std::string &name, bool loop);

   /* Starts a non-loop sound */
   int signalSound(const std::string &name);

   /* Swaps the running track to sampleNum track (loop tracks only) */
   int swapMusicTrack(const std::string &name);

   /* Edits volume: (1.0 to 0.0). Volume is grouped into effects and loop tracks */
   int setVolume(bool isLoop, float volume);

   /* Clean-up references */
   int cleanUp();
};

#endif
