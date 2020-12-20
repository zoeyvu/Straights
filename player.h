#ifndef PLAYER_H
#define PLAYER_H 

#include "cardList.h"
#include <memory>

class Human;
class Computer;

class Player {
    public:
    CardList hand = CardList();
    CardList legal = CardList();
    CardList discarded = CardList();
    
    std::string playerName;
    std::unique_ptr<Human> strategyHuman = std::make_unique<Human>();
    std::unique_ptr<Computer> strategyComputer = std::make_unique<Computer>();
    bool isHuman = false;
    unsigned int score = 0;
    unsigned int previous_score = 0;
    
    void display();
    void displayLegal(CardList c);
    bool discardCard(std::string card);
    CardList legalMove(CardList tableCards); 
    std::string getPlayerName();
    std::string playCard();
    void setPlayerName(std::string name);
    void addCard(std::string card);
    void setStrategy();
    void rageQuit();
    unsigned int getScore();    
};


class Computer { 
    public:
    ~Computer() = default;
    std::string chooseCard(Player* player);
};

class Human {
    public:
    ~Human() = default;
    std::string chooseCard(Player* player);
};


#endif
