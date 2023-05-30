#ifndef TEXTURE_H
#define TEXTURE_H

#include <raylib.h>

Texture2D *texture_create(const char *image_file);
void texture_destroy(Texture2D *texture);

#endif // TEXTURE_H
