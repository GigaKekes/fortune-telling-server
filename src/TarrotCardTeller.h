#ifndef FT_TAROTCARDTELLER_H
#define FT_TAROTCARDTELLER_H

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <regex>

#include <curl/curl.h>
#include <jsoncpp/json/json.h>

namespace srv
{

    class TarotCardTeller
    {
    public:
        TarotCardTeller();            // Constructor
        ~TarotCardTeller() = default; // Destructor

        std::string tell_tarot(const std::string &question); // Method to tell tarot

    private:
        std::string generate_text(const std::string &prompt, const std::string &model_id); // Method to generate text from tarot card future teller
        std::vector<std::string> generateRandomCards(int amount);                          // Method to generate random cards
    };

} // namespace server

#endif // FT_TAROTCARDTELLER_H