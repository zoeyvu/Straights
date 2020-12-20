#include "deck.h"

Deck::Deck() : CardList() {
    std::string rank = "A23456789TJQK";
    std::string suite = "CSHD";
    for (std::string::size_type s = 0; s < suite.size(); s++) {
        for (std::string::size_type r = 0; r < rank.size(); r++) {
                    std::string card = "";
                    card += rank[r];
                    card += suite[s];
                    this->addCardUnordered(card);
        }
    }
}

void Deck::initial() {
    this->clear();
    std::string rank = "A23456789TJQK";
    std::string suite = "CSHD";
    for (std::string::size_type s = 0; s < suite.size(); s++) {
        for (std::string::size_type r = 0; r < rank.size(); r++) {
                    std::string card = "";
                    card += rank[r];
                    card += suite[s];
                    this->addCardUnordered(card);
        }
    }
}

void Deck::shuffle(unsigned seed) {
    // seed = std::chrono::system_clock::now().time_since_epoch().count(); // Comment this out if want to test!
    std::shuffle(listCard.begin(), listCard.end(), std::default_random_engine(seed));
}

