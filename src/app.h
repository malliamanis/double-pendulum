#ifndef GAME_H
#define GAME_H

#include <raylib.h>

#include <stdint.h>

#include "util/list.h"
#include "graphics/window.h"

#define WIDTH 1280
#define HEIGHT 720
#define TITLE "App"

typedef struct {
	Window *window;
	float delta_time;

	List *double_pendulums;
} App;

void app_run(void);

#endif // GAME_H
