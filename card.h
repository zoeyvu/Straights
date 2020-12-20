#ifndef CARD_H
#define CARD_H 

#include <string>
#include <iostream>

class Card {
    private:
    std::string cardName;

    public:
    Card(std::string cardName);
    int getRank() const;
    char getSuite() const;
    int getOrderedSuite() const;
    std::string getCardName() const;
    friend bool operator<(const Card &c1, const Card &c2);
};

#endif
