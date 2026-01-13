#ifndef POMODORO_H
#define POMODORO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "button.h"
#include "drawings.h"
#include "pomtime.h"
#include "config.h"

#include "raylib.h"

typedef struct {
	int current_width;
	int current_height;
	int min_width;
	int min_height;
	int max_width;
	int max_height;
} WindowDimensions;

#endif


