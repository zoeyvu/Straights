#ifndef GAME_H
#define GAMEK_H 

#include "deck.h"
#include "player.h"

class StraightGame {
    public:
    Deck deck;
    CardList table;
    std::vector<std::unique_ptr<Player>> player;
    std::vector<std::unique_ptr<CardList>> suites;
    int start = 0;
    int turn = -1;

    StraightGame();
    bool isNewStart(); // all player's hands are empty
    int findStartPlayer();
    int getTurn();
    void increTurn();
    void deal(int seed = 20831324);
    void endRound(); 
    void addTable(std::string c);
    void displayTable();
    void displayInfo(Player* player);
    void displayScore();
};

#endif
