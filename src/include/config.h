#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>

#include "pomtime.h"

typedef struct {
	Pomodoro pomodoro;
} Config;

int import_config(Config* config);
void export_config(Config config);

#endif
