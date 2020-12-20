#include "straightGame.h"

int main(int argc, char **argv) {
    int seed = 0;
    if (argc > 2) {
		std::cerr << "Too much arguments" << std::endl;
		exit(1);
	};
    if (argc == 2) {
		seed = std::stoi(argv[1]);
	};
    std::string cmd;
    std:: string input;
    bool quit = false;
    bool over80 = false;
    int turn = -10;
    int round = 0;
    StraightGame s = StraightGame(); // s stands for Straight. Just call s for short, aka for the sake of my sanity
    
    // The pre-assign roles before starting the game
    for (int i = 0; i < 4; i++) {
        s.player[i]->setStrategy();
    }
    while ( (quit == false) && (over80 == false)) {
        bool roundSuccess = false;  
        if (s.isNewStart()) { // if all hands are empty
            if (round > 0) {
                 s.displayScore(); 
                 }
            round++;
            s.endRound();
            s.deck.initial();   // return deck to the initial order: AC 2C 3C ....
            s.deal(seed); // shuffle + deal
            s.findStartPlayer();
            turn = s.start;
            std::cout << std::endl;
            std::cout << "A new round begins. It's " << s.player[turn]->getPlayerName() << "'s turn to play." << std::endl;
        } else {
            turn = s.getTurn();
        }
        if (s.player[turn]->score >= 80) {
            over80 = true;
        }
        if (over80 && turn == s.start) {
            quit = true;
            break;
        }
        if (!s.player[turn]->isHuman) { // Computer turn
            if (!s.player[turn]->hand.isEmpty()) {
                s.displayTable();
                s.displayInfo( s.player[turn].get() );
                s.addTable( s.player[turn]->playCard() );
            }
            s.increTurn();
            turn = s.getTurn();
            roundSuccess = true;;
        } else { // Human turn, take inputs
            s.displayTable();
            s.displayInfo( s.player[turn].get() );
            std::cout << ">";
            
            while (true) {
                std::cin >> cmd;
                std::string success;
                if (cmd == "play") {
                    success = s.player[turn]->playCard();
                    if (success != "XXXX") {
                        roundSuccess = true;
                        s.addTable(success);
                    }
                } else if (cmd == "discard") {
                    std::cin >> input;
                    roundSuccess = s.player[turn]->discardCard(input);
                } else if (cmd == "deck") {
                    s.deck.display();
                    std::cout << std::endl << ">";
                } else if (cmd == "quit" || std::cin.eof()) {
                    std::cout << "The game was suspended. See you next time!" << std::endl << std::endl;
                    quit = true;
                    break;
                } else if (cmd == "ragequit") {
                    s.player[turn]->isHuman = false;
                    std::cout << "Player" << std::to_string(turn+1) << " ragequits. A computer now will take over." << std::endl;
                    s.addTable( s.player[turn]->playCard() );
                    roundSuccess = true;
                } else if (cmd == "man") {
                    std::cout << "Manual will be updated soon" << std::endl;
                    std::cout << ">";
                } else {
                    std::cout << "Please input valid command. Type 'man' to see details." << std::endl;
                    std::cout << ">";
                }
                if (roundSuccess) { 
                    s.increTurn();
                    turn = s.getTurn();
                    break;
                    if (s.isNewStart()) {
                        s.displayScore();
                    }
                }
                
            }
        }
        if (s.player[turn]->score+s.player[turn]->previous_score >= 80) {
            over80 = true;
        }

        if (quit) {
            break;
        };
    }
    s.displayScore();
    int min = 10000;
    for (int i = 0; i < 4; i++) {
        int score = s.player[i]->score + s.player[i]->previous_score;
        if (min > score) {
            min = score;
        }
    }
    for (int i = 0; i < 4; i++) {
        int score = s.player[i]->score + s.player[i]->previous_score;
        if (score == min) {
            std::cout << s.player[i]->getPlayerName() << " wins." << std::endl;
        }
    }
    return 1;
}
