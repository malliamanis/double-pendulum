#include <stdlib.h>

#include "app.h"
#include "util/mathutil.h"
#include "graphics/renderer.h"

#define SCREEN_OFFSET (Vector2){WIDTH / 2.0f, HEIGHT / 3.5f}

void renderer_render_line(Vector2 start, Vector2 end, float thickness, Color color)
{
    DrawLineEx(math_vec2_add(start, SCREEN_OFFSET), math_vec2_add(end, SCREEN_OFFSET), thickness, color);
}

void renderer_render_curve(Vector2 *points, size_t points_size)
{
    for (size_t i = 0; i < points_size; ++i)
        points[i] = math_vec2_add(points[i], SCREEN_OFFSET);

    DrawLineStrip(points, points_size, BLUE);
}

void renderer_render_circle(Vector2 pos, float radius, Color color)
{
    DrawCircleV(math_vec2_add(pos, SCREEN_OFFSET), radius, color);
}
