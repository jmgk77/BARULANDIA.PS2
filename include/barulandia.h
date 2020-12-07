#pragma once

//#define DEBUG 1

//#define SKIP_INTRO
//#define SKIP_STARTSCREEN
//#define SKIP_GALLERY
//#define SKIP_MAIN

// #define PRE_CACHE
// #define PRE_CACHE_THREADS 2

#define MAX_STRING 512

#define DATA_PATH ""

#define WIDTH 640
#define HEIGHT 480

#define DRAW_W 384
#define DRAW_H 480

#define MAX_DRAW 10

#define JOYBUTTONS 16

#define GRAPH_EXT ".PNG"

using namespace std;

#define INTRO_INIT 1
#define INTRO_MAIN 2
#define INTRO_END 3
#define START_INIT 4
#define START_MAIN 5
#define START_END 6
#define GALLERY_INIT 7
#define GALLERY_MAIN 8
#define GALLERY_END 9
#define MAIN_INIT 10
#define MAIN_MAIN 11
#define MAIN_END 12
#define FINISHED 13

#include <SDL/SDL.h>
#include <SDL/SDL_events.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_thread.h>
#include <SDL/SDL_ttf.h>

#include <stdio.h>
#include <string.h>

#include <bitset>
#include <cmath>
#include <cstring>
#include <dirent.h>
#include <fcntl.h>
#include <list>
#include <png.h>
#include <queue>
#include <romfs.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unordered_map>

#include "debug.h"
#include "floodfill.h"
#include "memcard.h"
#include "romfs.h"
#include "romfs_help.h"
#include "save.h"
#include "savepng.h"
#include "screen.h"
#include "sdl_help.h"
#include "sound.h"
#include "video.h"

#ifdef PS2
#include <debug.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <hdd-ioctl.h>
#include <iopcontrol.h>
#include <iopheap.h>
#include <kernel.h>
#include <libcdvd.h>
#include <libmc.h>
#include <libpad.h>
#include <libpwroff.h>
#include <limits.h>
#include <loadfile.h>
#include <malloc.h>
#include <math.h>
#include <netman.h>
#include <osd_config.h>
#include <ps2ips.h>
#include <ps2smb.h>
#include <sbv_patches.h>
#include <sifrpc.h>
#include <smem.h>
#include <smod.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tamtypes.h>
#include <unistd.h>
#include <usbhdfsd-common.h>
#endif
