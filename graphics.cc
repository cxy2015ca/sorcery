#include "graphics.h"

const int hCard = 100;
const int wCard = 150;

const int hMid = hCard / 2;
const int wMid = wCard / 2;

const int rows = 7;
const int cols = 5;

const int inactvHand = 0;
const int inactvStats = 1;
const int inactvBoard = 2;
const int sorcery = 3;
const int actvBoard = 4;
const int actvStats = 5;
const int actvHand = 6;

const int hBoard = hCard * rows;
const int wBoard = wCard * cols;

GraphicDisplay::GraphicDisplay() {
    xw = new Xwindow(wBoard, hBoard);
}

void GraphicDisplay::init() {
    xw->fillRectangle(0, 0, wBoard, hBoard, Xwindow::White);

    // CENTRE =================================================================
    xw->fillRectangle(0, hCard * sorcery, wBoard, hCard, Xwindow::White);
    xw->drawString(wCard * 2, hCard * sorcery + hMid, "S   O   R   C   E   R   Y");

    // HANDS ==================================================================
    xw->fillRectangle(0, hCard * actvHand, wBoard, hCard, Xwindow::White);
    xw->fillRectangle(0, hCard * inactvHand, wBoard, hCard, Xwindow::White);

    // PLAYER CARDS ===========================================================
    xw->fillRectangle(wCard * 2, hCard * actvStats, wCard, hCard, Xwindow::Blue);
    xw->fillRectangle(wCard * 2, hCard * inactvStats, wCard, hCard, Xwindow::Blue);

    // GRAVEYARDS =============================================================
    xw->fillRectangle(wCard * 4, hCard * actvStats, wCard, hCard, Xwindow::Red);
    xw->fillRectangle(wCard * 4, hCard * inactvStats, wCard, hCard, Xwindow::Red);

    // RITUALS ================================================================
    xw->fillRectangle(0, hCard * actvStats, wCard, hCard, Xwindow::Red);
    xw->fillRectangle(0, hCard * inactvStats, wCard, hCard, Xwindow::Red);

    // BOARDS =================================================================
    xw->fillRectangle(0, hCard * actvBoard, wBoard, hCard, Xwindow::White);
    xw->fillRectangle(0, hCard * inactvBoard, wBoard, hCard, Xwindow::White);
}

void GraphicDisplay::draw(Player& actv, Player& inactv) {
    init(); // reset the board

    // PLAYER STATS ===========================================================
    drawPlayers(actv, inactv);

    // HANDS ==================================================================
    for (int i = 1; i <= actv.getSize("hand"); i++) {
        drawCard(hCard * actvHand, wCard * (i - 1), actv.getCard(i, "hand").getName());
    }
    for (int i = 1; i <= inactv.getSize("hand"); i++) {
        drawCard(hCard * inactvHand, wCard * (i - 1), inactv.getCard(i, "hand").getName());
    }

    // BOARDS =================================================================
    for (int i = 1; i <= actv.getSize("board"); i++) {
        drawMinion(hCard * actvBoard, wCard * (i - 1), actv.getMinion(i, "board"));
    }
    for (int i = 1; i <= inactv.getSize("board"); i++) {
        drawMinion(hCard * inactvBoard, wCard * (i - 1), inactv.getMinion(i, "board"));
    }

    // GRAVES =================================================================
    if (actv.getSize("grave") > 0) {
        drawMinion(hCard * actvStats, wCard * 4, actv.getMinion(actv.getSize("grave"), "grave"));
    }
    if (inactv.getSize("grave") > 0) {
        drawMinion(hCard * inactvStats, wCard * 4, inactv.getMinion(inactv.getSize("grave"), "grave"));
    }

    // RITUALS ================================================================
    if (actv.getRitual().getCard().getName() != "invalid card") {
        drawRitual(hCard * actvStats, 0, actv.getRitual());
    }
    if (inactv.getRitual().getCard().getName() != "invalid card") {
        drawRitual(hCard * inactvStats, 0, inactv.getRitual());
    }
}

void GraphicDisplay::drawPlayers(Player& actv, Player& inactv) {
    int w = wCard * 2;

    // Name
    xw->drawString(w + 10, hCard * actvStats + hMid, actv.getName());
    xw->drawString(w + 10, hCard * inactvStats + hMid, inactv.getName());

    // Life
    xw->drawString(w + 10, hCard * actvStats + 90, to_string(actv.getHealth()));
    xw->drawString(w + 10, hCard * inactvStats + 90, to_string(inactv.getHealth()));
    
    // Magic
    xw->drawString(w + 130, hCard * actvStats + 90, to_string(actv.getMagic()));
    xw->drawString(w + 130, hCard * inactvStats + 90, to_string(inactv.getMagic()));
}

void GraphicDisplay::drawCard(int h, int w, string name) {
    xw->fillRectangle(w, h, wCard, hCard, Xwindow::Green);

    // Name and type
    xw->drawString(w + 10, h + 15, name);
    xw->drawString(w + 100, h + 30, types.find(name)->second);

    // Cost
    xw->drawString(w + 130, h + 15, to_string(costs.find(name)->second));

    // Description
    if ((name == "Novice Pyromancer") ||
        (name == "Apprentice Summoner") ||
        (name == "Master Summoner")) {
        name += ": Ability";
    }
    string s = descriptions.find(name)->second;

    xw->drawString(w + 10, h + 45, s.substr(0, 22));
    if (s.length() > 22) { xw->drawString(w + 10, h + 55, s.substr(22, 22)); }
    if (s.length() > 44) { xw->drawString(w + 10, h + 65, s.substr(44)); }
}

void GraphicDisplay::drawMinion(int h, int w, AbstractMinion* m) {
    drawCard(h, w, m->getName());

    // Damage and health
    xw->drawString(w + 10, h + 90, to_string(m->getDamage()));
    xw->drawString(w + 130, h + 90, to_string(m->getHealth()));
}

void GraphicDisplay::drawRitual(int h, int w, Ritual rit) {
    xw->fillRectangle(w, h, wCard, hCard, Xwindow::Red);

    string name = rit.getCard().getName();
    // Name, cost, ability cost, charge
    xw->drawString(w + 10, h + 15, name);
    xw->drawString(w + 130, h + 15, to_string(costs.find(name)->second));
    xw->drawString(w + 10, h + 45, to_string(abilitys.find(name)->second.getCost()));
    xw->drawString(w + 130, h + 90, to_string(rit.getCharge()));

    // Description
    string s = descriptions.find(name)->second;
    int pad = 30;
    int len = 18;
    xw->drawString(w + pad, h + 45, s.substr(0, len));
    if (s.length() > len) { xw->drawString(w + pad, h + 55, s.substr(len, len)); }
    if (s.length() > len * 2) { xw->drawString(w + pad, h + 65, s.substr(len * 2)); }
}
