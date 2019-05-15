#ifndef PLAYER_H
#define PLAYER_H

#include <algorithm>
#include "abstractminion.h"
#include "ritual.h"
#include "maps.h"
#include "ctime"

//int maxHand = 5;
//int maxBoard = 5;

class Player {
    Ritual rit;
    string name;
    static int players; // the number of players that exist.
    int player_num;
    int health;
    int magic;
    vector<Card> deck;
    vector<Card> hand;
    vector<AbstractMinion*> board;
    vector<AbstractMinion*> grave;
    int maxMagic;
public:
    Player(string n,int i); //initializes ritual with cardname "none"
    ~Player(); // deletes all cards in all holders.

    // --- basic memeber access functions ---
    string getName() const;
    void setName(string);
    int getHealth() const;
    void setHealth(int);
    int getPlayerNum();

    // --- action/magic functions ---
    void setMaxMagic(int);
    int getMaxMagic();
    int getMagic() const;
    void setMagic(int);
    bool checkMagic(int); // this isn't used
    bool checkAction(int, int); // neither is this.
    void setMinionAction(); // resets minion actions to max_actions.


    // ---------- Vector Access Functions -----------------
    // Note: string input to these functions should be "deck","hand","board" or "grave"
    // Note: when accessing card use 1 as the smallest index and getSize([location]) as
    //       the largest

    // returns the number of elements in the vector.
    int getSize(string) const;
    // adds the given card to the back of the deck or hand.
    void addCard(Card, string);
    // adds the given minion to the back of board or grave.
    void addMinion(AbstractMinion*, string);
    // returns a reference to the card at the given index in hand or deck.
    Card& getCard(int, string);
    // returns a reference to the minion at the given index in grave or board.
    AbstractMinion* getMinion(int, string);
    // sets the minion at the given index on board or in grave.
    void setMinion(AbstractMinion*, string, int);
    // removes and return the card at the given index.
    Card giveCard(int, string);
    // shuffles the given vector.
    void shuffleCards(std::string);
    // removes the minion at the index and returns a pointer to it.
    // client should free memory
    AbstractMinion* giveMinion(int, string);

    // These are not used...
    void setCard(int, Card, string); //insert card on nth spot
    void setCard(int, AbstractMinion*, string);

    // sets or returns the players ritual.
    void setRitual(std::string);
    Ritual& getRitual();

    //draws n cards from deck to hand, returns actual amount drawn
    int draw_card(int n);
};




#endif //TESTSORCERY_CLASSES_H
