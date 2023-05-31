#ifndef DOUBLE_PENDULUM_H
#define DOUBLE_PENDULUM_H

#include <stddef.h>
#include <stdint.h>

#include "objects/pendulum/pendulum.h"

typedef struct {
    Pendulum *pen1;
    Pendulum *pen2;
    Color color;

    Vector2 *trail;
    uint32_t trail_index;
    size_t trail_size;
} DoublePendulum;

DoublePendulum *double_pendulum_create(Vector2 start, float l1, float l2, float a1, float a2, float m1, float m2, Color color);

void double_pendulum_update(DoublePendulum *dp);
void double_pendulum_render(DoublePendulum *dp);

void double_pendulum_destroy(DoublePendulum *dp);

#endif // DOUBLE_PENDULUM_H
