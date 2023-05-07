#ifndef ASSIGNMENT2_BOARD_H
#define ASSIGNMENT2_BOARD_H
#include "Position.h"
#include "UnplayablePosition.h"
#include "PlayablePosition.h"
#include "Player.h"
#include <string>
class Board {
public:
    Board();
    Board(int boardNumber);
    Board(std::string positions);
    ~Board();
    void takeTurn(Player current);
    void drawBoard();
    std::string boardToString();
    bool getMoreMoves()const {return moreMoves;}
    bool isGameOver()const{return GameOver;}
    bool getSave() const{return SAVE;}
    bool getConcede()const{return CONCEDE;}
    void setConcede();
    void setSave();
    void setFirstPlayer(Player* f);
    void setSecondPlayer(Player* s);
    void setGameOver();
    bool isStar(int r, int c);
    bool isPlayable(int r, int c,char p);
    bool canConvert(int r, int c, char p);
    bool checkAdjPositions(int row, int col, char pie, char o,int dr,int dc);
    int getBlack();
    int getWhite();
    void makeMove(int r, int c, char p);
    void flip(int r, int c, char p, char o, int dr, int dc);
    bool isBoardFull();
    bool validMoves(char p, char op);
private:
    static const int SIZE{8};
    Position* board[SIZE][SIZE];
    Player* _first;
    Player* _second;
    Position *currentSpace;
    bool moreMoves= true;
    bool GameOver= false;
    bool SAVE = false;
    bool CONCEDE = false;
};


#endif //ASSIGNMENT2_BOARD_H
