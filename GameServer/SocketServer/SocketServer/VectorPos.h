#pragma once

class VectorPos
{
public:
	double x;
	double y;
	double z;

public:
	VectorPos() : x(0), y(0), z(0) {};
	VectorPos(double x, double z) : x(x), y(0), z(z) {};
	void SetX(double p_x) {
		x = p_x;
	}

	void SetZ(double p_z) {
		z = p_z;
	}
	double GetX() { return x; }
	double GetZ() { return z; }
};

