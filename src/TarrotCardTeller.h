#ifndef FT_TAROTCARDTELLER_H
#define FT_TAROTCARDTELLER_H

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

class TarotCardTeller {
private:


public:
    TarotCardTeller();  // Constructor
    ~TarotCardTeller(); // Destructor
    

private:

    std::string generate_text(const std::string& prompt, const std::string& model_id); // Method to generate text from tarot card future teller
    std::string generateRandomCards(int amount); // Method to generate random cards
    
    size_t write_callback(void *contents, size_t size, size_t nmemb, std::string *output) {
    output->append((char*)contents, size * nmemb);
    return size * nmemb;
    };


};

#endif // FT_TAROTCARDTELLER_H