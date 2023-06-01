#include <stdio.h>
#include <stdlib.h>

#include "app.h"
#include "util/mathutil.h"
#include "graphics/renderer.h"

void renderer_render_line(Vector2 start, Vector2 end, float thickness, Color color)
{
	DrawLineEx(math_vec2_add(start, SCREEN_OFFSET), math_vec2_add(end, SCREEN_OFFSET), thickness, color);
}

void renderer_render_circle(Vector2 pos, float radius, Color color)
{
	DrawCircleV(math_vec2_add(pos, SCREEN_OFFSET), radius, color);
}

void renderer_render_point(Vector2 pos, Color color)
{
	// DrawPixelV(math_vec2_add(pos, SCREEN_OFFSET), color);
	if (color.a > 0.0f)
		DrawCircleV(math_vec2_add(pos, SCREEN_OFFSET), 1.5f, color);
}
