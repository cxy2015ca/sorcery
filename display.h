#ifndef DISPLAY_H
#define DISPLAY_H
#include <iostream>
#include <iostream>
#include <sstream>
#include <vector>
#include "card.h"
#include "abstractminion.h"
#include "maps.h"
#include "player.h"
#include "ascii_graphics.h"

class Card;
class AbstractMinion;
class Player;
class Ritual;

class ASCIIDisplay {
public:
    ASCIIDisplay(int);
    ASCIIDisplay(Card&);
    ASCIIDisplay(string);
    ASCIIDisplay(AbstractMinion*);
    ASCIIDisplay(Player&);
    ASCIIDisplay(Ritual&);
    ASCIIDisplay(vector<string>);
    void reform_to_board(Player&,Player&);
    void reform_to_hand(Player&);
    void reform_to_inspect(AbstractMinion*);
    void add(ASCIIDisplay& other,int offset);
    string getLine(int);
    int getSize();
    void print();
private:
    vector<string> line;
};

#endif //TESTSORCERY_DISPLAY_H
