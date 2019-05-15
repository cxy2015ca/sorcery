#ifndef SPELLS_H
#define SPELLS_H
#include "player.h"
#include "minion.h"

bool Banish(Player& p1, Player& p2, int target_player, int target_card);

bool addMagic(Player& p, int n);

//changes stats for ith minion on p's board
// use + for add, - for subtract, 0 for no change
bool manipDamageHealth(Player& p, int ith, int dam, int health);

bool unsummon(Player& p1, Player& p2, int target_player, int target_card);

bool recharge(Player& p, int charge);

bool disenchant(Player& p1, Player& p2, int target_player, int target_card);

bool raiseDead(Player& p); //puts dead minion back in board

bool blizzard(Player& p1, Player& p2);

bool  novicePyromancerAbil(Player& p1, Player& p2, int target_player, int ith);

bool apprenticeSummonerAbil(Player& p);

int masterSummonerAbil(Player& p);

#endif
