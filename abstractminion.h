#ifndef ABSTRACTMINION_H
#define ABSTRACTMINION_H
#include "card.h"

class Minion;
class Enchantment;

// The AbstractMinion class is an abstract base class that is 
// Inherited by:
// * Minion (concrete)
// * Enchantment (abstract)
// * inheritors of Enchantment (concrete)

class AbstractMinion {
    public:
        virtual ~AbstractMinion() = 0;
        virtual string getName() = 0;
        virtual void setName(string) = 0;
        virtual int getHealth() = 0;
        virtual void setHealth(int) = 0;
        virtual int getDamage() = 0;
        virtual void setDamage(int) = 0;
        virtual int getSize(string) = 0;
        virtual void addCard(Card) = 0;
        virtual void addCard(Trigger) = 0;
        virtual Card& getAbil(int) = 0;
        virtual Trigger& getTrig(int) = 0;
        virtual Card giveAbil(int) = 0;
        virtual Trigger giveTrig(int) = 0;
        virtual void setCard(int, Card) = 0;
        virtual void setCard(int, Trigger) = 0;
        virtual int getActions() = 0;
        virtual void setActions(int) = 0;
        virtual int getMaxActions() = 0;
        virtual void setMaxActions(int) = 0;
        virtual string getEnchant() = 0;
        virtual void pushEnchant(string) = 0;
        virtual void popEnchant() = 0;
        virtual Card use() = 0;
        virtual AbstractMinion* detach(int) = 0; // remove n enchantments
};

#endif
