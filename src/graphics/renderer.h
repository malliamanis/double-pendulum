#ifndef RENDERER_H
#define RENDERER_H

#include <raylib.h>

#define renderer_clear ClearBackground

void renderer_render_line(Vector2 start, Vector2 end, float thickness, Color color);
void renderer_render_circle(Vector2 pos, float radius, Color color);
void renderer_render_point(Vector2 pos, Color color);


#endif // RENDERER_H
