#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"

typedef struct {
	Rectangle rect;
	int state;
	int action;
	Color color;
	Color unselect;
	Color hover;
	Color click;
	char* text;
} Button;


void check_button(Button *button);

#endif
