#ifndef RITUAL_H
#define RITUAL_H

#include <string>
#include "card.h"
#include "maps.h"


// _____________ THIS CLASS IS FOR RITUALS ______________

class Ritual {
    // the abilities and activation costs are in card spell
    Card spell;
    int charge;
    //trigger word
    std::string trigger;
public:
    // -- CTOR ---------
    Ritual(std::string cardName);

    // get set methods
    int getCharge() const ;
    void setCharge(int);
    std::string getTrigger()const ;
    void setTrigger(std::string);
    Card getCard();
};


#endif
