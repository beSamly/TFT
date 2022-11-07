#pragma once
#include "VectorPos.h"

class MathUtil
{
public:
	static double GetRadianBetweenTwoPoint(VectorPos v1, VectorPos v2) {
		double radian = atan2(v2.z - v1.z, v2.x - v1.x);
		return radian;
	}

	static double GetAngleBetweenTwoPoint(VectorPos v1, VectorPos v2) {
		double radian = GetRadianBetweenTwoPoint(v1, v2);
		double angle = (radian * 180) / 3.14159265;
		return angle;
	}

	static VectorPos GetDeltaPosFromAngle(VectorPos pos, double radian) {
		double x = pos.x + (1 * cos(radian));
		double z = pos.z + (1 * sin(radian));

		VectorPos deltaPos(x, z);
		return deltaPos;
	}

	static float GetDistanceBetweenTwoPoint(VectorPos a, VectorPos b) {
		return sqrt(pow(a.x - b.x, 2) + pow(a.z - b.z, 2));
	}
};

