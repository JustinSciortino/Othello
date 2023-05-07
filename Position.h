#ifndef ASSIGNMENT2_POSITION_H
#define ASSIGNMENT2_POSITION_H

class Position {
public:
    Position();
    virtual ~Position();
    static const char EMPTY=' ';
    static const char BLACK = 'B';
    static const char WHITE = 'W';
    char getPiece() const{return piece;}
    void setPiece(char p);
    virtual bool canPlay() const =0;
private:
    char piece;
protected:
    Position(char piece);
};
#endif //ASSIGNMENT2_POSITION_H
