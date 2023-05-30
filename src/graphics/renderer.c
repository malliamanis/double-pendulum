#include <raylib.h>

#include "graphics/renderer.h"

void renderer_clear(Color color)
{
	ClearBackground(color);
}

void renderer_render_entity(Entity *entity)
{
	if (ENTITY_BODY_RECTANGLE)
		DrawRectangleRec(entity->body.rect, entity->color);
	else
		DrawEllipse(entity->body.ell.x, entity->body.ell.y, entity->body.ell.radiusX, entity->body.ell.radiusX, entity->color);
}
