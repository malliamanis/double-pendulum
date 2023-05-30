#include "app.h"
#include "util/mathutil.h"
#include "graphics/renderer.h"

#define SCREEN_OFFSET (Vector2){WIDTH / 2.0f, HEIGHT / 2.0f}

void renderer_render_line(Vector2 start, Vector2 end, float thickness, Color color)
{
    DrawLineEx(math_vec2_add(start, SCREEN_OFFSET), math_vec2_add(end, SCREEN_OFFSET), thickness, color);
}

// void renderer_render_curve(Vector2 *points, size_t points_size)
// {
// }

void renderer_render_circle(Vector2 pos, float radius, Color color)
{
    DrawCircleV(math_vec2_add(pos, SCREEN_OFFSET), radius, color);
}
