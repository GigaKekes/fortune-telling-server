#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <mutex>

#include "Server.h"
#include "TarrotCardTeller.h"

int main()
{
    srv::Server mainServer;
    mainServer.start();

    return 0;
}