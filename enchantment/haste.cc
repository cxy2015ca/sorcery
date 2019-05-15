#include "haste.h"

Haste::Haste(AbstractMinion *m) : Enchantment{m} {
    m->setMaxActions(m->getMaxActions() + 1);
    m->pushEnchant("Haste");
}

Haste::~Haste() {}

void Haste::disenchant() {
    int a = m->getMaxActions() - 1;
    if (a > 0) { m->setMaxActions(a); }
    else { m ->setMaxActions(0); }
}

