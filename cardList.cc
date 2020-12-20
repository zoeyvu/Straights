#include "cardList.h"

void CardList::deleteCard(std::vector<Card>::iterator i) {
    if (i != listCard.end()) {
    listCard.erase(i);
    } else {
        std::cerr << "Index is out of range" << std::endl;
    }
}

int CardList::size() {
    return listCard.size();
}

void CardList::display() {
    int count = 0;
    int round = 0;
    for (auto &cur_card: listCard) {
        if (count == 13) {
            std::cout << std::endl;
            count = 0;
        }
        if (round != 0 && count == 0) {
            std::cout << std::endl;
        }
        std::cout << cur_card.getCardName() << " ";
        count++;
    }
}

std::string CardList::getCard(unsigned int i) {
    if (i < listCard.size()) {
        Card c = listCard.at(i);
        return c.getCardName();
    } else {
        return "i for getCard() out of range";
    }
}

std::vector<Card>::iterator CardList::findCard(std::string nameCard) {
    std::vector<Card>::iterator iter = listCard.begin();
    for (auto &cur_card: listCard) {
        if (cur_card.getCardName().compare(nameCard) == 0){
            return iter;
        } else {
            iter++;
        }
    }
    return iter;
}

bool CardList::foundCard(std::string nameCard) {
    std::vector<Card>::iterator found = this->findCard(nameCard);
    return found != listCard.end();
}

std::vector<Card>::iterator CardList::end() {
    return listCard.end();
}

std::vector<Card>::iterator CardList::begin() {
    return listCard.begin();
}

void CardList::deleteCard(std::string nameCard) {
    std::vector<Card>::iterator it = this->findCard(nameCard);
    if (it != listCard.end()) {
        listCard.erase(it);
    }
}

void CardList::addCard(std::string str) {
    Card c = Card(str);
    auto iter = listCard.begin();
    for (auto &cur_card: listCard) {
        if (cur_card < c) {
            iter++;
        }
    }
    listCard.insert(iter, c);
}

void CardList::addCardUnordered(std::string str) {
    Card c = Card(str);
    listCard.push_back(c);
}


bool CardList::isEmpty() {
    return listCard.size() == 0;
}

void CardList::clear() {
    listCard.clear();
}


