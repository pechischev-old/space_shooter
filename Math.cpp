#include "Math.h"
#include "Config.h"

float Math::CalculationDistance(Vector2f posObject1, Vector2f posObject2) {
	return sqrt((posObject1.x - posObject2.x)*(posObject1.x - posObject2.x) + (posObject1.y - posObject2.y)*(posObject1.y - posObject2.y));
}

Vector2f Math::NormalizeVector(Vector2f posObject1, Vector2f posObject2) {
	Vector2f normalizeVector;
	normalizeVector.x = (posObject1.x - posObject2.x) / CalculationDistance(posObject1, posObject2);
	normalizeVector.y = (posObject1.y - posObject2.y) / CalculationDistance(posObject1, posObject2);
	return normalizeVector;
}

float Math::CalculationRotate(Vector2f posObject1, Vector2f posObject2) {
	return float(atan2((posObject1.y - posObject2.y), (posObject1.x - posObject2.x)) * 180 / M_PI);
}