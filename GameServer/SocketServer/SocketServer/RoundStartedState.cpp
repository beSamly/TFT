#include "pch.h"
#include "RoundStartedState.h"

void RoundStartedState::Update(GameHost& gameHost, float deltaTime)
{
    elapsedSec += deltaTime;

    if (elapsedSec > 100)
    {
        // round�� ���� �Ǿ��ٸ� field index ������� �ʵ��� pos�� �̵������شٶ�
    }

    if (elapsedSec > 1000)
    {
        SetEnded();
    }
}
