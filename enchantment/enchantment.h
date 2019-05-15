#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H
#include "../abstractminion.h"

// Abstract decorator class for AbstractMinion; effects are implemented
// in the specific enchantment's concrete class (ex. Enrage, Silence, etc.)

class Enchantment : public AbstractMinion {
    protected:
        Enchantment(AbstractMinion *m);
        AbstractMinion *m;
    public:
        virtual ~Enchantment();

        // Call the component's corresponding method  =========================
        string getName() override;
        void setName(string) override;
        int getHealth() override;
        void setHealth(int) override;
        int getDamage() override;
        void setDamage(int) override;
        int getSize(string) override;
        void addCard(Card) override;
        void addCard(Trigger) override;
        Card& getAbil(int) override;
        Trigger& getTrig(int) override;
        Card giveAbil(int) override;
        Trigger giveTrig(int) override;
        void setCard(int, Card) override;
        void setCard(int, Trigger) override;
        int getActions() override;
        void setActions(int) override;
        int getMaxActions() override;
        void setMaxActions(int) override;
        string getEnchant() override;
        void pushEnchant(string) override;
        void popEnchant() override;
        Card use() override;
        
        // Enchantment-specific methods =======================================
        AbstractMinion* getChild();
        AbstractMinion* detach(int) override;
        virtual void disenchant() = 0;
};

#endif
