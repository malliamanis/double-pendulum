#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "util/mathutil.h"
#include "graphics/renderer.h"
#include "objects/pendulum/pendulum.h"

#define RADIUS 15.0f

Pendulum *pendulum_create(Vector2 rod_start, float rod_length, float angle, float weight_mass)
{
    Pendulum *pendulum = malloc(sizeof(Pendulum));

    pendulum->rod_start = rod_start;
    pendulum->rod_length = rod_length;

    pendulum->angle = angle;
    pendulum->angular_vel = 0.0f;
    pendulum->angular_acc = 0.0f;

    pendulum->weight = weight_create(RADIUS, weight_mass);

    return pendulum;
}

Vector2 pendulum_get_rod_end(Pendulum *pendulum)
{
    return (Vector2){pendulum->rod_length * sinf(pendulum->angle), pendulum->rod_length * cosf(pendulum->angle)};
}

void pendulum_destroy(Pendulum *pendulum)
{
    weight_destroy(pendulum->weight);
    free(pendulum);
}
