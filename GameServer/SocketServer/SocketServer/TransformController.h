#pragma once
#include "Vector3.h"

class TransformController
{
private:
    Vector3 position;
    Vector3 targetPosition;

public:
    TransformController() {};
    Vector3 GetPosition();
};
