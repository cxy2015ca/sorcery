#ifndef MAPS_H
#define MAPS_H

#include <iostream>
#include <map>

using namespace std;

#include "card.h"

const map<string,int> costs = {pair<string,int>("Air Elemental",0),
                               pair<string,int>("Earth Elemental",3),
                               pair<string,int>("Bone Golem",2),
                               pair<string,int>("Fire Elemental",2),
                               pair<string,int>("Potion Seller",2),
                               pair<string,int>("Novice Pyromancer",1),
                               pair<string,int>("Apprentice Summoner",1),
                               pair<string,int>("Master Summoner",1),
                               pair<string,int>("Banish",2),
                               pair<string,int>("Unsummon",1),
                               pair<string,int>("Recharge",1),
                               pair<string,int>("Disenchant",1),
                               pair<string,int>("Raise Dead",1),
                               pair<string,int>("Blizzard",3),
                               pair<string,int>("Giant Strength",1),
                               pair<string,int>("Enrage",2),
                               pair<string,int>("Haste",1),
                               pair<string,int>("Magic Fatigue",0),
                               pair<string,int>("Silence",1),
                               pair<string,int>("Dark Ritual",0),
                               pair<string,int>("Aura of Power",1),
                               pair<string,int>("Standstill",3)};

const map<string,std::string> types = {pair<string,std::string>("Air Elemental","Minion"),
                               pair<string,std::string>("Earth Elemental","Minion"),
                               pair<string,std::string>("Bone Golem","Minion"),
                               pair<string,std::string>("Fire Elemental","Minion"),
                               pair<string,std::string>("Potion Seller","Minion"),
                               pair<string,std::string>("Novice Pyromancer","Minion"),
                               pair<string,std::string>("Apprentice Summoner","Minion"),
                               pair<string,std::string>("Master Summoner","Minion"),
                               pair<string,std::string>("Banish","Spell"),
                               pair<string,std::string>("Unsummon","Spell"),
                               pair<string,std::string>("Recharge","Spell"),
                               pair<string,std::string>("Disenchant","Spell"),
                               pair<string,std::string>("Raise Dead","Spell"),
                               pair<string,std::string>("Blizzard","Spell"),
                               pair<string,std::string>("Giant Strength","Enchantment"),
                               pair<string,std::string>("Enrage","Enchantment"),
                               pair<string,std::string>("Haste","Enchantment"),
                               pair<string,std::string>("Magic Fatigue","Enchantment"),
                               pair<string,std::string>("Silence","Enchantment"),
                               pair<string,std::string>("Dark Ritual","Ritual"),
                               pair<string,std::string>("Aura of Power","Ritual"),
                               pair<string,std::string>("Standstill","Ritual")};


const map<string,std::string> descriptions = {pair<string,std::string>("invalid card",""),
                                       pair<string,std::string>("Bone Golem","Gain +1/+1 whenever a minion leaves play."),
                                       pair<string,std::string>("Fire Elemental","Whenever an opponent's minion enters play, deal 1 damage to it. "),
                                       pair<string,std::string>("Potion Seller","At the end of turn, all your minions gain +0/+1."),
                                       pair<string,std::string>("Novice Pyromancer: Ability","Deal 1 damage to target minion."),
                                       pair<string,std::string>("Apprentice Summoner: Ability","Summon a 1/1 air elemental."),
                                       pair<string,std::string>("Master Summoner: Ability","Summon up to three 1/1 air elementals."),
                                       pair<string,std::string>("Banish","Destroy target minion or ritual"),
                                       pair<string,std::string>("Unsummon","Return target minion to it's owner's hand"),
                                       pair<string,std::string>("Recharge","Your ritual gains 3 charges"),
                                       pair<string,std::string>("Disenchant","Destroy the top enchantment on target minion"),
                                       pair<string,std::string>("Raise Dead","Resurrect the top minion in your graveyard and set its defence to 1"),
                                       pair<string,std::string>("Blizzard","Deal 2 damage to all minions"),
                                       pair<string,std::string>("Giant Strength","Enchantment"),
                                       pair<string,std::string>("Enrage","Enchantment"),
                                       pair<string,std::string>("Haste","Enchanted minion gains +1 action each turn"),
                                       pair<string,std::string>("Magic Fatigue","Enchanted minion's activated ability costs 2 more"),
                                       pair<string,std::string>("Silence","Enchanted minion cannot use abilities"),
                                       pair<string,std::string>("Dark Ritual","At the start of your turn, gain 1 magic"),
                                       pair<string,std::string>("Aura of Power","Whenever a minion enters play under your control, it gains +1/+1"),
                                       pair<string,std::string>("Standstill","Whenever a minion enters play, destroy it"),
                                       pair<string,std::string>("Silence: Enchantment","This Minion is Silenced.")};

const map<string,int> damage = {pair<string,int>("Air Elemental",1),
                                pair<string,int>("Earth Elemental",4),
                                pair<string,int>("Bone Golem",1),
                                pair<string,int>("Fire Elemental",2),
                                pair<string,int>("Potion Seller",1),
                                pair<string,int>("Novice Pyromancer",0),
                                pair<string,int>("Apprentice Summoner",1),
                                pair<string,int>("Master Summoner",2)};

const map<string,int> health = {pair<string,int>("Air Elemental",1),
                                pair<string,int>("Earth Elemental",4),
                                pair<string,int>("Bone Golem",3),
                                pair<string,int>("Fire Elemental",2),
                                pair<string,int>("Potion Seller",3),
                                pair<string,int>("Novice Pyromancer",1),
                                pair<string,int>("Apprentice Summoner",1),
                                pair<string,int>("Master Summoner",3)};

const map<string,Card> abilitys = {pair<string,Card>("Air Elemental",Card{0,"invalid card"}),
                                   pair<string,Card>("Earth Elemental",Card{0,"invalid card"}),
                                   pair<string,Card>("Bone Golem",Card{0,"invalid card"}),
                                   pair<string,Card>("Fire Elemental",Card{0,"invalid card"}),
                                   pair<string,Card>("Potion Seller",Card{0,"invalid card"}),
                                   pair<string,Card>("Novice Pyromancer",Card{1,"Novice Pyromancer: Ability"}),
                                   pair<string,Card>("Apprentice Summoner",Card{1,"Apprentice Summoner: Ability"}),
                                   pair<string,Card>("Master Summoner",Card{2,"Master Summoner: Ability"}),
                                   pair<string,Card>("Dark Ritual",Card{1,"Dark Ritual"}),
                                   pair<string,Card>("Aura of Power",Card{1,"Aura of Power"}),
                                   pair<string,Card>("Standstill",Card{2,"Standstill"}),
                                   pair<string,Card>("none",Card{0,"invalid card"}),
                                   pair<string,Card>("Silence",Card{0,"Silence: Enchantment"})};

const map<string,Trigger> trigger_list = {pair<string,Trigger>("Air Elemental",Trigger{"none","invalid card"}),
                                   pair<string,Trigger>("Earth Elemental",Trigger{"none","invalid card"}),
                                   pair<string,Trigger>("Bone Golem",Trigger{"minion_exit_play","Bone Golem"}),
                                   pair<string,Trigger>("Fire Elemental",Trigger{"op_minion_enter_play","Fire Elemental"}),
                                   pair<string,Trigger>("Potion Seller",Trigger{"end_of_turn","Potion Seller"}),
                                   pair<string,Trigger>("Novice Pyromancer",Trigger{"none","invalid card"}),
                                   pair<string,Trigger>("Apprentice Summoner",Trigger{"none","invalid card"}),
                                   pair<string,Trigger>("Master Summoner",Trigger{"none","invalid card"}),
                                   pair<string,Trigger>("Dark Ritual",Trigger{"fr_start_of_turn","Dark Ritual"}),
                                   pair<string,Trigger>("Aura of Power",Trigger{"fr_minion_enter_play","+Aura of Power"}),
                                   pair<string,Trigger>("Standstill",Trigger{"minion_enter_play","Standstill"}),
                                   pair<string,Trigger>("none",Trigger{"none","invalid card"})};

const map<string,int> charges = { pair<string,int>("Dark Ritual",5),
                                  pair<string,int>("Aura of Power",4),
                                  pair<string,int>("Standstill",4)};

#endif //TESTSORCERY_MAPS_H
