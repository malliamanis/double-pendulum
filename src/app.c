#include <raylib.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "app.h"
#include "graphics/renderer.h"
#include "objects/double_pendulum.h"

static App *init(void);

static void update(App *app);
static void tick(App *app);
static void render(App *app);

static void terminate(App *app);

static App *init(void)
{
	App *app = malloc(sizeof(App));

	app->window = window_init(WIDTH, HEIGHT, TITLE);

	app->double_pendulums = list_create((destructor)double_pendulum_destroy, sizeof(DoublePendulum));

	return app;
}

void app_run(void)
{
	App *app = init();

	const double delta_time = DELTA_TIME;

	const float l1 = 1.05f * METER;
	const float l2 = 1.05f * METER;

	const float a1 = PI;
	const float a2 = 2.0 * PI / 3.0f;

	const float m1 = 1.5f;
	const float m2 = 1.0f;

	for (uint32_t i = 0; i < 1; ++i)
		list_add(app->double_pendulums, double_pendulum_create((Vector2){0.0f, 0.0f}, l1, l2, a1, a2, m1 - i / 10000.0f, m2 - i / 100000.0f, (Color){255 - i, 255 - i * 1.5f, 255 - i * 2.0f, 255}));

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
		DrawFPS(0, 0);
	}

	terminate(app);
}

static void update(App *app)
{
	window_update(app->window);

	for (Node *temp = app->double_pendulums->head; temp != NULL; temp = temp->next)
		double_pendulum_update(temp->data);
}

static void tick(App *app)
{
	for (Node *temp = app->double_pendulums->head; temp != NULL; temp = temp->next)
		double_pendulum_tick(temp->data);
}

static void render(App *app)
{
	BeginDrawing();
	ClearBackground(app->window->background);

	for (Node *temp = app->double_pendulums->head; temp != NULL; temp = temp->next) {
		double_pendulum_render(temp->data);
	}

	EndDrawing();
}

static void terminate(App *app)
{
	list_free(app->double_pendulums);
	window_destroy(app->window);
	free(app);
}
