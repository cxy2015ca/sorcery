#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <vector>
using namespace std;

class Card {
    int cost;
    string name;
public:
    Card(int, string);
    int getCost() const;
    void setCost(int);
    std::string getName() const;
    void setName(string);
};

class Trigger {
public:
    Trigger(string, string);
    string getTriggerWord() const;
    string getTriggerSpell() const;
private:
    string trigger_word;
    string trigger_spell;
};

#endif
