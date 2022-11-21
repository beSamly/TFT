#pragma once
#include "MathUtil.h"
#include "VectorPos.h"

class MoveEntity
{
private:
    VectorPos position;
    VectorPos targetPosition;

public:
    MoveEntity();
    MoveEntity(VectorPos pVectorPos);
    void SetPosition(double x, double z);
    VectorPos GetPosition() { return position; };

protected:
    void Update(float deltaTime);

public:
    void SetTarget(double x, double z);
    void SetTarget(VectorPos v);
    void MoveToNextPos();
    bool IsArrived();
};
