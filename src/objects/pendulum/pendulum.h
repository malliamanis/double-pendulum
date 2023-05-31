#ifndef PENDULUM_H
#define PENDULUM_H

#include "objects/pendulum/components/weight.h"

typedef struct {
    Vector2 rod_start;
    float rod_length;
    float angle; // radians
    float angular_vel;
    float angular_acc;
    Weight *weight;
} Pendulum;

Pendulum *pendulum_create(Vector2 rod_start, float rod_length, float angle, float weight_mass);

Vector2 pendulum_get_rod_end(Pendulum *pendulum);

void pendulum_destroy(Pendulum *pendulum);

#endif // PENDULUM_H
