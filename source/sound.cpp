#include "sound.h"

Mix_Chunk *chunk = 0;

int do_effect_play(void *index) {
  char buf[128];
  snprintf(buf, 128, "%sSOUND%d.WAV", DATA_PATH, index);
  dbglogger_printf("MIX->PLAYING: %s\n", buf);

  Mix_HaltChannel(-1);
  if (chunk) {
    Mix_FreeChunk(chunk);
  }
  chunk = 0;

  chunk = Mix_LoadWAV_RW(f2rw(buf), 0);
  if (chunk == NULL) {
    dbglogger_printf("MIX->Could not open %s: %s\n", buf, Mix_GetError());
    return 0;
  }
  Mix_VolumeChunk(chunk, MIX_MAX_VOLUME);
  if (Mix_PlayChannel(-1, chunk, 0) == -1) {
    dbglogger_printf("MIX->Mix_PlayChannel: %s\n", Mix_GetError());
  }
  return 0;
}

void effect_play(int index) {
  SDL_Thread *thread = SDL_CreateThread(do_effect_play, (void *)index);

  if (thread == NULL) {
    dbglogger_printf("MIX->SDL_CreateThread failed: %s\n", SDL_GetError());
  }
}

void sound_init() {
  SDL_version compile_version;
  SDL_MIXER_VERSION(&compile_version);
  dbglogger_printf("MIX->SDL_mixer version %ld.%ld.%ld\n",
                   compile_version.major, compile_version.minor,
                   compile_version.patch);

  // Mix_Init(0);
  if (Mix_OpenAudio(44100, AUDIO_S16, 1, 4096) < 0) {
    dbglogger_printf("MIX->Couldn't open audio: %s\n", SDL_GetError());
  }
  debug_audio();
}

void sound_end() {
  if (chunk) {
    Mix_FreeChunk(chunk);
  }
  Mix_CloseAudio();
  // Mix_Quit();
}
