#include "util/mathutil.h"

Vector2 math_vec2_add_f(Vector2 v, float f)
{
	return (Vector2){v.x + f, v.y + f};
}

Vector2 math_vec2_add(Vector2 v1, Vector2 v2)
{
	return (Vector2){v1.x + v2.x, v1.y + v2.y};
}

Vector2 math_vec2_sub(Vector2 v1, Vector2 v2)
{
	return (Vector2){v1.x - v2.x, v1.y - v2.y};
}
