#pragma once
#include <SFML/Graphics.hpp>

#define _USE_MATH_DEFINES

#include <math.h>

using namespace sf;

struct Math {
	float CalculationDistance(Vector2f posObject1, Vector2f posObject2);
	Vector2f NormalizeVector(Vector2f posObject1, Vector2f posObject2);
	float CalculationRotate(Vector2f posObject1, Vector2f posObject2);
};

static Math mathFunction;