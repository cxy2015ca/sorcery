#ifndef TRIGGERSPELL_H
#define TRIGGERSPELL_H
#include "abstractminion.h"
#include "player.h"

class Player;

void modvals(int atk, int hp, AbstractMinion* m);

void standstill(AbstractMinion* m);

void dark_ritual(Player& p);
#endif
