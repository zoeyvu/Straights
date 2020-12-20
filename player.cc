#include "player.h"


std::string Computer::chooseCard(Player* player) {
    if (player->hand.isEmpty() ) {
        std::cerr << "Computer has no cards -> no moves, contactNguyen" << std::endl;
        return "No more card, this should not be printed";
    } else if (player->legal.isEmpty()) {
        return player->hand.getCard(0);
    } else {
         return player->legal.getCard(0);
    }
}

std::string Human::chooseCard(Player* player) {
    std::string card_input;
    std::cin >> card_input;  // EXTREMELY DANGEROUS if CTRL+D happens here!!!!!
        if (player->legal.isEmpty() && player->hand.foundCard(card_input)) {
            std::cout << "Please discard a card." << std::endl;
        } else if (!player->legal.isEmpty() && player->legal.foundCard(card_input)) {
            return card_input;
        } else if (player->legal.isEmpty() && !player->hand.foundCard(card_input) && !player->hand.isEmpty()) {
            std::cout << card_input << " not found. Please discard a card in your hand." << std::endl;
        } else if (!player->legal.isEmpty() && !player->legal.foundCard(card_input)) {
            std::cout << "Card " << card_input << " is not a legal move." << std::endl;
        } else if (!player->hand.foundCard(card_input)) {
            std::cout << "Card " << card_input << " is not in your hand." << std::endl;
        } else {
            std::cout << "Card " << card_input << " can't be play. Contact Nguyen because this line should not be printed." << std::endl;
        }
        std::cout << ">";
    return "No Cards Found";
}

void Player::display() {
    hand.display();
}

void Player::setPlayerName(std::string name) {
    playerName = name;
}

std::string Player::getPlayerName() {
    return playerName;
}

void Player::addCard(std::string card) {
    hand.addCard(card);
}

bool Player::discardCard(std::string card) {
    if (legal.isEmpty() && hand.findCard(card) != hand.end()) {
        discarded.addCardUnordered(card); 
        hand.deleteCard(card);
        Card c = Card(card);
        score += c.getRank();
        std::cout << this->getPlayerName() << " discards " << card << std::endl;
        std::cout << std::endl;
        return true;
    } else if (!legal.isEmpty()) {
        std::cerr << "You have a legal play. You may not discard." << std::endl;
        std::cout << ">";
    } else if (hand.findCard(card) == hand.end()) {
        std::cerr << card << " is not in hand" << std::endl << ">";
    } else {
        std::cerr << "Discard failed. Undetected error." << std::endl;
    }
    return false;
}


unsigned int Player::getScore() {
    return score;
}

char to_Rank(int i) {
    if (i == 0) {
        return 'X';
    } else if (i==1) {
        return 'A';
    } else if (i==2) {
        return '2';
    } else if (i==3) {
        return '3';
    } else if (i==4) {
        return '4';
    } else if (i==5) {
        return '5';
    } else if (i==6) {
        return '6';
    } else if (i==7) {
        return '7';
    } else if (i==8) {
        return '8';
    } else if (i==9) {
        return '9';
    } else if (i==10) {
        return 'T';
    } else if (i==11) {
        return 'J';
    } else if (i==12) {
        return 'Q';
    } else if (i==13) {
        return 'K';
    } else if (i==14) {
        return 'X';
    };
    return 'X';
}

CardList Player::legalMove(CardList c) {
    CardList legalMoves = CardList();
    if (c.isEmpty()) {
        // std::cout << "c is empty" << std::endl;
        if (hand.findCard("7S") != hand.end()){
            // std::cout << "Found 7S" << std::endl;
            legalMoves.addCard("7S");
            return legalMoves;
        } else {
            return legalMoves;
        }
    }
    for (auto &cur_card: hand) {
        std::string ajName_low = "XX";
        std::string ajName_high = "XX";
        int cur_card_rank = cur_card.getRank();
        int ajName_low_rank = cur_card_rank - 1;
        int ajName_high_rank = cur_card_rank + 1;
        ajName_low[0] = to_Rank(ajName_low_rank);
        ajName_high[0] = to_Rank(ajName_high_rank);
        ajName_low[1] = cur_card.getSuite();
        ajName_high[1] = cur_card.getSuite();
        // Card ajdLow = Card(ajName_low);
        // Card ajdHigh = Card(ajName_high);
        if (cur_card.getRank() == 7) {
            legalMoves.addCard(cur_card.getCardName());
        } else if (c.findCard(ajName_low) != c.end()) {
            legalMoves.addCard(cur_card.getCardName());
        } else if (c.findCard(ajName_high) != c.end()) {
            legalMoves.addCard(cur_card.getCardName());
        } 
    }
    return legalMoves;
}

void Player::displayLegal(CardList c) {
    legal = this->legalMove(c);
    std::cout << "Legal: ";
    legal.display();
    std::cout << std::endl;
}

void Player::setStrategy() {
    std::string input;
    std::cout << "Is " << this->getPlayerName() << " a human (h) or a computer (c)?" << std::endl;
    while (std::cin >> input) {
        if (input == "h" || input == "H") {
            isHuman = true;
            break;
        } else if (input == "c" || input == "C") {
            isHuman = false;
            break;
        }
    }
}


void Player::rageQuit() {
    isHuman = false;
}

std::string Player::playCard() {
    std::string chosenCard;
    if (isHuman) {
        chosenCard = strategyHuman->chooseCard(this);
    } else {
        chosenCard = strategyComputer->chooseCard(this);
    }
    if (legal.foundCard(chosenCard)) {
        hand.deleteCard(chosenCard);
        std::cout << this->getPlayerName() << " plays " << chosenCard << std::endl;
        std::cout << std::endl;
        return chosenCard;
    } else if (isHuman && !legal.foundCard(chosenCard)) {
        return "XXXX";
    } else if (isHuman && !hand.foundCard(chosenCard)) {
        std::cout << "Please choose a card in your hand." << std::endl;
        std::cout << ">";
        return "XXXX";
    } else if (hand.foundCard(chosenCard) && isHuman == false) {
        this->discardCard(chosenCard);
        return chosenCard;
    } else if (hand.foundCard(chosenCard) && isHuman == false) {
        std::cout << "This is not a legal play." << std::endl;
        std::cout << ">";
        return "XXXX";
    }
    else {
        return "XXXX";
    }
}



