#ifndef MAGICFATIGUE_H
#define MAGICFATIGUE_H
#include "enchantment.h"

// MagicFatigue causes the minion's current ability costs 2 extra
// Modifies only the top ability on the vector; adding another ability
// to the minion will not maintain the MagicFatigue affect (as in Hearthstone)

class MagicFatigue : public Enchantment {
    private:
        int i; // position of the top ability (keep track to disenchant later)
    public:
        MagicFatigue(AbstractMinion *m);
        ~MagicFatigue();
        void disenchant() override;
};

#endif
