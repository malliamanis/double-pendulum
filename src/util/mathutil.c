#include "util/mathutil.h"

Vector2 math_vec2_add(Vector2 v1, Vector2 v2)
{
    return (Vector2){v1.x + v2.x, v2.x + v2.y};
}
