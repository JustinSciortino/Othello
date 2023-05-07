#ifndef ASSIGNMENT2_UNPLAYABLEPOSITION_H
#define ASSIGNMENT2_UNPLAYABLEPOSITION_H
#include "Position.h"

class UnplayablePosition: public Position {

public:
    UnplayablePosition(char piece): Position(piece){};
    bool canPlay() const;
    static const char UNPLAYABLE= '*';
};

#endif //ASSIGNMENT2_UNPLAYABLEPOSITION_H
