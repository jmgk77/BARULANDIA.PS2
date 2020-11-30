#pragma once

#define DEBUG 1

//#define SKIP_INTRO
//#define SKIP_STARTSCREEN
//#define SKIP_GALLERY
//#define SKIP_MAIN

#define MAX_STRING 2048

#define DRAW_W 384
#define DRAW_H 480

#define MAX_DRAW 10

#define JOYBUTTONS 16

#define GRAPH_EXT ".PNG"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#ifdef PS3
#include <dbglogger.h>
#include <io/pad.h>
#include <ppu-types.h>
#include <sys/process.h>
#include <sysutil/msg.h>
#include <sysutil/sysutil.h>
#endif

#define DATA_PATH ""

#define WIDTH 640
#define HEIGHT 480

#include <bitset>
#include <cmath>
#include <dirent.h>
#include <list>
#include <mikmod.h>
#include <png.h>
#include <queue>
#include <time.h>

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
