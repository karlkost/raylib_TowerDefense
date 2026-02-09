#pragma once

#include "raylib.h"
#include "raymath.h"

// Check collision for a line to see if it intersects with a circle
bool CheckCollisionLineCircle(Vector2 lineStart, Vector2 lineEnd, Vector2 circleCenter, float circleSize) {
	// vector projection to get closest point on the line
	Vector2 one = Vector2Subtract(lineEnd, lineStart);
	Vector2 two = Vector2Subtract(circleCenter, lineStart);

	float distanceAlongLine = Vector2DotProduct(one, two) / Vector2DotProduct(one, one);
	distanceAlongLine = Clamp(distanceAlongLine, 0.0f, 1.0f);

	Vector2 pointOnLine = Vector2Add(lineStart, Vector2Scale(one, distanceAlongLine));
	
	// using that point on the line check if it collides with the circle
	return Vector2DistanceSqr(pointOnLine, circleCenter) <= circleSize * circleSize;
}