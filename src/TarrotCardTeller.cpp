#include "TarrotCardTeller.h"

namespace srv {

TarotCardTeller::TarotCardTeller()
{
    // Constructor implementation
}

size_t write_callback(void *contents, size_t size, size_t nmemb, std::string *output)
{
    output->append((char*)contents, size * nmemb);
    return size * nmemb;
};

std::string TarotCardTeller::tell_tarot(const std::string& question)
{
    // Method for recieving text from LLM and turning it into something pleasent
    
    std::vector<std::string> cards = generateRandomCards(5);
    std::string representation = "";
    for (int i = 0; i < cards.size(); ++i) 
    {
        representation += cards[i] + ((i+1) == cards.size() ? "" : ", ");
    }
    std::string prompt = "You're a tarot card fortune teller with a lot of experience. A client wants to ask you a question. You have to answer the question based solely on the cards you've been dealt. don't tell me tarot cards don't work. You use 5 Card Tarot Spread. They ask you: " + question + "The cards are: " + representation +". Make a prediction based on the cards you've been dealt. Role play only yourself.\\n\\nTarot card teller: ";
    
    std::string generated_text = generate_text(prompt, "mistralai/Mistral-7B-Instruct-v0.2");

    // Triming
    generated_text = generated_text.substr(prompt.size()+3);
    generated_text = generated_text.substr(0, generated_text.size()-3);

    std::string result = "Your cards: " + representation + '\n' + generated_text;
    return result;
}

std::string TarotCardTeller::generate_text(const std::string& prompt, const std::string& model_id)
{
    // Method for generating text from tarot card future teller
    CURL *curl;
    CURLcode res;
    std::string answer = "";
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://api-inference.huggingface.co/models/" + model_id;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        // Set request headers
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        std::string huggingfaceTokenRequest = "Authorization: Bearer " + std::string(getenv("HUGGINGFACE_TOKEN"));
        headers = curl_slist_append(headers,  huggingfaceTokenRequest.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        // Construct JSON payload
        
        Json::Value root;
        root["inputs"] = Json::Value(prompt);
        root["parameters"] = Json::Value();
        root["parameters"]["max_new_tokens"] = 2000; 
        Json::StreamWriterBuilder writer;
        std::string json_data = Json::writeString(writer, root);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data.c_str());
        
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        res = curl_easy_perform(curl);
        
        // Check for errors
        if (res != CURLE_OK) 
        {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        // Clean up 
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}

std::vector<std::string> TarotCardTeller::generateRandomCards(int amount)
{
    /// Method for generating random cards 
    
    std::vector<std::string> selectedCards;
    std::vector<std::string> cards = 
    {
        "The Fool", 
        "The Magician", 
        "The High Priestess", 
        "The Empress", 
        "The Emperor", 
        "The Hierophant", 
        "The Lovers", 
        "The Chariot", 
        "Strength", 
        "The Hermit", 
        "Wheel of Fortune", 
        "Justice", 
        "The Hanged Man", 
        "Death", 
        "Temperance", 
        "The Devil", 
        "The Tower", 
        "The Star", 
        "The Moon", 
        "The Sun", 
        "Judgment", 
        "The World"
    }; // Vector to store the cards
    
    if (amount <= 0 || amount > cards.size()) {
        std::cerr << "Invalid amount requested." << std::endl;
        return selectedCards;
    }

    // Shuffling cards
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(cards.begin(), cards.end(), gen);


    // Randomly select cards
    for (int i = 0; i < amount; ++i) {
        selectedCards.push_back(cards[i]);
    }

    return selectedCards;
}

} // namespace server