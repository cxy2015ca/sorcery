#include "ritual.h"

Ritual::Ritual( std::string cardName):
spell{abilitys.find(cardName)->second},
charge{charges.find(cardName)->second}, trigger(trigger_list.find(cardName)->second.getTriggerWord()){}



int Ritual::getCharge() const  {
    return charge;
}

void Ritual::setCharge(int n) {
    charge = n;
}

string Ritual::getTrigger()const  {
    return trigger;
}

void Ritual::setTrigger(std::string s) {
    trigger = s;
}

Card Ritual::getCard() {
    return spell;
}