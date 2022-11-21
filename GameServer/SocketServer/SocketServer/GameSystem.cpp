#include "pch.h"

#include "GameSystem.h"
#include "GameHost.h"

DWORD intervalTick = 1000; // 3�ʿ� �� ����

namespace
{
#define TO_LAMBDA(FUNC) [&](sptr<ICommand> command) { FUNC(command); }
} // namespace

GameSystem::GameSystem()
{
    commandHandler.emplace((int)CommandId::CREATE_DEBUG_MODE_HOST, TO_LAMBDA(HandleCreateDebugModeHost));
}

void GameSystem::Init()
{
    /*GameHost* host1 = new GameHost();
    host1->Init();
    gameHostList.push_back(host1);*/
}

void GameSystem::Run()
{
    DWORD intervalTick = 20; // 50 frame
    DWORD startTime = 0;
    DWORD nextTickTime = GetTickCount() + intervalTick;
    DWORD deltaTime = 0;
    DWORD prevTime = 0;

    while (true)
    {
        DWORD currentTime = GetTickCount();
        if (startTime == 0)
        {
            startTime = currentTime;
        }

        DWORD elapsedMils = currentTime - startTime;
        DWORD elapsedSec = elapsedMils / 1000;
        if (currentTime > nextTickTime)
        {

            deltaTime = currentTime - prevTime;
            prevTime = currentTime;
            nextTickTime += intervalTick;
            cout << "elapsed time is " << elapsedMils / 1000 << " delta time is " << deltaTime << endl;
            Update(elapsedMils / 1000);
        }
    }
}

void GameSystem::Update(float deltaTime)
{
    // GameSystem�� ó���ؾ��� ��Ŷ ���� ó��
    ProcessCommand();
    // Host�� ������Ʈ
    /*for (GameHost* gameHost : gameHostList)
    {
        gameHost->Update(deltaTime);
    }*/
}

queue<sptr<ICommand>> GameSystem::FlushQueue()
{
    WRITE_LOCK;
    queue<sptr<ICommand>> copied(commandQueue);
    return copied;
}

void GameSystem::ProcessCommand()
{
    queue<sptr<ICommand>> copied = FlushQueue();

    while (!copied.empty())
    {
        sptr<ICommand> command = copied.front();
        int commandId = command->GetCommandId();
        if (commandHandler[commandId])
        {
            commandHandler[commandId](command);
        }
        copied.pop();
    }
}

void GameSystem::PushCommand(sptr<ICommand> command)
{
    WRITE_LOCK;
    commandQueue.push(command);
}

void GameSystem::HandleCreateDebugModeHost(sptr<ICommand> p_command)
{
    sptr<CreateDebugModeHostCommand> command = dynamic_pointer_cast<CreateDebugModeHostCommand>(p_command);
}
