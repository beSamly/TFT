#include "pch.h"
#include "MatchSystem.h"

namespace
{
#define TO_LAMBDA(FUNC) [&](sptr<ICommand> command) { FUNC(command); }
} // namespace

MatchSystem::MatchSystem(sptr<GameSystem> p_gameSystem)
{
    gameSystem = p_gameSystem;
    commandHandler.emplace((int)CommandId::MATCH_REQUEST, TO_LAMBDA(HandleMatchRequestCommand));
}

void MatchSystem::Run()
{
    DWORD intervalTick = 1000; // 1초에 한 번씩

    DWORD nextTickTime = GetTickCount() + intervalTick;
    DWORD prevTickTime = GetTickCount();

    while (true)
    {
        DWORD currentTime = GetTickCount();

        if (currentTime > nextTickTime)
        {
            Update();
        }
    }
}

void MatchSystem::PushCommand(sptr<ICommand> command)
{
    WRITE_LOCK;
    commandQueue.push(command);
}

queue<sptr<ICommand>> MatchSystem::FlushQueue()
{
    WRITE_LOCK;
    queue<sptr<ICommand>> copied(commandQueue);
    return copied;
}

void MatchSystem::ProcessCommand()
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

void MatchSystem::Update() {}

void MatchSystem::HandleMatchRequestCommand(sptr<ICommand> p_command)
{
    sptr<MatchRequestCommand> command = dynamic_pointer_cast<MatchRequestCommand>(p_command);

    if (!command)
    {
    }
}