#include <raylib.h>

#include <stdio.h>
#include <stdlib.h>

#include "app.h"
#include "graphics/renderer.h"

#define WIDTH 1280
#define HEIGHT 720
#define TITLE "App"

static App *init(void);

static void update(App *app);
static void tick(App *app);
static void render(App *app);

static void terminate(App *app);

static App *init(void)
{
	App *app = malloc(sizeof(App));

	app->window = window_init(WIDTH, HEIGHT, TITLE);
	InitAudioDevice();

	app->double_pendulums = list_create();

	return app;
}

void app_run(void)
{
	App *app = init();

    const double delta_time = 1.0 / 60.0;

    double currentTime = GetTime();
	double newTime;
    double accumulator = 0.0;

    while (!window_should_close())
    {
		update(app);

        newTime = GetTime();

        accumulator += newTime - currentTime;
        currentTime = newTime;

        while (accumulator >= delta_time)
        {
            tick(app);
            accumulator -= delta_time;
        }

        render(app);
    }

	terminate(app);
}

static void update(App *app)
{
	window_update(app->window);
}

static void tick(App *app)
{
}

static void render(App *app)
{
	BeginDrawing();
	ClearBackground(app->window->background);

	EndDrawing();
}

static void terminate(App *app)
{
	CloseAudioDevice();
	window_destroy(app->window);
	list_free(app->double_pendulums);
	free(app);
}
