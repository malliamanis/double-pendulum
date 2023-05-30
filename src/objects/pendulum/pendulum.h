#ifndef PENDULUM_H
#define PENDULUM_H

#include "objects/pendulum/components/weight.h"

typedef struct {
    Vector2 rod_start;
    float rod_length;
    float angle; // radians
    float angular_vel;
    Weight *weight;
} Pendulum;

Pendulum *pendulum_create(Vector2 rod_start, float rod_length, float angle, float weight_mass);

void pendulum_render(Pendulum *pendulum);

void pendulum_destroy(Pendulum *pendulum);

#endif // PENDULUM_H
