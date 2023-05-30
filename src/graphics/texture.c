#include <raylib.h>
#include <stdlib.h>

#include "graphics/texture.h"

Texture2D *texture_create(const char *file)
{
	Texture2D *texture = malloc(sizeof(Texture2D));

	*texture = LoadTexture(file);
	if (texture->id <= 0)
		texture = NULL;

	return texture;
}

void texture_destroy(Texture2D *texture)
{
	UnloadTexture(*texture);
}
