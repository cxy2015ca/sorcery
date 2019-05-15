#include "card.h"

Card::Card(int c, string n) {
    cost = c;
    name = n;
}

int Card::getCost() const {
    return cost;
}

void Card::setCost(int i){
    cost = i;
}

string Card::getName() const {
    return name;
}

void Card::setName(string s) {
    name = s;
}

std::string Trigger::getTriggerWord() const {
    return trigger_word;
}

std::string Trigger::getTriggerSpell() const {
    return trigger_spell;
}

Trigger::Trigger(string trig, string spell) {
    trigger_word = trig;
    trigger_spell = spell;
}
