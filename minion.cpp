#include "minion.h"

Minion::Minion() {}

Minion::~Minion() {}

Minion::Minion(string n, int i, int j) : name{n}, health{i}, damage{j}, actions{0} {
    maxactions = 1;
    this->addCard(abilitys.find(this->getName())->second);
    this->addCard(trigger_list.find(this->getName())->second);
}

// GETTERS/SETTERS ============================================================

string Minion::getName() {
    return name;
}

void Minion::setName(string n) {
    name = n;
}

int Minion::getHealth() {
    return health;
}

void Minion::setHealth(int n) {
    health = n;
}

int Minion::getDamage() {
    return damage;
}

void Minion::setDamage(int n) {
    damage = n;
}

int Minion::getActions() {
    return actions;
}

void Minion::setActions(int n) {
    actions = n;
}

int Minion::getMaxActions() {
    return maxactions;
}

void Minion::setMaxActions(int n) {
    maxactions = n;
}

// Implemented for display purposes only
string Minion::getEnchant() {
    string s;
    for (int i = 0; i < enchantments.size(); i++) {
        s = s + enchantments.at(i) + "\n";
    }
    s += "base";
    return s;
}

void Minion::pushEnchant(string e) {
    enchantments.push_back(e);
}

void Minion::popEnchant() {
    enchantments.pop_back();
}

// VECTOR MANIPULATIONS =======================================================

int Minion::getSize(string s) {
    if (s == "abilities") return abilities.size();
    if (s == "triggers") return triggers.size();
    return 0;
}

void Minion::addCard(Card c) {
    abilities.push_back(c);
}

void Minion::addCard(Trigger t) {
    triggers.push_back(t);
}

Card& Minion::getAbil(int n) {
    return abilities.at(n - 1);
}

Trigger& Minion::getTrig(int n) {
    return triggers.at(n - 1);
}

Card Minion::giveAbil(int n) {
    Card c = abilities.at(n - 1);
    abilities.erase(abilities.begin() + n - 1);
    abilities.shrink_to_fit();
    return c;
}

Trigger Minion::giveTrig(int n){
    Trigger c = triggers.at(n - 1);
    triggers.erase(triggers.begin() + n - 1);
    triggers.shrink_to_fit();
    return c;
}

void Minion::setCard(int i, Card c) {
    abilities.insert(abilities.begin() + i - 1, c);
}

void Minion::setCard(int i, Trigger t) {
    triggers.insert(triggers.begin() + i - 1, t);
}

Card Minion::use() {
    if (abilities.empty()) { return Card{0,"invalid card"}; } 
    else { return abilities.back(); }
}

// ENCHANTMENTS ===============================================================

AbstractMinion* Minion::detach(int n) {
    return this;
}
