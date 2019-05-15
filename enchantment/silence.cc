#include "silence.h"

// Adds a new NULL activated and triggered ability to the minion
Silence::Silence(AbstractMinion *m) : Enchantment{m} {
    Card *c = new Card(0, "Silence: Enchantment");
    Trigger *trig = new Trigger("none", "Silence: Enchantment");
    m->addCard(*c);
    m->addCard(*trig);
    a = m->getSize("abilities");
    t = m->getSize("triggers");
    m->pushEnchant("Silence");
}

Silence::~Silence() {}

// Removes the null activated/triggered abilities from the minion
void Silence::disenchant() {
    m->giveAbil(a);
    m->giveTrig(t);
}
