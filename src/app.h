#ifndef GAME_H
#define GAME_H

#include <raylib.h>

#include <stdint.h>

#include "util/list.h"
#include "graphics/window.h"
#include "objects/pendulum/pendulum.h"

#define WIDTH 1280
#define HEIGHT 720
#define TITLE "App"

typedef struct {
	Window *window;
	float delta_time;

	List *double_pendulums;
	Pendulum *pendulum;
} App;

void app_run(void);

#endif // GAME_H
