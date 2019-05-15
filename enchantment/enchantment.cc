#include "enchantment.h"

Enchantment::Enchantment(AbstractMinion *m) : m{m} {}
Enchantment::~Enchantment() { delete m; }

AbstractMinion* Enchantment::getChild() { return m; }

// detach(int n) recursively removes n number of enchantments
// from the AbstractMinion
AbstractMinion* Enchantment::detach(int n) {
    this->disenchant(); // remove effects of enchantment from the component
    this->popEnchant(); // remove name from m->enchantments (vector of strings)
    AbstractMinion *temp = this->getChild();
    if (n == 1) return temp;
    return temp->detach(n - 1);
}

// Get/set component ==========================================================

string Enchantment::getName() { return m->getName(); }
void Enchantment::setName(string s) { m->setName(s); }
int Enchantment::getHealth() { return m->getHealth(); }
void Enchantment::setHealth(int n) { m->setHealth(n); }
int Enchantment::getDamage() { return m->getDamage(); }
void Enchantment::setDamage(int n) { m->setDamage(n); }
int Enchantment::getSize(string s) { return m->getSize(s); }
void Enchantment::addCard(Card c) { m->addCard(c); }
void Enchantment::addCard(Trigger t) { m->addCard(t); }
Card& Enchantment::getAbil(int n) { return m->getAbil(n); }
Trigger& Enchantment::getTrig(int n) { return m->getTrig(n); }
Card Enchantment::giveAbil(int n) { return m->giveAbil(n); }
Trigger Enchantment::giveTrig(int n) { return m->giveTrig(n); }
void Enchantment::setCard(int n, Card c) { m->setCard(n, c); }
void Enchantment::setCard(int n, Trigger t) { m->setCard(n, t); }
int Enchantment::getActions() { return m->getActions(); }
void Enchantment::setActions(int n) { m->setActions(n); }
int Enchantment::getMaxActions() { return m->getMaxActions(); }
void Enchantment::setMaxActions(int n) { m->setMaxActions(n); }
string Enchantment::getEnchant() { return m->getEnchant(); }
void Enchantment::pushEnchant(string s) { m->pushEnchant(s); }
void Enchantment::popEnchant() { m->popEnchant(); }
Card Enchantment::use() { return m->use(); }
