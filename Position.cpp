#include "Position.h"
Position::Position() {
    piece = EMPTY;
}
Position::Position(char piece):piece(piece){
}
Position::~Position() {}
void Position::setPiece(char p) {
    this->piece=p;
}
