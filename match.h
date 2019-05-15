#ifndef MATCH_H
#define MATCH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "card.h"
#include "minion.h"
#include "player.h"
#include "spells.h"
#include "maps.h"

#include "abstractminion.h"
#include "enchantment/enchantment.h"
#include "enchantment/giantstrength.h"
#include "enchantment/enrage.h"
#include "enchantment/haste.h"
#include "enchantment/magicfatigue.h"
#include "enchantment/silence.h"
#include "triggerspell.h"
#include "graphics.h"
#include "display.h"

using namespace std;
//int maxHand = 5;
class Player;
class Card;
class GraphicDisplay;



// _________________________ REDIRECT CLASS ____________________________
// Note: the redirect class is the handle input from init and from user
//       it automaticly decides weather to read from fstream(init)
//       readbuffer or the standard cin readbuffer.
//       it should be called with [redirect] >> var;

struct Redirect {
    // --- Constructor ---
    // Note:: Input is the filename of the file to redirect to cin.
    Redirect(string file_name) {
        if (file_name != "") {
            f_name = file_name;
            fbuf.open(file_name, ios::in); // open file for input
            oldbuf = cin.rdbuf(addressof(fbuf)); // redirect file to cin
        }
    }
    // --- Destructor ---
    ~Redirect() { cin.rdbuf(oldbuf); }
    istream & operator>>(string& str) {
        // if file exists redirect it to cin.
        if (f_name != "") {
            if (cin >> str) { return cin; } // if reading from cin with fstream
            else {                          // readbuffer fails revert to original.
                cin.rdbuf(oldbuf);
                cin >> str;
                return cin;
            }
        // if filename is empty just read from cin.
        } else {
            cin >> str;
            return cin;
        }
    }
    // Provide getline functionality for redirects.
    void getline_bin(std::string& str) {  getline(std::cin,str); }
    // The feilds of redirect
    std::filebuf fbuf ; // file readbuffer
    std::streambuf* oldbuf ; // cin original readbuffer
    std::string f_name; // file name

};





// ______________________________ MATCH ______________________________
// abstract class that defines a gamemode.



class Match {
    Redirect bin;
    string deck1;
    string deck2;
    bool graphics;
    GraphicDisplay *g;

    //applies the effects of a triggered ability.
    void trigger_cast(Player& self, Player& opponent, AbstractMinion* target,
                            AbstractMinion* activated, const string spell);

    protected:
        Redirect& get_bin() { return bin; }
        //a tool for testing can be called with print.
        void print_state_testing_tool(Player& p1, Player& p2);
        //checks for death of minions
        void resolve(Player& actv, Player& inactv);
        // Notifies minions and rituals of a trigger.
        void trigger(string, AbstractMinion*, Player&, Player&);
        // Simplifies calling triggers
        void minEnterTrig(Player& actv, Player& inactv);
        // Starts actv players turn and allows them to enter commands.
        virtual bool take_turn(Player& actv, Player& inactv)=0;
        //plays a card, casts spell, places minions
        virtual bool play(Player& actv ,Player& inactv,Card card)=0;
        //uses minion abilities
        virtual bool use(Player& actv ,Player& inactv,Card card, AbstractMinion* m)=0;
        // Throws an wincondition to be caught in rungame.
        void declare_winner(string condition, string win, string lose );
        // Allows a minion to attack (if m2 is nullptr minion attacks player)
        virtual void attack(AbstractMinion* m1, AbstractMinion* m2,Player& p);

        string getdeck1(){return deck1;}
        string getdeck2(){return deck2;}
        bool getGraphics() { return graphics; }
        GraphicDisplay& getGraphicDisplay() { return *g; }

    public:
        Match(bool graphics,
            string deck1file = "default.deck",
            std::string deck2file = "default.deck",
            std::string initilization_file = "");
        virtual ~Match();
        Player& getPlayer(Player& actv, Player& inactv, int);
        virtual void run_game()=0; //init game
};





// _____________________________ STANDARD ____________________________
// This is the standard gamemode with normal rules.




class Standard : public Match {
    // Active player takes a turn.
    bool take_turn(Player& actv, Player& inactv) override;
    // Plays the given card to the board.
    bool play(Player& actv ,Player& inactv,Card card) override;
    // Uses a minions active ability.
    bool use(Player& actv ,Player& inactv, Card card, AbstractMinion* m) override;

public:
    void run_game() override; // Starts the game.
    // --- Constructor ---
    Standard(
        bool graphics,
        std::string deck1file,
         std::string deck2file,
         std::string init = "");

    // --- Destructor ---
    ~Standard();
};





// _____________________________ Testmode ____________________________
// This is the standard gamemode with normal rules.




class Testmode : public Match {
    // Active player takes a turn.
    bool take_turn(Player& actv, Player& inactv) override;
    // Plays the given card to the board.
    bool play(Player& actv ,Player& inactv,Card card) override;
    // Uses a minions active ability.
    bool use(Player& actv ,Player& inactv, Card card, AbstractMinion* m) override;

public:
    void run_game() override; // Starts the game.
    // --- Constructor ---
    Testmode(
            bool graphics,
            std::string deck1file,
            std::string deck2file,
            std::string init = "");

    // --- Destructor ---
    ~Testmode();
};


// __________________________ WIN CONDITION __________________________
// This is a class that should be thrown like an exception when the game is over.
// This allows the game to exit at any point (such as when a player tries to draw a
// card and none are left). It is caught and it's message is displayed in run_game;
class WinCondition{
    string message;
public:
    // conditions are "game_end" "milled" "player_died"
    WinCondition(string, string, string);
    string read() const;
};




#endif //TESTSORCERY_MATCH_H
