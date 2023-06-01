#ifndef WEIGHT_H
#define WEIGHT_H

#include <raylib.h>

typedef struct {
	// Vector2 position;
	float radius;
	float mass;
} Weight;

Weight *weight_create(float radius, float mass);
void weight_destroy(Weight *weight);

#endif // WEIGHT_H
