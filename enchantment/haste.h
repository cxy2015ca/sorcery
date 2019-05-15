#ifndef HASTE_H
#define HASTE_H
#include "enchantment.h"

// Grants a minion one extra action per turn

class Haste : public Enchantment {
    public:
        Haste(AbstractMinion *m);
        ~Haste();
        void disenchant() override;
};

#endif
