#ifndef ENRAGE_H
#define ENRAGE_H
#include "enchantment.h"

// Updates the attack/defence values of the minion to *2/*2

class Enrage : public Enchantment {
    public:
        Enrage(AbstractMinion *m);
        ~Enrage();
        void disenchant() override;
};

#endif
