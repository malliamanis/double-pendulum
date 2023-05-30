#include <stdlib.h>

#include "entities/entity.h"

Entity *entity_create_rectangle(EntityType type, float x, float y, float width, float height)
{
	Entity *entity = calloc(1, sizeof(Entity));

	entity->type = type;
	entity->body_type = ENTITY_BODY_RECTANGLE;

	entity->body.rect.x = x;
	entity->body.rect.y = y;
	entity->body.rect.width = width;
	entity->body.rect.height = height;

	entity->color = WHITE;

	return entity;
}

Entity *entity_create_ellipse(EntityType type, float x, float y, float radiusX, float radiusY)
{
	Entity *entity = calloc(1, sizeof(Entity));

	entity->type = type;
	entity->body_type = ENTITY_BODY_ELLIPSE;

	entity->body.ell.x = x;
	entity->body.ell.y = y;
	entity->body.ell.radiusX = radiusX;
	entity->body.ell.radiusY = radiusY;

	entity->color = WHITE;

	return entity;
}

void entity_destroy(Entity *entity)
{
	free(entity);
}
