#include "Game.h"
#include <iostream>
#include <string>
#include "fstream"
using namespace std;
Game::Game(Player p1, Player p2, std::string c):first(p1),second(p2),board(nullptr) {
    if(c=="first"){
        currentPlayer =&first;
    }else{
        currentPlayer = &second;
    }
}
Game::Game(Player p1, Player p2):first(p1), second(p2),currentPlayer(&first), board(nullptr){
}
void Game::setBoard(Board* b){
    if(board!= nullptr){
        delete board;
    }
    board=new Board(*b);
}
void Game::setBoard(int b){
    if(board!= nullptr){
        delete board;
    }
    board = new Board(b);
}
void Game::start() {
    cout<<"Player 1:"<<first.getName()<<endl;
    cout<<"Player 2:"<<second.getName()<<endl;
    cout<<endl;
    int boardOption;
    cout << "From the five options below, pick the one you wish to play on" << endl;
    ifstream inputFile("boardOptions.txt");
    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            cout << line << endl;
        }
        inputFile.close();
    } else {
        cout << "Unable to open file" << endl;
    }
    cout<<"Option: ";
    cin>>boardOption;
    setBoard(boardOption);
}
void Game::save() {
    string filename;
    cout<<"Enter the name of the file you want to save the game to (must be .txt): ";
    cin>>filename;
    string currentPNum;
    if(currentPlayer==&first){
        currentPNum = "first";
    }else{
        currentPNum = "second";
    }
    string boardSequence = board->boardToString();
    ofstream outfile(filename);
    outfile<<first.getName()<<endl;
    outfile<<second.getName()<<endl;
    outfile<<currentPNum<<endl;
    outfile<<boardSequence<<endl;

    if(outfile.good()){
        cout<<"Successfully saved"<<endl;
    }else{
        cout<<"Error. File not saved"<<endl;
    }
    outfile.close();
}
Board Game::load(string b) {
    Board board1(b);
    return board1;
}
void Game::play(){
    do{
        board->drawBoard();
        board->setFirstPlayer(&first);
        board->setSecondPlayer(&second);
        board->takeTurn(*currentPlayer);

        if(board->getSave()){
            this->save();
        }
        if (!board->isGameOver()) {
            if (currentPlayer == &first) currentPlayer = &second;
            else currentPlayer = &first;
        }
    }while((!board->isGameOver() && board->getMoreMoves())&&(!board->getSave() && !board->getConcede()));

    if(board->isBoardFull()){
        board->drawBoard();
    }
}
Game::~Game(){
    delete board;
}
