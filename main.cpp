#include <iostream>
#include <vector>
#include <fstream>
#include "match.h"
#include "ctime"
using namespace std;


int main(int argc, char *argv[]) {
    std::srand(std::time(0));
    int i = 1;
    std::string init = "";
    std::string deck1 = "";
    std::string deck2 = "";
    bool testmode = false;
    bool graphics = false;
    while (i < argc) {
        string arg = argv[i];
        if (arg == "-init") {
            i+= 1;
            init = argv[i];
        } else if (arg == "-testing") {
            testmode = true;
        } else if (arg == "-graphics") {
            graphics = true;
        } else if (arg == "-deck1") {
            i+= 1;
            deck1 = argv[i];
        } else if (arg == "-deck2") {
            i+= 1;
            deck2 = argv[i];
        }

        i += 1;
    }
    if (!testmode) {
        Standard game1(graphics, deck1, deck2, init);
        game1.run_game();
    } else{
        Testmode game(graphics, deck1, deck2, init);
        game.run_game();
    }

}




