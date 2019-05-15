#include "triggerspell.h"

void modvals(int atk, int hp, AbstractMinion* m) {
    m->setDamage(m->getDamage()+atk);
    m->setHealth(m->getHealth()+hp);
}

void standstill(AbstractMinion* m) {
    m->setHealth(0);
}

void dark_ritual(Player& p) {
    p.setMagic(p.getMagic()+1);
}