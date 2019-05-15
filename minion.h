#ifndef MINION_H
#define MINION_H

#include "abstractminion.h"
#include "maps.h"


// _____________________________ MINION _________________________________
// Note: This is the concrete implementation of AbstractMinion.
//       Minion objects are created when placing a card
//       (mapped to type "Minion") from the hand onto the board.
//       Minions can be enchanted, and become components of the corresponding
//       "enhantment" class.

class Minion : public AbstractMinion {
    string name;
    int health; //defence
    int damage; //attack
    int actions;
    int maxactions;
    vector<Card> abilities; // list of active abilities
    vector<Trigger> triggers; // list of triggered abilities
    vector<string> enchantments; // for display purposes only
public:
    Minion();
    ~Minion() override;
    Minion(string n ,int i ,int j);
    string getName() override;

    // --- basic access operators ---
    void setName(string) override;
    int getHealth() override;
    void setHealth(int) override;
    int getDamage() override;
    void setDamage(int) override;

    // gets size of vector | pass : "triggers" "abilities"
    int getSize(string) override;

    // --------------------------------------------
    // Note: when accessing the following
    //       functions use 1 as the smallest index
    // --------------------------------------------

    // add a activated ability or a trigger.
    void addCard(Card) override;
    void addCard(Trigger) override;
    // same thing as above but at an specified index.
    void setCard(int, Card) override;
    void setCard(int, Trigger) override;

    // get returns ref to top ability
    // give returns a copy and pops it.
    Card& getAbil(int) override;
    Trigger& getTrig(int) override;
    Card giveAbil(int) override;
    Trigger giveTrig(int) override;

    int getActions() override;
    void setActions(int) override;
    int getMaxActions() override;
    void setMaxActions(int) override;
    string getEnchant() override;

    void pushEnchant(string) override;
    void popEnchant() override;
    Card use() override;
    AbstractMinion* detach(int) override; // disenchant; returns itself
};

#endif
