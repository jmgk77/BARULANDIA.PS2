#pragma once

#define DEBUG 1

//#define SKIP_INTRO
//#define SKIP_STARTSCREEN
//#define SKIP_GALLERY
//#define SKIP_MAIN

#define MAX_STRING 2048

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
#include <SDL/SDL_thread.h>
#include <SDL/SDL_ttf.h>

#include <stdio.h>
#include <string.h>

#include <bitset>
#include <cmath>
#include <cstring>
#include <dirent.h>
#include <list>
#include <mikmod.h>
#include <png.h>
#include <queue>
#include <romfs.h>
#include <time.h>

#include "debug.h"
#include "floodfill.h"
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
#include <errno.h>
#include <iopcontrol.h>
#include <iopheap.h>
#include <kernel.h>
#include <libmc.h>
#include <loadfile.h>
#include <sbv_patches.h>
#include <sifrpc.h>
#include <stdio.h>
#include <stdlib.h>
#include <tamtypes.h>
#endif
