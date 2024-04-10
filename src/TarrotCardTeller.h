#ifndef FT_TAROTCARDTELLER_H
#define FT_TAROTCARDTELLER_H

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

#include <curl/curl.h>
#include <jsoncpp/include/json/json.h>

namespace server {

class TarotCardTeller {
private:
    std::string huggingfaceTokenRequest;
public:
    TarotCardTeller();  // Constructor
    ~TarotCardTeller(); // Destructor
    std::string tell_tarot(const std::string& question); // Method to tell tarot

private:

    std::string generate_text(const std::string& prompt, const std::string& model_id); // Method to generate text from tarot card future teller
    std::vector<std::string> generateRandomCards(int amount); // Method to generate random cards
};

} // namespace server

#endif // FT_TAROTCARDTELLER_H