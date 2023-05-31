#include <math.h>
#include <stdlib.h>

#include "app.h"
#include "util/mathutil.h"
#include "graphics/renderer.h"
#include "objects/double_pendulum.h"

#define ENABLE_TRAIL 1

#define G (9.81f / 75.0f)

DoublePendulum *double_pendulum_create(Vector2 start, float l1, float l2, float a1, float a2, float m1, float m2, Color color)
{
    DoublePendulum *dp = malloc(sizeof(DoublePendulum));

    dp->pen1 = pendulum_create(start, l1, a1, m1);
    dp->pen2 = pendulum_create(pendulum_get_rod_end(dp->pen1), l2, a2, m2);

	dp->color = color;

	dp->trail_size = 8;
	dp->trail = malloc(dp->trail_size * sizeof(Vector2));
	dp->trail_index = 0;

    return dp;
}

void double_pendulum_update(DoublePendulum *dp)
{
#if ENABLE_TRAIL == 1
	if (dp->trail_index + 1 == dp->trail_size)
		dp->trail = realloc(dp->trail, (dp->trail_size *= 2) * sizeof(Vector2));

	dp->trail[dp->trail_index++] = math_vec2_add(math_vec2_add(pendulum_get_rod_end(dp->pen1), pendulum_get_rod_end(dp->pen2)), SCREEN_OFFSET);
#endif

    // for convenience
    const float l1 = dp->pen1->rod_length;
    const float l2 = dp->pen2->rod_length;

    const float a1 = dp->pen1->angle;
    const float a2 = dp->pen2->angle;

    const float a_v1 = dp->pen1->angular_vel;
    const float a_v2 = dp->pen2->angular_vel;

    const float m1 = dp->pen1->weight->mass;
    const float m2 = dp->pen2->weight->mass;

	const float denominator = l1 * (2 * m1 + m2 - m2 * cosf(2 * a1 - 2 * a2));

    dp->pen1->angular_acc = (-1 * G * (2 * m1 + m2) * sinf(a1) - m2 * G * sinf(a1 - 2 * a2) - 2 * sinf(a1 - a2) * m2 * (a_v2*a_v2 * l2 + a_v1*a_v1 * l1 * cosf(a1 - a2))) / denominator;
	dp->pen2->angular_acc = (2 * sinf(a1 - a2) * (a_v1*a_v1 * l1 * (m1 + m2) + G * (m1 + m2) * cosf(a1) + a_v2*a_v2 * l2 * cosf(a1 - a2))) / denominator;

	dp->pen1->angular_vel += dp->pen1->angular_acc;
	dp->pen2->angular_vel += dp->pen2->angular_acc;

    dp->pen1->angle += dp->pen1->angular_vel;
    dp->pen2->angle += dp->pen2->angular_vel;
}

void double_pendulum_render(DoublePendulum *dp)
{
    Vector2 pen1_rod_end = pendulum_get_rod_end(dp->pen1);
    Vector2 pen2_rod_end = math_vec2_add(pendulum_get_rod_end(dp->pen2), pen1_rod_end);

	renderer_render_curve(dp->trail, dp->trail_index, dp->color);

    renderer_render_line(dp->pen1->rod_start, pen1_rod_end, 2.0f, dp->color);
    renderer_render_line(pen1_rod_end, pen2_rod_end, 2.0f, dp->color);

    renderer_render_circle(pen1_rod_end, dp->pen1->weight->radius, dp->color);
    renderer_render_circle(pen2_rod_end, dp->pen2->weight->radius, dp->color);
}

void double_pendulum_destroy(DoublePendulum *dp)
{
    pendulum_destroy(dp->pen1);
    pendulum_destroy(dp->pen2);
    free(dp);
}
