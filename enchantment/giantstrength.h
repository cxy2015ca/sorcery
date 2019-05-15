#ifndef GIANTSTRENGTH_H
#define GIANTSTRENGTH_H
#include "enchantment.h"

// Updates the attack/defence values of the minion to +2/+2
// The minion cannot die from enchantment removal

class GiantStrength : public Enchantment {
    public:
        GiantStrength(AbstractMinion *m);
        ~GiantStrength();
        void disenchant() override;
};

#endif
