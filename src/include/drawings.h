#ifndef DRAWINGS_H
#define DRAWINGS_H

#include <stdarg.h>

#include "button.h"
#include "pomtime.h"

#include "raylib.h"

void draw_centered_text(Font font, const char* text, float font_size, float spacing, Color tint);
void draw_button(Button button, Font font, float font_size, float spacing, Color tint);
void draw_timer_screen(Button settings, Button control, Time time, Pomodoro pomodoro, char* percentage);
void draw_settings_screen(Button settings, Button increment, Button decrement, Button up, Button down, Button save, Pomodoro* pomodoro);

#endif
