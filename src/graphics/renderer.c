#include "app.h"
#include "util/mathutil.h"
#include "graphics/renderer.h"

void renderer_render_line(Vector2 start, Vector2 end, float thickness, Color color)
{
    DrawLineEx(math_vec2_add(start, APP_OFFSET), math_vec2_add(end, APP_OFFSET), thickness, color);
}

// void renderer_render_curve(Vector2 *points, size_t points_size)
// {
// }

void renderer_render_circle(float x, float y, float radius, Color color)
{
    DrawCircle(x + APP_OFFSET.x, y + APP_OFFSET.y, radius, color);
}