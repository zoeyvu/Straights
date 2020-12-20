#include "card.h"

Card::Card(std::string cardName)
    : cardName{cardName}
    {}

int Card::getRank() const {
    char rankCard = cardName[0];
    if (rankCard == 'A') {
        return 1;
    } else if (rankCard == '2') {
        return 2;
    } else if (rankCard == '3') {
        return 3;
    } else if (rankCard == '4') {
        return 4;
    } else if (rankCard == '5') {
        return 5;
    } else if (rankCard == '6') {
        return 6;
    } else if (rankCard == '7') {
        return 7;
    } else if (rankCard == '8') {
        return 8;
    } else if (rankCard == '9') {
        return 9;
    } else if (rankCard == 'T') {
        return 10;
    } else if (rankCard == 'J') {
        return 11;
    } else if (rankCard == 'Q') {
        return 12;
    } else if (rankCard == 'K') {
        return 13;
    }
    return -10;
}

char Card::getSuite() const {
    return cardName[1];
}

int Card::getOrderedSuite() const {
    char suite = this->getSuite();
    // Club = 1, Suite = 2, Heart = 3, Diamond = 4
    if (suite == 'C') {
        return 1;
    } else if (suite == 'S') {
        return 2;
    } else if (suite == 'H') {
        return 3;
    } else if (suite == 'D') {
        return 4;
    }
    return -1;

}

std::string Card::getCardName() const {
    return cardName;
}

bool operator<(const Card &c1, const Card &c2) {
    if (c1.getRank() < c2.getRank()) {
        return true;
    } else if (c1.getRank() == c2.getRank() && c1.getOrderedSuite() < c2.getOrderedSuite()) {
        return true;
    }
    return false;
}
