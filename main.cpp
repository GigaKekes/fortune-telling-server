#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <mutex>

#include "src/Server.h"
#include "src/TarrotCardTeller.h"

int main()
{
    server::TarotCardTeller tarotCardTeller;
    std::cout << tarotCardTeller.tell_tarot("What will happen to me in the future?") << std::endl;
    return 0;
}