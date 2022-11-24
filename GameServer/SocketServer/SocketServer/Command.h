#pragma once
#include "ClientSession.h"

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
        wptr<ClientSession> client;
        int commandId;

    public:
        ICommand(){};
        ICommand(wptr<ClientSession> p_client) : client(p_client){};
        virtual int GetCommandId() { return commandId; };
    };

    class BuyCommand : public ICommand
    {
    public:
        BuyCommand(wptr<ClientSession> p_client, int p_champUid) : champUid(p_champUid), ICommand(p_client)
        {
            ICommand::commandId = CommandId::BUY_COMMAND;
        };

    public:
        int champUid;
    };

    class MatchRequestCommand : public ICommand
    {
    public:
        int matchType;

    public:
        MatchRequestCommand(wptr<ClientSession> p_client) : ICommand(p_client)
        {
            ICommand::commandId = CommandId::MATCH_REQUEST;
        };
    };

    class CreateHostCommand : public ICommand
    {
    public:
        vector<wptr<ClientSession>> clientVec;

    public:
        CreateHostCommand(vector<wptr<ClientSession>> p_clientVec) : clientVec(p_clientVec)
        {
            ICommand::commandId = CommandId::CREATE_HOST;
        };
    };

    class LocateToFieldCommand : public ICommand
    {
    public:
        int fieldIndex;

    public:
        LocateToFieldCommand(wptr<ClientSession> p_client, int p_fieldIndex)
            : fieldIndex(p_fieldIndex), ICommand(p_client){};
    };

    class LocateToBenchCommand : public ICommand
    {
    public:
        int benchIndex;

    public:
        LocateToBenchCommand(wptr<ClientSession> p_client, int p_benchIndex)
            : benchIndex(p_benchIndex), ICommand(p_client){};
    };

    class CreateDebugModeHostCommand : public ICommand
    {

    public:
        CreateDebugModeHostCommand(wptr<ClientSession> p_client) : ICommand(p_client){};
    };
} // namespace Command
