#pragma once
#include "ClientSession.h"

class ClientSession;

namespace Command
{

enum CommandId
{
    BUY_COMMAND = 1,
    MATCH_REQUEST,
    CREATE_HOST,
    CREATE_DEBUG_MODE_HOST,
};

class ICommand
{
public:
    sptr<ClientSession> client;
    int commandId;

public:
    ICommand(){};
    ICommand(sptr<ClientSession> p_client) : client(p_client){};
    virtual int GetCommandId() { return commandId; };
};

class BuyCommand : public ICommand
{
public:
    BuyCommand(sptr<ClientSession> p_client, int p_invenIndex) : invenIndex(p_invenIndex), ICommand(p_client)
    {
        ICommand::commandId = CommandId::BUY_COMMAND;
    };

public:
    int invenIndex;
};

class MatchRequestCommand : public ICommand
{
public:
    int matchType;

public:
    MatchRequestCommand(sptr<ClientSession> p_client) : ICommand(p_client)
    {
        ICommand::commandId = CommandId::MATCH_REQUEST;
    };
};

class CreateHostCommand : public ICommand
{
public:
    vector<sptr<ClientSession>> clientVec;

public:
    CreateHostCommand(vector<sptr<ClientSession>> p_clientVec) : clientVec(p_clientVec)
    {
        ICommand::commandId = CommandId::CREATE_HOST;
    };
};

class LocateToFieldCommand : public ICommand
{
public:
    int fieldIndex;

public:
    LocateToFieldCommand(sptr<ClientSession> p_client, int p_fieldIndex)
        : fieldIndex(p_fieldIndex), ICommand(p_client){};
};

class LocateToBenchCommand : public ICommand
{
public:
    int benchIndex;

public:
    LocateToBenchCommand(sptr<ClientSession> p_client, int p_benchIndex)
        : benchIndex(p_benchIndex), ICommand(p_client){};
};

class CreateDebugModeHostCommand : public ICommand
{

public:
    CreateDebugModeHostCommand(sptr<ClientSession> p_client) : ICommand(p_client){};
};
} // namespace Command
