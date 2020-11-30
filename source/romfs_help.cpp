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

// mikmod mmio.c parts

typedef struct MMEMREADER {
  MREADER core;
  const void *buffer;
  long len;
  long pos;
} MMEMREADER;

void _mm_delete_mem_reader(MREADER *reader) { MikMod_free(reader); }

static BOOL _mm_MemReader_Eof(MREADER *reader) {
  MMEMREADER *mr = (MMEMREADER *)reader;
  if (!mr)
    return 1;
  if (mr->pos >= mr->len)
    return 1;
  return 0;
}

static BOOL _mm_MemReader_Read(MREADER *reader, void *ptr, size_t size) {
  unsigned char *d;
  const unsigned char *s;
  MMEMREADER *mr;
  long siz;
  BOOL ret;

  if (!reader || !size || (size > (size_t)LONG_MAX))
    return 0;

  mr = (MMEMREADER *)reader;
  siz = (long)size;
  if (mr->pos >= mr->len)
    return 0; /* @ eof */
  if (mr->pos + siz > mr->len) {
    siz = mr->len - mr->pos;
    ret = 0; /* not enough remaining bytes */
  } else {
    ret = 1;
  }

  s = (const unsigned char *)mr->buffer;
  s += mr->pos;
  mr->pos += siz;
  d = (unsigned char *)ptr;

  while (siz) {
    *d++ = *s++;
    siz--;
  }

  return ret;
}

static int _mm_MemReader_Get(MREADER *reader) {
  MMEMREADER *mr;
  int c;

  mr = (MMEMREADER *)reader;
  if (mr->pos >= mr->len)
    return EOF;
  c = ((const unsigned char *)mr->buffer)[mr->pos];
  mr->pos++;

  return c;
}

static int _mm_MemReader_Seek(MREADER *reader, long offset, int whence) {
  MMEMREADER *mr;

  if (!reader)
    return -1;
  mr = (MMEMREADER *)reader;
  switch (whence) {
  case SEEK_CUR:
    mr->pos += offset;
    break;
  case SEEK_SET:
    mr->pos = reader->iobase + offset;
    break;
  case SEEK_END:
    mr->pos = mr->len + offset;
    break;
  default: /* invalid */
    return -1;
  }
  if (mr->pos < reader->iobase) {
    mr->pos = mr->core.iobase;
    return -1;
  }
  if (mr->pos > mr->len) {
    mr->pos = mr->len;
  }
  return 0;
}

static long _mm_MemReader_Tell(MREADER *reader) {
  if (reader) {
    return ((MMEMREADER *)reader)->pos - reader->iobase;
  }
  return 0;
}

MREADER *_mm_new_mem_reader(const void *buffer, long len) {
  MMEMREADER *reader = (MMEMREADER *)MikMod_calloc(1, sizeof(MMEMREADER));
  if (reader) {
    reader->core.Eof = &_mm_MemReader_Eof;
    reader->core.Read = &_mm_MemReader_Read;
    reader->core.Get = &_mm_MemReader_Get;
    reader->core.Seek = &_mm_MemReader_Seek;
    reader->core.Tell = &_mm_MemReader_Tell;
    reader->buffer = buffer;
    reader->len = len;
    reader->pos = 0;
  }
  return (MREADER *)reader;
}

/*========== Memory Reader */

MREADER *f2mr(char *src) {
  void *ptr = 0;
  int size = 0;
  romdisk_find(src, &ptr, &size);
  dbglogger_printf("f2mr -> %s\t%x\t%d\n", src, ptr, size);
  return _mm_new_mem_reader(ptr, size);
}