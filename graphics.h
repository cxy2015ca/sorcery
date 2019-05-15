#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "match.h"
#include "window.h"
#include "maps.h"

class GraphicDisplay {
    Xwindow *xw;

    public:
        GraphicDisplay();
        void init();
        
        void draw(Player& actv, Player& inactv);
        void drawPlayers(Player& actv, Player& inactv);
        void drawCard(int h, int w, string name);
        void drawMinion(int h, int w, AbstractMinion* m);
        void drawRitual(int h, int w, Ritual rit);
};

#endif
