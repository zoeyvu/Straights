#ifndef DECK_H
#define DECK_H 
#include "cardList.h"
#include <algorithm>
#include <random>
#include <chrono>

class Deck : public CardList {
    public:
    Deck();
    void initial();
    void shuffle(unsigned seed);
};

#endif
