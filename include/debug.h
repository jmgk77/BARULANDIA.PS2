#pragma once

#include "barulandia.h"

#define DBG_IP "192.168.0.30"
#define DBG_PORT "18194"

#ifdef DEBUG
#define dbglogger_init_str(x)
#define dbglogger_stop(x)
#define dbglogger_printf printf
#define dbglogger_printf printf
#define dbglogger_screenshot_tmp(x) /*debug_screenshot()*/
#define dbglogger_failsafe(x)
#else
#define dbglogger_init_str(x)
#define dbglogger_stop(x)
#define dbglogger_printf(...)
#define dbglogger_printf(...)
#define dbglogger_screenshot_tmp(x)
#endif

void debug_keyboard(SDL_KeyboardEvent *key);
void debug_joystick(SDL_Joystick *joystick);
void debug_video();
void debug_format(int tf);
void debug_font(TTF_Font *font);
void debug_audio();
void debug_audio_spec(SDL_AudioSpec *a);
void debug_screenshot();
void debug_audio();
