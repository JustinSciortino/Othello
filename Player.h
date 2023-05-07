#ifndef ASSIGNMENT2_PLAYER_H
#define ASSIGNMENT2_PLAYER_H
#include <string>

class Player {
private:
    std::string name;
public:
    Player(std::string name);
    std::string getName(){ return name; }

};


#endif //ASSIGNMENT2_PLAYER_H
