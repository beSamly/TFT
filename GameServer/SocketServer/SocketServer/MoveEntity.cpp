#include "pch.h"
#include "MoveEntity.h"

MoveEntity::MoveEntity()
{
    position.x = 0;
    position.z = 0;
}

MoveEntity::MoveEntity(VectorPos pVectorPos)
{
    position.x = pVectorPos.x;
    position.z = pVectorPos.z;
}

void MoveEntity::Update(float deltaTime) { MoveToNextPos(); }

void MoveEntity::SetPosition(double x, double z)
{
    position.SetX(x);
    position.SetZ(z);
}

void MoveEntity::SetTarget(double x, double z)
{
    targetPosition.SetX(x);
    targetPosition.SetZ(z);
}

void MoveEntity::SetTarget(VectorPos v)
{
    targetPosition.SetX(v.x);
    targetPosition.SetZ(v.z);
}

void MoveEntity::MoveToNextPos()
{
    double radian = MathUtil::GetRadianBetweenTwoPoint(position, targetPosition);
    VectorPos deltaPos = MathUtil::GetDeltaPosFromAngle(position, radian);
    cout << "current position : " << position.GetX() << " " << position.GetZ() << endl;
    position.x = deltaPos.x;
    position.z = deltaPos.z;

    // Log->Info("After add x={} z={} ", position.GetX(), position.GetZ());
    cout << "After add : " << position.GetX() << " " << position.GetZ() << endl;
    if (IsArrived())
    {
        cout << " arrived ! " << endl;
    }
}

bool MoveEntity::IsArrived()
{
    if ((int)position.GetX() > (int)targetPosition.GetX() && (int)position.GetZ() > (int)targetPosition.GetZ())
    {
        return true;
    }
    return false;
}
