#ifndef CARDLIST_H
#define CARDLIST_H 

#include "card.h"
#include <vector>

class CardList {
    protected:
    std::vector<Card> listCard;

    public:
    bool isEmpty();
    void display();
    void clear();
    int size();
    bool foundCard(std::string nameCard);
    std::vector<Card>::iterator findCard(std::string nameCard);
    std::vector<Card>::iterator end();
    std::vector<Card>::iterator begin();
    std::string getCard(unsigned int i);
    void deleteCard(std::string nameCard);
    void deleteCard(std::vector<Card>::iterator i);
    void addCard(std::string str);
    void addCardUnordered(std::string str);
};

#endif
