#include "magicfatigue.h"

MagicFatigue::MagicFatigue(AbstractMinion *m) : Enchantment{m} {
    i = getSize("abilities");
    m->getAbil(i).setCost(m->getAbil(i).getCost() + 2);
    m->pushEnchant("Magic Fatigue");
}

MagicFatigue::~MagicFatigue() {}

void MagicFatigue::disenchant() {
    int c = m->getAbil(i).getCost() - 2;
    if (c < 0) { m->getAbil(i).setCost(0); }
    else m->getAbil(i).setCost(c);
}
