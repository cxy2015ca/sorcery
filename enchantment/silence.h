#ifndef SILENCE_H
#define SILENCE_H
#include "enchantment.h"

// Silence forces the enchanted minion to be unable to use any actviated
// or triggered abilities.
// If a new ability is added to the minion, it will be able to use it.

class Silence : public Enchantment {
    private:
        int a; // position of the silenced activated ability
        int t; // position of the silenced triggered ability
    public:
        Silence(AbstractMinion *m);
        ~Silence();
        void disenchant() override;
};

#endif
