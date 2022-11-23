#include "pch.h"
#include "RoundStartedState.h"

void RoundStartedState::Update(GameHost& gameHost, float deltaTime)
{
    elapsedSec += deltaTime;

    if (elapsedSec > 100)
    {
        // round가 시작 되었다면 field index 기반으로 필드의 pos로 이동시켜준다랏
    }

    if (elapsedSec > 1000)
    {
        SetEnded();
    }
}
