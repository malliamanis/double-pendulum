#include <math.h>
#include <stdlib.h>

#include "app.h"
#include "graphics/renderer.h"
#include "objects/pendulum/pendulum.h"

Pendulum *pendulum_create(Vector2 start, float rod_length, float angle, float weight_mass)
{
    Pendulum *pendulum = malloc(sizeof(Pendulum));

    pendulum->rod_start = start;
    pendulum->rod_length = rod_length;

    pendulum->angle = angle;
    pendulum->angular_vel = 0.0f;

    pendulum->weight = weight_create(25.0f, weight_mass);

    return pendulum;
}

void pendulum_render(Pendulum *pendulum)
{
    Vector2 rod_end = {sinf(pendulum->angle) * pendulum->rod_length, cosf(pendulum->angle) * pendulum->rod_length};

    renderer_render_line(pendulum->rod_start, rod_end, 2.0f, WHITE);
    renderer_render_circle(rod_end.x + pendulum->weight->radius, rod_end.y + pendulum->weight->radius, pendulum->weight->radius, WHITE);
}

void pendulum_destroy(Pendulum *pendulum)
{
    weight_destroy(pendulum->weight);
    free(pendulum);
}
