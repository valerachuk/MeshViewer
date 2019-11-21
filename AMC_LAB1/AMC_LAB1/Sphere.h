#pragma once
#include "Solid.h"
#define _USE_MATH_DEFINES
#include <math.h>

static class Sphere {
	static Vector3 GetVertex(double R, double Th, double Ph);
public:
	static Solid GetSphere(double radius = 100, double rings = 100, double slices = 100, Vector3 origin = Vector3());
};