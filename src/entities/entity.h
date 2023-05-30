#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>

#include <stdint.h>
#include <stddef.h>

typedef enum {
	ENTITY_ROD,
	ENTITY_WEIGHT
} EntityType;

typedef enum {
	ENTITY_BODY_RECTANGLE,
	ENTITY_BODY_ELLIPSE
} EntityBodyType;

typedef struct {
	float x, y; // Center position;
	float radiusX, radiusY;
} Ellipse;

typedef union {
	Rectangle rect;
	Ellipse ell;
} Body;

typedef struct {
	EntityType type;
	EntityBodyType body_type;

	Body body;
	Vector2 velocity;
	Vector2 acceleration;
	Color color;
} Entity;

Entity *entity_create_rectangle(EntityType type, float x, float y, float width, float height);
Entity *entity_create_ellipse(EntityType type, float x, float y, float radiusX, float radiusY);
void entity_destroy(Entity *entity);

#endif // ENTITY_H
