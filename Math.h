#pragma once
#include <SFML/Graphics.hpp>

#define _USE_MATH_DEFINES

#include <math.h>
#include <random> 
#include <assert.h>

using namespace sf;

struct Math {
	static float CalculateDistance(Vector2f posObject1, Vector2f posObject2);
	static Vector2f Normalize(Vector2f posObject1, Vector2f posObject2);
	static float CalculateRotate(Vector2f posObject1, Vector2f posObject2);
	static int GetRandomNumerForSection(int begin, int end);
};
