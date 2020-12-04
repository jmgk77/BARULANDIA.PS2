#include "romfs_help.h"

SDL_RWops *f2rw(char *src) {
  void *ptr = 0;
  int size = 0;
  romdisk_find(src, &ptr, &size);
  dbglogger_printf("f2rw -> %s\t%x\t%d\n", src, ptr, size);
  SDL_RWops *rw = SDL_RWFromMem(ptr, size);
  if (rw == NULL) {
    dbglogger_printf("SDL_RWFromMem: %s", SDL_GetError());
  }
  return rw;
}
