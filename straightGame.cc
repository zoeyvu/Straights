#include "straightGame.h"
//#include <iostream>

StraightGame::StraightGame()
    : deck{}
    {
        for (int i = 0; i < 4; i++) {

            player.emplace_back( std::make_unique<Player>() );
            suites.emplace_back( std::make_unique<CardList>() );
        }
        player[0]->setPlayerName("Player1");
        player[1]->setPlayerName("Player2");
        player[2]->setPlayerName("Player3");
        player[3]->setPlayerName("Player4");
    }

void StraightGame::deal(int seed) {
    deck.shuffle(seed);
    for (int i = 0; i < 13; i++) {
        player[0]->addCard(deck.getCard(i));
    }
    for (int i = 13; i < 26; i++) {
        player[1]->addCard(deck.getCard(i));
    }
    for (int i = 26; i < 39; i++) {
        player[2]->addCard(deck.getCard(i));
    }
    for (int i = 39; i < 52; i++) {
        player[3]->addCard(deck.getCard(i));
    }
}

void StraightGame::endRound() {
    deck = Deck();
    table.clear();
    for (int i = 0; i < 4; i++) {
        player[i]->hand.clear();
        player[i]->discarded.clear();
        player[i]->legal.clear();
        suites[i]->clear();
    }
    turn = -1;
}

void StraightGame::displayTable() {
    std::cout << "Cards on the table: " << std::endl;
    std::cout << "Clubs: ";
    suites[0]->display();
    std::cout << std::endl;
    std::cout << "Diamonds: ";
    suites[3]->display();
    std::cout << std::endl;
    std::cout << "Hearts: ";
    suites[2]->display();
    std::cout << std::endl;
    std::cout << "Spades: ";
    suites[1]->display();
    std::cout << std::endl;
}

void StraightGame::displayInfo(Player* player) {
    std::cout << "Your hand: ";
    player->display();
    std::cout << std::endl;
    player->displayLegal(table);
}

int StraightGame::findStartPlayer() {
    if (player[0]->hand.foundCard("7S")) {
        start = 0;
        return start;
    }
    if (player[1]->hand.foundCard("7S")) {
        start =  1;
        return start;
    }
    if (player[2]->hand.foundCard("7S")) {
        start = 2;
        return start;
    }
    if (player[3]->hand.foundCard("7S")) {
        start = 3;
        return start;
    }
    else {
        std::cerr << "7S does not found in any player. Contact Nguyen." << std::endl;
        return -1;;
    }
    // std::cout << "7S found at start =" << std::to_string(start) << std::endl;
}

void StraightGame::addTable(std::string c) {
    std::string card;
    card += c[0];
    card += " ";
    table.addCard(c);
    if ( c[1] == 'C') {
        suites[0]->addCard(card);
    } else if (c[1] == 'S') {
        suites[1]->addCard(card);
    } else if (c[1] == 'H') {
        suites[2]->addCard(card);
    } else if (c[1] == 'D') {
        suites[3]->addCard(card);
    }
}


void StraightGame::displayScore() {
    for (int i = 0; i < 4; i++) {
        std::cout << player[i]->getPlayerName() << "'s discards: ";
        player[i]->discarded.display();
        std::cout << std::endl;
        std::cout << player[i]->getPlayerName() << "'s score: ";
        std::string s = std::to_string(player[i]->previous_score+player[i]->score);
        std::cout << std::to_string(player[i]->previous_score) << " + " << std::to_string(player[i]->score) << " = " << s <<  std::endl;
        player[i]->previous_score += player[i]->score;
        player[i]->score = 0;
    }
}

int StraightGame::getTurn() {
    if (turn == -1) {
        turn = start;
        return turn;
    } else {
        return turn;
    }
}

void StraightGame::increTurn() {
    turn++;
    if (turn > 3) {
        turn = 0;
    }
}

bool StraightGame::isNewStart() {
    return player[0]->hand.isEmpty() && player[1]->hand.isEmpty() && player[2]->hand.isEmpty() && player[3]->hand.isEmpty();
}





