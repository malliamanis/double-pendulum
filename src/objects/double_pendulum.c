#include <math.h>
#include <stdlib.h>

#include "app.h"
#include "util/mathutil.h"
#include "graphics/renderer.h"
#include "objects/double_pendulum.h"

#define ENABLE_TRAIL 0

#define FONT_SIZE 30

#define G ((float)(9.81f) * METER)

DoublePendulum *double_pendulum_create(Vector2 start, float l1, float l2, float a1, float a2, float m1, float m2, Color color)
{
	DoublePendulum *dp = malloc(sizeof(DoublePendulum));

	dp->pen1 = pendulum_create(start, l1, a1, m1);
	dp->pen2 = pendulum_create(pendulum_get_rod_end(dp->pen1), l2, a2, m2);

	dp->color = color;

	dp->pause = false;

	dp->hold_pen1 = false;
	dp->hold_pen2 = false;

#if ENABLE_TRAIL == 1
	dp->trail = (Trail){malloc(128 * sizeof(Trail)), 128, 0};
#endif

	return dp;
}

void double_pendulum_update(DoublePendulum *dp)
{
	if (IsKeyPressed(KEY_SPACE)) {
		dp->pause = !dp->pause;
	}

	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
		Vector2 mouse_pos = math_vec2_sub(GetMousePosition(), SCREEN_OFFSET);
		Pendulum *pen = NULL;

		if (CheckCollisionPointCircle(mouse_pos, pendulum_get_rod_end(dp->pen1), dp->pen1->weight->radius) || dp->hold_pen1) {
			dp->hold_pen1 = true;
			pen = dp->pen1;
		}
		else if (CheckCollisionPointCircle(mouse_pos, math_vec2_add(pendulum_get_rod_end(dp->pen1), pendulum_get_rod_end(dp->pen2)), dp->pen2->weight->radius) || dp->hold_pen2) {
			dp->hold_pen2 = true;
			pen = dp->pen2;
		}

		if (pen != NULL) {
			if (pen == dp->pen1) {
				dp->pen1->angle = -fmod(atan2f(mouse_pos.y, mouse_pos.x) - 2.0f * PI / 4.0f, 2.0f * PI);
			}
			else {
				mouse_pos = math_vec2_sub(mouse_pos, pendulum_get_rod_end(dp->pen1));
				pen->angle = -fmod(atan2f(mouse_pos.y, mouse_pos.x) - 2.0f * PI / 4.0f, 2.0f * PI);
			}

			dp->pen1->angular_vel = 0.0f;
			dp->pen1->angular_acc = 0.0f;

			dp->pen2->angular_vel = 0.0f;
			dp->pen2->angular_acc = 0.0f;
		}
	}
	else {
		dp->hold_pen1 = false;
		dp->hold_pen2 = false;
	}
}

void double_pendulum_tick(DoublePendulum *dp)
{
#if ENABLE_TRAIL == 1
	if (!dp->pause) {
		if (dp->trail.segments_index + 1 >=dp->trail.segments_size)
			dp->trail.segments = realloc(dp->trail.segments, (dp->trail.segments_size *= 2) * sizeof(Trail));

		dp->trail.segments[dp->trail.segments_index].point = math_vec2_add(pendulum_get_rod_end(dp->pen1), pendulum_get_rod_end(dp->pen2));
		dp->trail.segments[dp->trail.segments_index++].alpha = 1.0f;
	}

	for (uint32_t i = 0; i <dp->trail.segments_index; ++i)
		dp->trail.segments[i].alpha -= 0.0025f;
#endif

	if (dp->pause || dp->hold_pen1 || dp->hold_pen2)
		return;

	// for convenience
	const float l1 = dp->pen1->rod_length;
	const float l2 = dp->pen2->rod_length;

	const float a1 = dp->pen1->angle;
	const float a2 = dp->pen2->angle;

	const float a_v1 = dp->pen1->angular_vel;
	const float a_v2 = dp->pen2->angular_vel;

	const float m1 = dp->pen1->weight->mass;
	const float m2 = dp->pen2->weight->mass;

	const float denominator = (2 * m1 + m2 - m2 * cosf(2 * a1 - 2 * a2));

	dp->pen1->angular_acc = (-G * (2 * m1 + m2) * sinf(a1) - m2 * G * sinf(a1 - 2 * a2) - 2 * sinf(a1 - a2) * m2 * (a_v2*a_v2 * l2 + a_v1*a_v1 * l1 * cosf(a1 - a2))) / (l1 * denominator);
	dp->pen2->angular_acc = (2 * sinf(a1 - a2) * (a_v1*a_v1 * l1 * (m1 + m2) + G * (m1 + m2) * cosf(a1) + a_v2*a_v2 * l2 * m2 * cosf(a1 - a2))) / (l2 * denominator);

	// dp->pen1->angular_vel *= 0.999f;
	// dp->pen2->angular_vel *= 0.999f;

	dp->pen1->angular_vel += dp->pen1->angular_acc * DELTA_TIME;
	dp->pen2->angular_vel += dp->pen2->angular_acc * DELTA_TIME;

	dp->pen1->angle += dp->pen1->angular_vel * DELTA_TIME;
	dp->pen2->angle += dp->pen2->angular_vel * DELTA_TIME;

	// Vector2 pen1_end = pendulum_get_rod_end(dp->pen1);
	// Vector2 pen2_end = math_vec2_add(pen1_end, pendulum_get_rod_end(dp->pen2));
	// printf("%f\n", (G * fabsf(pen1_end.y + SCREEN_OFFSET.y) + G * fabsf(pen2_end.y + SCREEN_OFFSET.y)) + ((1.0f/2.0f) * powf(dp->pen1->angular_vel * dp->pen1->rod_length, 2.0) + (1.0f/2.0f) * powf(dp->pen2->angular_vel * dp->pen2->rod_length, 2.0)));
}

void double_pendulum_render(DoublePendulum *dp)
{
	if (dp->hold_pen1)
		DrawText("HOLDING WEIGHT 1", 5, HEIGHT - FONT_SIZE, FONT_SIZE, WHITE);
	else if (dp->hold_pen2)
		DrawText("HOLDING WEIGHT 2", 5, HEIGHT - FONT_SIZE, FONT_SIZE, WHITE);
	else if (dp->pause)
		DrawText("PAUSE", 5, HEIGHT - FONT_SIZE, FONT_SIZE, WHITE);

	Vector2 pen1_rod_end = pendulum_get_rod_end(dp->pen1);
	Vector2 pen2_rod_end = math_vec2_add(pendulum_get_rod_end(dp->pen2), pen1_rod_end);

#if ENABLE_TRAIL == 1
	for (uint32_t j = 0; j < dp->trail.segments_index; ++j)
		renderer_render_point(dp->trail.segments[j].point, ColorAlpha(dp->color, dp->trail.segments[j].alpha));
#endif

	renderer_render_line(dp->pen1->rod_start, pen1_rod_end, 2.0f, dp->color);
	renderer_render_line(pen1_rod_end, pen2_rod_end, 2.0f, dp->color);

	renderer_render_circle(pen1_rod_end, dp->pen1->weight->radius, dp->color);
	renderer_render_circle(pen2_rod_end, dp->pen2->weight->radius, dp->color);
}

void double_pendulum_destroy(DoublePendulum *dp)
{
	pendulum_destroy(dp->pen1);
	pendulum_destroy(dp->pen2);

#if ENABLE_TRAIL == 1
	free(dp->trail.segments);
#endif

	free(dp);
}
