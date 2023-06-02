#ifndef DOUBLE_PENDULUM_H
#define DOUBLE_PENDULUM_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "objects/pendulum/pendulum.h"

typedef struct {
	Vector2 point;
	float alpha;
} TrailSegment;

typedef struct {
	TrailSegment *segments;
	size_t segments_size;
	uint32_t segments_index;
} Trail;

typedef struct {
	Pendulum *pen1;
	Pendulum *pen2;
	Color color;

	bool pause;

	bool hold_pen1;
	bool hold_pen2;

	Trail trail;

	// Vector2 *
} DoublePendulum;

DoublePendulum *double_pendulum_create(Vector2 start, float l1, float l2, float a1, float a2, float m1, float m2, Color color);

void double_pendulum_update(DoublePendulum *dp);
void double_pendulum_tick(DoublePendulum *dp);
void double_pendulum_render(DoublePendulum *dp);

void double_pendulum_destroy(DoublePendulum *dp);

#endif // DOUBLE_PENDULUM_H
