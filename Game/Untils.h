#pragma once
#include <math.h>
#include "Object.h"
struct MathUntils
{
	static float FindDistance(Position p1, Position p2)
	{
		return sqrtf((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
	}
};