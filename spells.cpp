#include "spells.h"

bool Banish(Player& p1, Player& p2, int target_player, int target_card){
    if (target_card < 6) {
        if (target_player == 1) {
            p1.getMinion(target_card, "board")->setHealth(0);
        } else {
            p2.getMinion(target_card, "board")->setHealth(0);
        }
        return true;
    } else if (target_card == 6){
        if (target_player == 1) {
            p1.setRitual("none");
        } else {
            p2.setRitual("none");
        }
        return true;
    }
    return false;
}

bool addMagic(Player& p, int n){
    int old = p.getMagic();
    p.setMagic(old + n);
    return true;
}

bool manipDamageHealth(Player& p, int ith, int dam, int health){
        AbstractMinion *m = p.getMinion(ith, "board");
        m->setDamage(m->getDamage() + dam);
        m->setHealth(m->getHealth() + health);
    return true;
}

bool unsummon(Player& p1, Player& p2, int target_player, int target_card){
    if(target_player==1){
        AbstractMinion* m = p1.giveMinion(target_card, "board");
        string minion = m->getName();
        delete m;
        Card temp(costs.find(minion)->second,minion);
        p1.addCard(temp,"hand");
        return true;
    }else if(target_player==2){
        AbstractMinion* m = p2.giveMinion(target_card, "board");
        string minion = m->getName();
        delete m;
        Card temp(costs.find(minion)->second,minion);
        p2.addCard(temp,"hand");
        return true;
    }
    return false;
}

bool recharge(Player& p, int charge) {
    if (p.getRitual().getCard().getName() != "none"||"invalid card"){
        throw("invalid ritual");
    }
    if (p.getRitual().getCard().getName() != "none"||"invalid card") {
        int prevCharge = p.getRitual().getCharge();
        p.getRitual().setCharge(prevCharge + charge);
        return true;
    }
    return false;
}


bool disenchant(Player& p1, Player& p2, int targetPlayer, int targetMinion){
    AbstractMinion* m;
    if (targetPlayer == 1) { m = p1.getMinion(targetMinion, "board"); }
    else                   { m = p2.getMinion(targetMinion, "board"); }
    m = m->detach(1);
    return true;
}

bool raiseDead(Player& p) {
    if (p.getSize("board") < 5 && (p.getSize("grave")>0)) {
        p.addMinion(p.giveMinion(p.getSize("grave"), "grave"), "board");
        p.getMinion(p.getSize("board"), "board")->setHealth(1);
        return true;
    }
    return false;
}

bool blizzard(Player& p1, Player& p2){
    for(int i = 1; i <= p1.getSize("board"); i++){
        manipDamageHealth(p1, i, 0, -2);
    }
    for(int i = 1; i <= p2.getSize("board"); i++){
        manipDamageHealth(p2, i, 0, -2);
    }
    return true;
}

//***********************   activated abilities  *************
bool novicePyromancerAbil(Player& p1, Player& p2, int target_player, int ith){
    if(target_player == 1) {
        manipDamageHealth(p1, ith, 0, -1);
        return true;
    }
    if(target_player == 2) {
        manipDamageHealth(p2, ith, 0, -1);
        return true;
    }
    return true;
}

bool apprenticeSummonerAbil(Player& p){
    if(p.getSize("board")<5){
        string min = "Air Elemental";
        AbstractMinion* m = new Minion{min,
                                       health.find(min)->second,
                                       damage.find(min)->second};
        p.addMinion(m, "board");
        return true;
    }
    return false;
}

int masterSummonerAbil(Player& p){
    int i = 0;
    while(p.getSize("board")<5 && i < 3){
        string min = "Air Elemental";
        AbstractMinion* m = new Minion{min,
                                       health.find(min)->second,
                                       damage.find(min)->second};
        p.addMinion(m, "board");
        i++;
    }
    return i;
}