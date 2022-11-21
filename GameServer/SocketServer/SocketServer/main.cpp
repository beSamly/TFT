#include "pch.h"
#include <iostream>

#include "ServerApp.h"

int main()
{
    uptr<ServerApp> serverApplication = make_unique<ServerApp>();

    serverApplication->StartSocketServer();
    serverApplication->StartGameSystem();
    serverApplication->StartMatchSystem();

    return 0;
}