#include "TarrotCardTeller.h"

TarotCardTeller::TarotCardTeller()
{
    // Constructor implementation
}

TarotCardTeller::~TarotCardTeller()
{
    // Destructor implementation
}

std::string TarotCardTeller::generate_text(const std::string& question, const std::string& model_id)
{
    // Method implementation for generating text from tarot card future teller

    return "";
}

std::string TarotCardTeller::generateRandomCards(int amount)
{
    // Method implementation for generating random cards
    std::vector<std::string> selectedCards;
    std::vector<std::string> cards = 
    {
        "The Fool (0)", 
        "The Magician (1)", 
        "The High Priestess (2)", 
        "The Empress (3)", 
        "The Emperor (4)", 
        "The Hierophant (5)", 
        "The Lovers (6)", 
        "The Chariot (7)", 
        "Strength (8)", 
        "The Hermit (9)", 
        "Wheel of Fortune (10)", 
        "Justice (11)", 
        "The Hanged Man (12)", 
        "Death (13)", 
        "Temperance (14)", 
        "The Devil (15)", 
        "The Tower (16)", 
        "The Star (17)", 
        "The Moon (18)", 
        "The Sun (19)", 
        "Judgment (20)", 
        "The World (21)"
    }; // Vector to store the cards drawn
    if (amount <= 0 || amount > cards.size()) {
        std::cerr << "Invalid amount requested." << std::endl;
        return "";
    }


    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(cards.begin(), cards.end(), gen);


    // Randomly select cards
    for (int i = 0; i < amount; ++i) {
        selectedCards.push_back(cards[i]);
    }
    std::string representation = "";
    for (int i = 0; i < selectedCards.size(); ++i) {
        representation += selectedCards[i] + ((i+1) == amount ? "" : ", ");
    }

    return representation;
}

