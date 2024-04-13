#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <mutex>

#include "Server.h"
#include "TarrotCardTeller.h"

int main()
{
    server::TarotCardTeller tarotCardTeller;
    std::cout << tarotCardTeller.tell_tarot("how sholud i study for a calculus colloquium?") << std::endl;
    return 0;
}