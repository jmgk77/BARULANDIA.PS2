#include "save.h"

int do_save_png(void *d) {
  char buf[MAX_STRING];
  time_t rawtime;
  struct tm *t;

  time(&rawtime);
  t = gmtime(&rawtime);

  snprintf(buf, MAX_STRING, "mc0:BARULAND/%02d%02d%02d%02d.PNG", t->tm_mday,
           t->tm_hour, t->tm_min, t->tm_sec);
  dbglogger_printf("THREAD SAVING: %s\n", buf);

  SDL_Rect content;
  content.x = (WIDTH - DRAW_W) / 2;
  content.y = 0;
  content.w = DRAW_W;
  content.h = DRAW_H;

  // avoid lots of casts...
  SDL_Surface *in = (SDL_Surface *)d;
  SDL_Surface *out = SDL_CreateRGBSurface(
      0, content.w, content.h, in->format->BitsPerPixel, in->format->Rmask,
      in->format->Gmask, in->format->Bmask, 0);
  SDL_FillRect(out, NULL, SDL_MapRGBA(in->format, 255, 255, 255, 255));
  SDL_BlitSurface(in, &content, out, NULL);

  SDL_Surface *tmp = SDL_PNGFormatAlpha(out);
  SDL_SavePNG(tmp, buf);
  SDL_FreeSurface(tmp);

  SDL_FreeSurface(out);

  return 0;
}

extern SDL_Surface *screen;

void save_png(SDL_Surface *d) {
  SDL_Thread *thread = SDL_CreateThread(do_save_png, d);

  effect_play(SOUND_CLICK);

  SDL_FillRect(screen, NULL, SDL_MapRGBA(screen->format, 255, 255, 255, 255));
  SDL_Flip(screen);

  if (thread == NULL) {
    dbglogger_printf("SDL_CreateThread failed: %s\n", SDL_GetError());
  }
}
