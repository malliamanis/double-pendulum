#ifndef RENDERER_H
#define RENDERER_H

#include <raylib.h>

#include <stddef.h>

#define renderer_clear ClearBackground

void renderer_render_line(Vector2 start, Vector2 end, float thickness, Color color);
// void renderer_render_curve(Vector2 *points, size_t points_size);
void renderer_render_circle(Vector2 pos, float radius, Color color);


#endif // RENDERER_H
