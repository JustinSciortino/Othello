#ifndef ASSIGNMENT2_GAME_H
#define ASSIGNMENT2_GAME_H
#include "Board.h"
#include "Player.h"
#include <string>


class Game {
public:
    Game();
    Game(Player p1, Player p2);
    Game(Player p1, Player p2, std::string c);
    void start();
    void setBoard(int);
    void setBoard(Board* b);
    ~Game();
    static Board load(std::string b);
    void play();
private:
    void save();
    Player first;
    Player second;
    Player *currentPlayer = &first;
    Board* board;
};


#endif
