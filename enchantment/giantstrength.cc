#include "giantstrength.h"

GiantStrength::GiantStrength(AbstractMinion *m) : Enchantment{m} {
    m->setDamage(m->getDamage() + 2);
    m->setHealth(m->getHealth() + 2);
    m->pushEnchant("Giant Strength");
}

GiantStrength::~GiantStrength() {}

void GiantStrength::disenchant() {
    int h = m->getHealth() - 2;
    int d = m->getDamage() - 2;

    if (h < 1) m->setHealth(1); // minion cannot die from enchantment remvoal
    else m->setHealth(h);
    if (d < 0) m->setDamage(0); // minion cannot have negative damage
    else m->setDamage(d);
}
