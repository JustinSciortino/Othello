#include <iostream>
#include <string>
#include <fstream>
#include "Game.h"
using namespace std;

int main() {
    int option;
    cout<<"1. Start a New Game"<<endl;
    cout<<"2. Quit"<<endl;
    cout<<"3. Load a Game"<<endl;
    cout<<"Option: ";
    cin>>option;

    if (option == 1){
        string name1,name2;
        cout<<"What is the name of Player 1"<<endl;
        cin>>name1;
        cout<<"What is the name of Player 2"<<endl;
        cin>>name2;
        Game game1((Player(name1)), Player(name2));
        game1.start();
        game1.play();
    }
    if(option==2){
        cout<<"Bye bye. Thanks for playing"<<endl;
    }
    if(option==3){
        int length =0;
        while(length!=64) {
            string filename, first_line, second_line, third_line, fourth_line;
            cout << "Enter the name of the file: ";
            cin >> filename;
            ifstream file(filename);
            if (file.is_open()) {
                getline(file, first_line);
                getline(file, second_line);
                getline(file, third_line);
                getline(file, fourth_line);
                file.close();
            }
            length = fourth_line.length();
            if(length!=64){
                cout<<"Could not load the board. Not enough positions. Try loading the file again."<<endl;
            }else {
                Game game2(first_line, second_line, third_line);
                Board b = game2.load(fourth_line);
                game2.setBoard(&b);
                game2.play();
            }
        }
    }
    return 0;
}
