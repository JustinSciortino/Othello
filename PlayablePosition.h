#ifndef ASSIGNMENT2_PLAYABLEPOSITION_H
#define ASSIGNMENT2_PLAYABLEPOSITION_H
#include "Position.h"

class PlayablePosition : public Position {
public:
    PlayablePosition(char piece): Position(piece){};
    bool canPlay() const;
};

#endif //ASSIGNMENT2_PLAYABLEPOSITION_H
