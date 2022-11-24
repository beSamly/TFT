#pragma once

class Vector3
{
public:
    float x;
    float y;
    float z;

public:
    Vector3() : x(0), y(0), z(0) {};
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {};
    void SetX(float p_x) { x = p_x; }

    void SetZ(float p_z) { z = p_z; }
    float GetX() { return x; }
    float GetZ() { return z; }
};
