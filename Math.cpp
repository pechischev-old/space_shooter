#include "Math.h"
#include "Config.h"

using namespace std;

float Math::CalculateDistance(Vector2f posObject1, Vector2f posObject2) {
	return sqrt((posObject1.x - posObject2.x)*(posObject1.x - posObject2.x) + (posObject1.y - posObject2.y)*(posObject1.y - posObject2.y));
}

Vector2f Math::Normalize(Vector2f posObject1, Vector2f posObject2) {
	Vector2f normalizeVector;
	normalizeVector.x = (posObject1.x - posObject2.x) / CalculateDistance(posObject1, posObject2);
	normalizeVector.y = (posObject1.y - posObject2.y) / CalculateDistance(posObject1, posObject2);
	return normalizeVector;
}

float Math::CalculateRotate(Vector2f posObject1, Vector2f posObject2) {
	return float(atan2((posObject1.y - posObject2.y), (posObject1.x - posObject2.x)) * 180 / M_PI);
}

int Math::GetRandomNumerForSection(int begin, int end) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(begin, end);
	return dist(gen);
}