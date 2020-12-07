#include "sdl_help.h"

void PutPixel32_nolock(SDL_Surface *surface, int x, int y, Uint32 color) {
  Uint8 *pixel = (Uint8 *)surface->pixels;
  pixel += (y * surface->pitch) + (x * (surface->format->BytesPerPixel));
  *((Uint32 *)pixel) = color;
}

Uint32 GetPixel32_nolock(SDL_Surface *surface, int x, int y) {
  Uint8 *pixel = (Uint8 *)surface->pixels;
  pixel += (y * surface->pitch) + (x * (surface->format->BytesPerPixel));
  return *((Uint32 *)pixel);
}

// http://www.sdltutorials.com/sdl-scale-surface
SDL_Surface *ScaleSurface(SDL_Surface *Surface, Uint16 Width, Uint16 Height) {
  if (!Surface || !Width || !Height)
    return 0;

  SDL_Surface *_ret = SDL_CreateRGBSurface(
      Surface->flags, Width, Height, Surface->format->BitsPerPixel,
      Surface->format->Rmask, Surface->format->Gmask, Surface->format->Bmask,
      Surface->format->Amask);
  SDL_LockSurface(_ret);

  double _stretch_factor_x =
             (static_cast<double>(Width) / static_cast<double>(Surface->w)),
         _stretch_factor_y =
             (static_cast<double>(Height) / static_cast<double>(Surface->h));

  for (Sint32 y = 0; y < Surface->h; y++)
    for (Sint32 x = 0; x < Surface->w; x++)
      for (Sint32 o_y = 0; o_y < _stretch_factor_y; ++o_y)
        for (Sint32 o_x = 0; o_x < _stretch_factor_x; ++o_x)
          PutPixel32_nolock(_ret,
                            static_cast<Sint32>(_stretch_factor_x * x) + o_x,
                            static_cast<Sint32>(_stretch_factor_y * y) + o_y,
                            GetPixel32_nolock(Surface, x, y));
  SDL_UnlockSurface(_ret);

  return _ret;
}

unordered_map<string, SDL_Surface *> cache;

void scale_show(SDL_Surface *destin, SDL_Surface *source, SDL_Rect *rect) {
  char buf[64];
  if (source) {
    snprintf(buf, 64, "%x.%d.%d", source, rect->w, rect->h);
    string key = buf;

    SDL_Surface *tmp;
    if (cache.find(key) == cache.end()) {
      tmp = ScaleSurface(source, rect->w, rect->h);
      if (tmp) {
        cache[key] = tmp;
      }
      dbglogger_printf("CACHE: (new) %s\n", buf);
    } else {
      tmp = cache[key];
      dbglogger_printf("CACHE: (found) %s\n", buf);
    }
    SDL_BlitSurface(tmp, NULL, destin, rect);
  }
  return;
}

void scale_free() {
  //***
  dbglogger_printf("------------------------------------\n");
  for (unordered_map<string, SDL_Surface *>::iterator itr = cache.begin();
       itr != cache.end(); itr++) {
    dbglogger_printf("CACHED\t%s\t%08x\n", itr->first.c_str(), itr->second);
  }
  unordered_map<string, SDL_Surface *>::iterator itr;
  for (itr = cache.begin(); itr != cache.end(); itr++) {
    SDL_FreeSurface(itr->second);
  }
  cache.clear();
  dbglogger_printf("++++++++++++++++++++++++++++++++++++\n");
  for (unordered_map<string, SDL_Surface *>::iterator itr = cache.begin();
       itr != cache.end(); itr++) {
    dbglogger_printf("CACHED\t%s\t%08x\n", itr->first.c_str(), itr->second);
  }
  dbglogger_printf("------------------------------------\n");
}

#ifdef PRE_CACHE

int volatile max_threads = 0;

int do_cache(void *param) {
  SDL_Surface *img = (SDL_Surface *)param;
  SDL_Rect dstrect;

  if (max_threads == PRE_CACHE_THREADS) {
    sleep(500);
  } else {
    max_threads++;
    dstrect.w = DRAW_W / 2.5;
    dstrect.h = DRAW_H / 2.5;
    scale_show(NULL, img, &dstrect);
    dstrect.w = DRAW_W / 2;
    dstrect.h = DRAW_H / 2;
    scale_show(NULL, img, &dstrect);
    dstrect.w = DRAW_W / 1.5;
    dstrect.h = DRAW_H / 1.5;
    scale_show(NULL, img, &dstrect);
    max_threads--;
  }
  return 0;
}

void cache_scale(SDL_Surface *img) {
  SDL_Thread *thread = SDL_CreateThread(do_cache, (void *)img);

  if (thread == NULL) {
    dbglogger_printf("CACHE -> SDL_CreateThread failed: %s\n", SDL_GetError());
  }
}

#endif
