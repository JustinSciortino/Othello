#include <iostream>
#include <string>
#include "Board.h"

using namespace std;
Board::Board() {}
Board::Board(std::string positions) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = nullptr;
        }
    }
    int strIndex = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (strIndex < positions.length()) {
                if (positions[strIndex] == '*') {
                    board[i][j] = new UnplayablePosition(UnplayablePosition::UNPLAYABLE);
                    strIndex++;
                } else if (positions[strIndex] == ' '){
                    board[i][j] = new PlayablePosition(PlayablePosition::EMPTY);
                    strIndex++;
                } else if (positions[strIndex] == 'W') {
                    board[i][j] = new PlayablePosition(PlayablePosition::WHITE);
                    strIndex++;
                } else if (positions[strIndex] == 'B') {
                    board[i][j] = new PlayablePosition(PlayablePosition::BLACK);
                    strIndex++;

                }
            }
        }

    }
}
Board::Board(int boardNumber) {
    for(int i =0;i <SIZE;i++) {
        for (int j = 0; j < SIZE; j++) {
            if ((i == 0 && j == 3) || (i == 0 && j == 4)) {
                board[i][j] = new UnplayablePosition(UnplayablePosition::UNPLAYABLE);
            } else {
                board[i][j] = new PlayablePosition(PlayablePosition::EMPTY);
            }

        }
    }
    switch (boardNumber) {
        case 0:
            board[3][3]->setPiece(Position::WHITE);
            board[4][4]->setPiece(Position::WHITE);
            board[3][4]->setPiece(Position::BLACK);
            board[4][3]->setPiece(Position::BLACK);
            break;
        case 1:
            board[2][2]->setPiece(Position::WHITE);
            board[3][3]->setPiece(Position::WHITE);
            board[2][3]->setPiece(Position::BLACK);
            board[3][2]->setPiece(Position::BLACK);
            break;
        case 2:
            board[2][4]->setPiece(Position::WHITE);
            board[3][5]->setPiece(Position::WHITE);
            board[2][5]->setPiece(Position::BLACK);
            board[3][4]->setPiece(Position::BLACK);
            break;
        case 3:
            board[4][2]->setPiece(Position::WHITE);
            board[5][3]->setPiece(Position::WHITE);
            board[4][3]->setPiece(Position::BLACK);
            board[5][2]->setPiece(Position::BLACK);
            break;
        case 4:
            board[4][4]->setPiece(Position::WHITE);
            board[5][5]->setPiece(Position::WHITE);
            board[4][5]->setPiece(Position::BLACK);
            board[5][4]->setPiece(Position::BLACK);
            break;
        default:
            cout<<"You entered an invalid number. You are playing on board 0 (Standard Starting Position)"<<endl;
            board[3][3]->setPiece(Position::WHITE);
            board[4][4]->setPiece(Position::WHITE);
            board[3][4]->setPiece(Position::BLACK);
            board[4][3]->setPiece(Position::BLACK);
            break;
    }
}
void Board::drawBoard() {
    cout<<"     0   1   2   3   4   5   6   7  "<<endl;
    for (int i = 0; i < SIZE; i++) {
        cout<<"   +---+---+---+---+---+---+---+---+"<<endl;
        int j =0;
        cout<<i<<"  "<<"| "<<board[i][j]->getPiece()<<" | "<<board[i][j+1]->getPiece()<<" | "<<board[i][j+2]->getPiece()
        <<" | "<<board[i][j+3]->getPiece()<<" | "<<board[i][j+4]->getPiece()<<" | "<<board[i][j+5]->getPiece()<<" | "
        <<board[i][j+6]->getPiece()<<" | "<<board[i][j+7]->getPiece()<<" | "<<endl;
    }
    cout<<"   +---+---+---+---+---+---+---+---+"<<endl;
}
string Board::boardToString() {
    string str;
    for (int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            str+=(board[i][j]->getPiece());
        }
    }
    return str;
}
Board::~Board(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            delete board[i][j];
            board[i][j]= nullptr;
        }
    }
}
bool Board::isStar(int r, int c) {
    currentSpace = board[r][c];
    if (currentSpace->getPiece()== UnplayablePosition::UNPLAYABLE){
        return false;
    }else{
        return currentSpace->canPlay();
    }
}
int Board::getBlack() {
    int k{0};
    for(int i =0;i <SIZE;i++) {
        for (int j = 0; j < SIZE; j++) {
            if(board[i][j]->getPiece()==Position::BLACK){
                k++;
            }
        }
    }
    return k;
}
int Board::getWhite() {
    int k{0};
    for(int i =0;i <SIZE;i++) {
        for (int j = 0; j < SIZE; j++) {
            if(board[i][j]->getPiece()==Position::WHITE){
                k++;
            }
        }
    }
    return k;
}
bool Board::isPlayable(int r, int c,char p) {
    currentSpace = board[r][c];
    if(currentSpace->getPiece() == PlayablePosition::EMPTY){
        return true;
    }else{
        return false;
    }
}
bool Board::validMoves(char p, char op) {
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(board[i][j]->getPiece()==PlayablePosition::EMPTY){
                for (int dr = -1; dr <= 1; dr++) {
                    for (int dc = -1; dc <= 1; dc++) {
                        if (dr == 0 && dc == 0) continue;
                        if (checkAdjPositions(i, j, p, op, dr, dc)) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}
void Board::makeMove(int r, int c, char p) {
    char otherPiece;
    if (p==PlayablePosition::BLACK){
        otherPiece=PlayablePosition::WHITE;
    }else{
        otherPiece=PlayablePosition::BLACK;
    }
    board[r][c]->setPiece(p);
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue;
            if (checkAdjPositions(r, c, p, otherPiece, dr, dc)) {
                flip(r, c, p, otherPiece, dr, dc);
            }
        }
    }
}
bool Board::checkAdjPositions(int row, int col, char pie, char o,int dr,int dc){
    int endRow = row+dr;
    int endCol = col+dc;
    if(endRow<0 || endRow>=SIZE || endCol<0 || endCol>= SIZE){
        return false;
    }
    if(board[endRow][endCol]->getPiece() != o){
        return false;
    }
    while(endRow>= 0 && endRow<SIZE && endCol>=0 && endCol<SIZE){
        endRow+=dr;
        endCol+=dc;
        if(endRow<0 || endRow>= SIZE || endCol<0 || endCol>=SIZE){
            return false;
        }
        if(board[endRow][endCol]->getPiece()==pie){
            return true;
        }
        if(board[endRow][endCol]->getPiece() != o){
            return false;
        }
    }
    return false;
}
void Board::flip(int r, int c, char p, char o, int dr, int dc) {
    int row = r + dr;
    int col = c + dc;
    while (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col]->getPiece() == o) {
        row += dr;
        col += dc;
    }
    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col]->getPiece() == p) {
        row -= dr;
        col -= dc;
        while (row != r || col != c) {
            board[row][col]->setPiece(p);
            row -= dr;
            col -= dc;
        }
    }
}
bool Board::isBoardFull() {
    int count{0};
    for(int i=0;i<SIZE;i++){
        for(int j =0;j <SIZE;j++){
            if(board[i][j]->getPiece()!=PlayablePosition::EMPTY){
                count+=1;
            }
        }
    }
    if(count==64){
        return true;
    }else{
        return false;
    }
}
bool Board::canConvert(int r, int c, char p) {
    char otherPiece;
    if (p==PlayablePosition::BLACK){
        otherPiece=PlayablePosition::WHITE;
    }else{
        otherPiece=PlayablePosition::BLACK;
    }
    bool nw = checkAdjPositions(r,c,p,otherPiece,-1,-1);
    bool nn = checkAdjPositions(r,c,p,otherPiece,-1,0);
    bool ne = checkAdjPositions(r,c,p,otherPiece,-1,1);
    bool ww = checkAdjPositions(r,c,p,otherPiece,0,-1);
    bool ee = checkAdjPositions(r,c,p,otherPiece,0,1);
    bool sw = checkAdjPositions(r,c,p,otherPiece,1,-1);
    bool ss = checkAdjPositions(r,c,p,otherPiece,1,0);
    bool se = checkAdjPositions(r,c,p,otherPiece,1,1);

    if(nw||nn||ne||ww||ee||sw||ss||se){
        return true;
    }else{
        return false;
    }
}

void Board::takeTurn(Player current) {
    char playerPiece;
    char otherPiece;
    char save{'s'}, concede{'c'}, forfeit{'f'};
    char userChoice;
    int row, col;
    char userInput;
    bool isTrue{true};
    if (current.getName() == _first->getName()) {
        while (isTrue) {
            cout << _first->getName() << " score (B): " << getBlack() << "\t" << _second->getName() << " score (W): "
                 << getWhite() << endl;
            playerPiece = PlayablePosition::BLACK;
            otherPiece=PlayablePosition::WHITE;
            if(validMoves(playerPiece, otherPiece)){
                cout << "It is " << current.getName() << "'s turn. Please place a "
                     << playerPiece
                     << " by entering the row followed by the column. You may also save the game (s) or concede the game (c)"
                     << endl;
                cout << "s, c or Row x Column:";
                cin >> userChoice;
                if (isdigit(userChoice) && !cin.fail()) {
                    cin.unget();
                    cin >> row >> col;
                    if ((0 <= row && row <= 7) && (0 <= col && col <= 7)) {
                        if (isStar(row, col)) {
                            if (isPlayable(row, col, playerPiece)) {
                                if (canConvert(row, col, playerPiece)) {
                                    makeMove(row, col, playerPiece);
                                    isTrue = false;
                                    if (isBoardFull()) {
                                        cout << "GAME OVER" << endl;
                                        cout << _first->getName() << " score (B): " << getBlack() << "\t"
                                             << _second->getName() << " score (W): " << getWhite() << endl;
                                        if (getBlack() > getWhite()) {
                                            cout << _first->getName() << " won!" << endl;
                                            setGameOver();
                                        } else if (getBlack() < getWhite()) {
                                            cout << _second->getName() << " won!" << endl;
                                            setGameOver();
                                        } else {
                                            cout << "Tie game" << endl;
                                            setGameOver();
                                        }
                                    }
                                } else {
                                    cout << row << " " << "x" << " " << col
                                         << " is not playable. Does not convert any other pieces. Try again"
                                         << endl;
                                }
                            } else {
                                cout << row << " " << "x" << " " << col
                                     << " is not playable. You cannot play on the positions with a piece already there. Try again"
                                     << endl;
                            }
                        } else {
                            cout << row << " " << "x" << " " << col
                                 << " is not playable. You cannot play on the positions with a *. Try again" << endl;
                        }
                    } else {
                        cout << "Row or column number out of range. Try again" << endl;
                    }
                } else {
                    if (userChoice == save) {
                        cout << current.getName() << " is saving the game" << endl;
                        setSave();
                        isTrue = false;
                    } else if (userChoice == concede) {
                        cout << current.getName() << " is conceding the game" << endl;
                        setConcede();
                        cout << _second->getName() << " won!" << endl;
                        isTrue = false;
                    } else {
                        cout << "Invalid input" << endl;
                    }
                }
            }else{
                cout <<"It is "<<current.getName()<<"' turn. " <<"There are no available moves to make. Forfeit your turn by inputting f." << endl;
                while(userInput!='f'){
                    cout<<"Press (f) to forfeit: ";
                    cin>>userInput;
                    if(userInput==forfeit){
                        cout<<"Forfeiting..."<<endl;
                        isTrue= false;
                    }
                }
            }
        }
    }else{
        while (isTrue) {
            cout << _first->getName() << " score (B): " << getBlack() << "\t" << _second->getName() << " score (W): "
                 << getWhite() << endl;
            playerPiece = PlayablePosition::WHITE;
            otherPiece=PlayablePosition::BLACK;
            if(validMoves(playerPiece, otherPiece)){
                cout << "It is " << current.getName() << "'s turn. Please place a "
                     << playerPiece
                     << " by entering the row followed by the column. You may also save the game (s) or concede the game (c)"
                     << endl;
                cout << "s, c or Row x Column:";
                cin >> userChoice;
                if (isdigit(userChoice) && !cin.fail()) {
                    cin.unget();
                    cin >> row >> col;
                    if ((0 <= row && row <= 7) && (0 <= col && col <= 7)) {
                        if (isStar(row, col)) {
                            if (isPlayable(row, col, playerPiece)) {
                                if (canConvert(row, col, playerPiece)) {
                                    makeMove(row, col, playerPiece);
                                    isTrue = false;
                                    if (isBoardFull()) {
                                        cout << "GAME OVER" << endl;
                                        cout << _first->getName() << " score (B): " << getBlack() << "\t"
                                             << _second->getName() << " score (W): " << getWhite() << endl;
                                        if (getBlack() > getWhite()) {
                                            cout << _first->getName() << " won!" << endl;
                                            setGameOver();
                                        } else if (getBlack() < getWhite()) {
                                            cout << _second->getName() << " won!" << endl;
                                            setGameOver();
                                        } else {
                                            cout << "Tie game" << endl;
                                            setGameOver();
                                        }
                                    }
                                } else {
                                    cout << row << " " << "x" << " " << col
                                         << " is not playable. Does not convert any other pieces. Try again"
                                         << endl;
                                }
                            } else {
                                cout << row << " " << "x" << " " << col
                                     << " is not playable. You cannot play on the positions with a piece already there. Try again"
                                     << endl;
                            }
                        } else {
                            cout << row << " " << "x" << " " << col
                                 << " is not playable. You cannot play on the positions with a *. Try again" << endl;
                        }
                    } else {
                        cout << "Row or column number out of range. Try again" << endl;
                    }
                } else {
                    if (userChoice == save) {
                        cout << current.getName() << " is saving the game" << endl;
                        setSave();
                        isTrue = false;
                    } else if (userChoice == concede) {
                        cout << current.getName() << " is conceding the game" << endl;
                        setConcede();
                        cout << _first->getName() << " won!" << endl;
                        isTrue = false;
                    } else {
                        cout << "Invalid input" << endl;
                    }
                }
            }else{
                cout <<"It is "<<current.getName()<<"' turn. " <<"There are no available moves to make. Forfeit your turn by inputting f." << endl;
                while(userInput!='f'){
                    cout<<"Press (f) to forfeit: ";
                    cin>>userInput;
                    if(userInput==forfeit){
                        cout<<"Forfeiting..."<<endl;
                        isTrue= false;
                    }
                }
            }
        }
    }
}

void Board::setFirstPlayer(Player* f) {
    _first = f;
}
void Board::setSecondPlayer(Player *s) {
    _second=s;
}
void Board::setGameOver() {
    GameOver = true;
}
void Board::setConcede() {
    CONCEDE= true;
}
void Board::setSave() {
    SAVE=true;
}