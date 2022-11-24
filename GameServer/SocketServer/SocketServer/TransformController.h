#pragma once
#include "Vector3.h"

class TransformController
{
private:
    Vector3 position;

public:
    TransformController(){};
    Vector3 GetPosition();
};
