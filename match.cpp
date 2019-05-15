#include "match.h"

// Tryparse for reading
bool tryParse(string& input, int& output) {
    try{
        output = std::stoi(input);
    } catch (std::invalid_argument) {
        return false;
    }
    return true;
}

// Match functions =================================================


Match::Match(bool graphics, std::string deck1file, std::string deck2file, std::string init) : graphics{graphics}, bin{init} {
    if (deck1file != "") { deck1 = deck1file; }
    else { deck1 = "default.deck"; }
    if (deck2file != "") { deck2 = deck1file; } 
    else { deck2 = "default.deck"; }
    if (getGraphics()) {
        g = new GraphicDisplay;
        g->init();
    }

}

Match::~Match() {
}

Player& Match::getPlayer(Player& actv,Player& inactv,int p) {
    if (actv.getPlayerNum() == p) {return actv;}
    else { return inactv; }
}

void Match::print_state_testing_tool(Player& actv,Player& inactv){
    Player& p1 = getPlayer(actv,inactv,1);
    Player& p2 = getPlayer(actv,inactv,2);
    ASCIIDisplay activ(actv);
    activ.reform_to_board(actv,inactv);
    activ.print();
    cout << "p1 hand:" << endl;
    for(int i = 1; i <= p1.getSize("hand"); i++){
        cout << "\t" << p1.getCard(i, "hand").getName() << endl;
    }
    cout << "p1 board:" << endl;
    for(int i = 1; i <= p1.getSize("board"); i++){
        cout << "\t" << "Minion #" << i << ": " << p1.getMinion(i, "board")->getName();
        cout << "; health: " << p1.getMinion(i, "board")->getHealth()
             << "; damage: " << p1.getMinion(i, "board")->getDamage()
             << "; actions: " << p1.getMinion(i, "board")->getActions()
             << "; top ability: " << p1.getMinion(i, "board")->getAbil(p1.getMinion(i, "board")->getSize("abilities")).getName()
             << "; ability cost: " << p1.getMinion(i, "board")->getAbil(p1.getMinion(i, "board")->getSize("abilities")).getCost()
             << endl;
    }
    cout<< "\t"<< "Ritual:"<<p1.getRitual().getCard().getName()<< " charge: "<< p1.getRitual().getCharge() <<endl;

    cout << "p2 hand:" << endl;
    for(int i = 1; i <= p2.getSize("hand"); i++){
        cout << "\t" << p2.getCard(i, "hand").getName()<< endl;
    }
    cout << "p2 board:" << endl;
    for(int i = 1; i <= p2.getSize("board"); i++){
        cout << "\t" << "Minion #" << i << ": " << p2.getMinion(i, "board")->getName();
        cout << "; health: " << p2.getMinion(i, "board")->getHealth()
             << "; damage: " << p2.getMinion(i, "board")->getDamage()
             << "; top ability: " << p2.getMinion(i, "board")->getAbil(p2.getMinion(i, "board")->getSize("abilities")).getName()
             << "; ability cost: " << p2.getMinion(i, "board")->getAbil(p2.getMinion(i, "board")->getSize("abilities")).getCost()
             << endl;
    }
     cout<< "\t"<< "Ritual:"<<p2.getRitual().getCard().getName()<< " charge: "<< p2.getRitual().getCharge()<<endl;
}

void Match::resolve(Player& actv,Player& inactv) {

 //   cout << "resolving combat" << endl;

    int body_count = 0;
    for (int i = 1; i <= actv.getSize("board"); i++) {
        if (actv.getMinion(i, "board")->getHealth() <= 0) {
            AbstractMinion* m = actv.giveMinion(i, "board")->detach(100);
            actv.addMinion(m,"grave");
            body_count += 1;
        }
    }
    for (int i = 1; i <= inactv.getSize("board"); i++) {
        if (inactv.getMinion(i, "board")->getHealth() <= 0) {
            inactv.getMinion(i, "board")->setHealth(0);
            AbstractMinion* m = inactv.giveMinion(i, "board")->detach(100);
            inactv.addMinion(m,"grave");
            body_count += 1;
        }
    }
  //  cout << "body count : " << body_count << endl;
}

void Match::trigger(std::string tword,AbstractMinion* m,Player& actv, Player& inactv){
    if (tword.substr(0,2) == "fr") {
        for(int i = 1; i <= actv.getSize("board"); i++){
            AbstractMinion* curr = actv.getMinion(i, "board");
            if (tword == curr->getTrig(curr->getSize("triggers")).getTriggerWord()){
                trigger_cast(actv,inactv,m,curr,curr->getTrig(curr->getSize("triggers")).getTriggerSpell());
                resolve(actv,inactv);
            }
        }
        Ritual& rit = actv.getRitual();
        if (rit.getCharge() >= rit.getCard().getCost()) {
            if (tword == rit.getTrigger()) {
                trigger_cast(actv,inactv,m,nullptr,rit.getCard().getName());
                rit.setCharge(rit.getCharge() - rit.getCard().getCost());
                resolve(actv,inactv);
            }
        }
    } else if (tword.substr(0,2) == "op") {
        for(int i = 1; i <= inactv.getSize("board"); i++){
            AbstractMinion* curr = inactv.getMinion(i, "board");
            if (tword == curr->getTrig(curr->getSize("triggers")).getTriggerWord()){
                trigger_cast(inactv,actv,m,curr,curr->getTrig(curr->getSize("triggers")).getTriggerSpell());
                resolve(actv,inactv);
            }
        }
        Ritual& rit = inactv.getRitual();
        if (rit.getCharge() >= rit.getCard().getCost()) {
            if (tword == rit.getTrigger()) {
                trigger_cast(actv,inactv,m,nullptr,rit.getCard().getName());
                rit.setCharge(rit.getCharge() - rit.getCard().getCost());
                resolve(actv,inactv);
            }
        }
    } else {
        for(int i = 1; i <= actv.getSize("board"); i++){
            AbstractMinion* curr = actv.getMinion(i, "board");
            if (tword == curr->getTrig(curr->getSize("triggers")).getTriggerWord()){
                trigger_cast(actv,inactv,m,curr,curr->getTrig(curr->getSize("triggers")).getTriggerSpell());
                resolve(actv,inactv);
            }
        }
        Ritual& rit1 = actv.getRitual();
        if (rit1.getCharge() >= rit1.getCard().getCost()) {
            if (tword == rit1.getTrigger()) {
                trigger_cast(actv,inactv,m,nullptr,rit1.getCard().getName());
                rit1.setCharge(rit1.getCharge() - rit1.getCard().getCost());
                resolve(actv,inactv);
            }
        }
        for(int i = 1; i <= inactv.getSize("board"); i++){
            AbstractMinion* curr = inactv.getMinion(i, "board");
            if (tword == curr->getTrig(curr->getSize("triggers")).getTriggerWord()){
                trigger_cast(inactv,actv,m,curr,curr->getTrig(curr->getSize("triggers")).getTriggerSpell());
                resolve(actv,inactv);
            }
        }
        Ritual& rit2 = inactv.getRitual();
        if (rit2.getCharge() >= rit2.getCard().getCost()) {
            if (tword == rit2.getTrigger()) {
                trigger_cast(inactv,actv,m,nullptr,rit2.getCard().getName());
                rit2.setCharge(rit2.getCharge() - rit2.getCard().getCost());
                resolve(actv,inactv);
            }
        }
    }
}

// fr_start_of_turn
// op_start_of_turn
// start_of_turn

// fr_end_of_turn
// op_end_of_turn
// end_of_turn

// fr_minion_enter_play
// op_minion_enter_play
// minion_enter_play

// minion_exit_play

void Match::trigger_cast(Player& self,Player& opponent ,AbstractMinion* target,AbstractMinion* activated,const std::string spell){
    //TEMP
    if (spell == "Bone Golem") {
        modvals(1,1,activated);
    }
    else if (spell == "Potion Seller") {
        for(int i = 1; i <= self.getSize("board"); i++){
            AbstractMinion* curr = self.getMinion(i, "board");
            modvals(0,1,curr);
        }
    } else if (spell == "Fire Elemental") {
        modvals(0,-1,target);
    } else if (spell == "Aura of Power") {
        modvals(1,1,target);
    } else if (spell == "Standstill") {
        standstill(target);
    } else if (spell == "Dark Ritual") {
      //  cout<<'\t'<<'\t'<<"dark ritual called in trigger cast"<<endl;
        dark_ritual(self);
    }
}

void Match::minEnterTrig(Player& actv, Player& inactv){
    trigger("fr_minion_enter_play", actv.getMinion(actv.getSize("board"), "board"), actv, inactv);
    trigger("op_minion_enter_play", actv.getMinion(actv.getSize("board"), "board"), actv, inactv);
    trigger("minion_enter_play", actv.getMinion(actv.getSize("board"), "board"), actv, inactv);
}

void Match::declare_winner(std::string condition, string win, string lose) {
    if (win == "" && lose =="") {
        const WinCondition throwable{"game_end",win,lose};
        throw throwable;
    } else {
        const WinCondition throwable{condition,win,lose};
        throw throwable;
    }
}

void Match::attack(AbstractMinion* m1, AbstractMinion* m2, Player& p) {
    if(m2 == nullptr){
        p.setHealth(p.getHealth()- m1->getDamage()) ;
    }else {
        m1->setHealth(m1->getHealth() - m2->getDamage());
        m2->setHealth(m2->getHealth() - m1->getDamage());
    }
}









// Standard functions ==================================================

Standard::Standard(bool graphics, string deck1f, string deck2f, string init) 
    : Match{ graphics, deck1f, deck2f, init } {}

Standard::~Standard() {}


bool Standard::take_turn(Player& actv, Player& inactv) {
    actv.setMaxMagic(actv.getMaxMagic() + 1);//gets 1 magic
    actv.setMagic(actv.getMaxMagic());
    actv.setMinionAction();// reset minion actions
    int drawn = actv.draw_card(1);//draws card
    if(drawn == 0 && actv.getSize("deck")==0){
        declare_winner("out of cards",inactv.getName(), actv.getName());
    }
    trigger("start_of_turn",nullptr,actv,inactv);
    trigger("fr_start_of_turn",nullptr,actv,inactv);
    trigger("op_start_of_turn",nullptr,actv,inactv);
    while(true) {
        if (getGraphics() == true) { getGraphicDisplay().draw(actv, inactv); }
        string input;
        get_bin() >> input;
        if (input == "end") {break;}
        else if (input == "play") {
            string card;
            int card_num; //= stoi(card);
            get_bin() >> card;
            while(!tryParse(card,card_num)){
                std::cout << "Bad Input" << std::endl;
                get_bin() >> card;
            };
            try {
                if(actv.getCard(card_num,"hand").getCost() <= actv.getMagic()) {
                    Card temp = actv.getCard(stoi(card), "hand");
                    bool result = play(actv, inactv, temp);
                    if(result) actv.setMagic(actv.getMagic()-temp.getCost());
                    actv.giveCard(stoi(card), "hand");
                }else cout<<"not enough magic"<<endl;
            } catch (const std::out_of_range& e) {
                std::cout << "card doesn't exist" << std::endl;
            } catch(const std::invalid_argument& e){
                std::cout << "you entered an invalid argument" << std::endl;
            }

        }
        else if (input == "use") {
            get_bin() >> input;
            int min;
            while(!tryParse(input,min)){
                std::cout << "Bad Input" << std::endl;
                get_bin() >> input;
            };
            try {
                Card ability = actv.getMinion(min, "board")->use();
                if(actv.getMinion(min, "board")->getActions() > 0) {
                    if(ability.getCost() <= actv.getMagic()) {
                        bool result = use(actv, inactv, ability, actv.getMinion(min, "board"));
                        if(result) actv.setMagic(actv.getMagic()-ability.getCost());
                        resolve(actv,inactv);
                    } else cout<<"not enough magic"<<endl;
                } else cout<<"not enough actions"<<endl;
            } catch (const std::out_of_range& e) {
                std::cout << "card doesn't exist" << std::endl;
            } catch(const std::invalid_argument& e){
                std::cout << "you entered an invalid argument" << std::endl;
            }
        }
        else if (input == "attack") {
            try {
                string min1, min2;
                get_bin().getline_bin(input);
                istringstream command{input};
                command >> min1;
                if (!command.eof()) {
                    command >> min2;
                } else {
                    min2 = "";
                }
                if (actv.getMinion(stoi(min1), "board")->getActions() > 0) {
                    AbstractMinion* m1 = actv.getMinion(stoi(min1),"board");
                    if(min2 == ""){
                        inactv.setHealth(inactv.getHealth()- m1->getDamage()) ;
                    }else {
                        AbstractMinion* m2 = inactv.getMinion(stoi(min2),"board");
                        m1->setHealth(m1->getHealth() - m2->getDamage());
                        m2->setHealth(m2->getHealth() - m1->getDamage());
                    }
		            actv.getMinion(stoi(min1), "board")->setActions(actv.getMinion(stoi(min1), "board")->getActions() - 1);
                    resolve(actv, inactv);
                } else cout << "not enough actions" << endl;

            } catch (const std::out_of_range& e) {
                std::cout << "card doesn't exist" << std::endl;
            } catch(const std::invalid_argument& e){
                std::cout << "you entered an invalid argument" << std::endl;
            }
        }
        else if (input == "print") {
            print_state_testing_tool(actv,inactv);
        }
        else if (input == "hand") {
            ASCIIDisplay hand(1);
            hand.reform_to_hand(actv);
            hand.print();
        }
        else if (input == "board") {
            ASCIIDisplay board(1);
            board.reform_to_board(actv,inactv);
            board.print();
        }
        else if (input == "inspect") {
            try {
                get_bin() >> input;
                int min = stoi(input);
                ASCIIDisplay inspection(1);
                inspection.reform_to_inspect(actv.getMinion(min,"board"));
                inspection.print();
            } catch (const std::out_of_range& e) {
                std::cout << "card doesn't exist" << std::endl;
            } catch(const std::invalid_argument& e){
                std::cout << "you entered an invalid argument" << std::endl;
            }
        }
        else if (input == "help") {
            std::cout << "Commands: help -- Display this message.\n" << std::endl;
            std::cout << "\t end -- End the current player’s turn.\n" << std::endl;
            std::cout << "\t quit -- End the game.\n" << std::endl;
            std::cout << "\t attack minion other-minion -- Orders minion to attack other-minion.\n" << std::endl;
            std::cout << "\t attack minion -- Orders minion to attack the opponent.\n" << std::endl;
            std::cout << "\t play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player.\n" << std::endl;
            std::cout << "\t use minion [target-player target-card] -- Use minion’s special ability, optionally targeting target-card owned by target-player.\n" << std::endl;
            std::cout << "\t inspect minion -- View a minion’s card and all enchantments on that minion." << std::endl;
            std::cout << "\t hand -- Describe all cards in your hand." << std::endl;
            std::cout << "\t board -- Describe all cards on the board." << std::endl;
        }
        else if (input == "surrender") { declare_winner("player_died",inactv.getName(), actv.getName()); }
        else if (input == "quit") { declare_winner("game_end",actv.getName(), inactv.getName()); }
    }
    trigger("end_of_turn",nullptr,actv,inactv);
    trigger("fr_end_of_turn",nullptr,actv,inactv);
    trigger("op_end_of_turn",nullptr,actv,inactv);

    // check to see if somebody won.
    if (inactv.getHealth() <= 0) {
        declare_winner("player_died", actv.getName(), inactv.getName());
        return true;
    }
    return true;
}


bool Standard::play(Player& actv ,Player& inactv,Card card) {

    Player &p1 = getPlayer(actv, inactv, 1);
    Player &p2 = getPlayer(actv, inactv, 2);
    bool result = false;
    int cost = card.getCost();
    if ((card.getName() == "invalid card") || card.getName() == "Silence: Enchantment") {}

    // Minions ================================================================

    else if (types.find(card.getName())->second == "Minion") {
        if (actv.getSize("board") < 5) {
            AbstractMinion *m = new Minion{card.getName(),
                                           health.find(card.getName())->second,
                                           damage.find(card.getName())->second};
            actv.addMinion(m, "board");
            result = true;
            minEnterTrig(actv, inactv);
        }
    }

    // Spells =================================================================

    else if (card.getName() == "Banish") {
        string target_player;
        int targ_card;
        string target_card;
        get_bin() >> target_player;
        get_bin() >> target_card;
        if (target_card == "r") { targ_card = 6; }
        else { targ_card = stoi(target_card); }
        result = Banish(p1, p2, stoi(target_player), targ_card);
        if (result) resolve(actv, inactv);

    } else if (card.getName() == "Unsummon") {
        string target_player;
        string target_card;
        get_bin() >> target_player >> target_card;
        result = unsummon(p1, p2, stoi(target_player), stoi(target_card));
        if (result) {
            trigger("minion_exit_play", actv.getMinion(stoi(target_card), "board"), actv, inactv);
        }
    } else if (card.getName() == "Recharge") {

        try {
            result = recharge(actv, 3);
        } catch (...) {
            cout << "invalid argument" << endl;
        }

    } else if (card.getName() == "Disenchant") {
        string targetPlayer, targetMinion;
        get_bin() >> targetPlayer >> targetMinion;
        result = disenchant(p1, p2, stoi(targetPlayer), stoi(targetMinion));

    } else if (card.getName() == "Raise Dead") {
        result = raiseDead(actv);
        if (result) minEnterTrig(actv, inactv);
    } else if (card.getName() == "Blizzard") {
        result = blizzard(actv, inactv);
        resolve(actv, inactv);
    }


    // Rituals ================================================================

    else if ((card.getName() == "Dark Ritual") ||
             (card.getName() == "Aura of Power") ||
             (card.getName() == "Standstill")) {
        actv.setRitual(card.getName());
        result = true;
    }

    // Enchantments ===========================================================

    else if ((card.getName() == "Giant Strength") ||
             (card.getName() == "Enrage") ||
             (card.getName() == "Haste") ||
             (card.getName() == "Magic Fatigue") ||
             (card.getName() == "Silence")) {
        string e = card.getName();
        string targetPlayer, targetMinion;
        get_bin() >> targetPlayer >> targetMinion;

        AbstractMinion *m;
        if (stoi(targetPlayer) == 1) { m = p1.getMinion(stoi(targetMinion), "board"); }
        else { m = p2.getMinion(stoi(targetMinion), "board"); }

        if (e == "Giant Strength") { m = new GiantStrength(m); }
        else if (e == "Enrage") { m = new Enrage(m); }
        else if (e == "Haste") { m = new Haste(m); }
        else if (e == "Magic Fatigue") { m = new MagicFatigue(m); }
        else if (e == "Silence") { m = new Silence(m); }

        if (stoi(targetPlayer) == 1) {
            p1.giveMinion(stoi(targetMinion), "board");
            p1.setMinion(m, "board", stoi(targetMinion));
        } else {
            p2.giveMinion(stoi(targetMinion), "board");
            p2.setMinion(m, "board", stoi(targetMinion));
        }
       result = true;
    } else {
        cout << card.getName() << endl;
    }
    return result;
}


bool Standard::use(Player &actv, Player &inactv, Card card, AbstractMinion *m) {
    bool result = false;
    Player& p1 = getPlayer(actv, inactv, 1);
    Player& p2 = getPlayer(actv, inactv, 2);
    int cost = card.getCost();
    // Abilities ==============================================================

    if (card.getName() == "Novice Pyromancer: Ability") {
        string target_player;
        string target_min;
        get_bin() >> target_player >> target_min;
            result = novicePyromancerAbil(p1, p2, stoi(target_player), stoi(target_min));
            if (result) {
                m->setActions(m->getActions()-1);
             //   actv.setMagic(actv.getMagic() - cost);
                resolve(actv, inactv);
            }
    }
    else if (card.getName() == "Apprentice Summoner: Ability") {
        result = apprenticeSummonerAbil(actv);
        if(result) {
            m->setActions(m->getActions()-1);
           // actv.setMagic(actv.getMagic() - cost);
            minEnterTrig(actv, inactv);
        }
    }
    else if(card.getName() == "Master Summoner: Ability") {
        int num = masterSummonerAbil(actv);
        if(num > 0) {
            m->setActions(m->getActions()-1);
            result = true;
        }
       // actv.setMagic(actv.getMagic() - cost);
        int size = actv.getSize("board");
        for (int i = num; i > 0; i--) {
            trigger("fr_minion_enter_play", actv.getMinion(size-i+1,"board"), actv, inactv);
            trigger("op_minion_enter_play", actv.getMinion(size-i+1,"board"), actv, inactv);
            trigger("minion_enter_play",actv.getMinion(size-i+1,"board"), actv, inactv);
        }
    }
    return result;
}




void Standard::run_game() {
    int whosTurn = 1;
    string player1, player2;
    get_bin() >> player1 >> player2;
    Player p1{player1,20};
    Player p2{player2,20};
    std::ifstream read_deck1;
    read_deck1.open(this->getdeck1());
    std::ifstream read_deck2;
    read_deck2.open(this->getdeck2());
    string nextcard1;
    string nextcard2;
    while(getline(read_deck1,nextcard1) && getline(read_deck2,nextcard2)){
        p1.addCard(Card(costs.find(nextcard1)->second,nextcard1), "deck");
        p2.addCard(Card(costs.find(nextcard2)->second,nextcard2), "deck");
    }

    //shuffle the decks before giving to hand
    p1.shuffleCards("deck");
    p2.shuffleCards("deck");

    p1.draw_card(5);
    p2.draw_card(5);

    // Take turns back and forth
    bool cont = true;
    while(cont) {
        try {
            if (whosTurn == 1) { cont = take_turn(p1,p2); }
            if (whosTurn == 2) { cont = take_turn(p2,p1); }
            whosTurn = (whosTurn % 2) + 1;
        }
        catch(const WinCondition& condition) {
            std::cout << condition.read() << std::endl;
            break;
        }
        catch(...) {
            std::cout << "turn ended pre-maturely due to an error" << std::endl;
            //break;
        }
    }
}




// TestMode ===============================================
Testmode::Testmode(bool graphics, string deck1f, string deck2f, string init)
        : Match{ graphics, deck1f, deck2f, init } {}

Testmode::~Testmode() {}

void Testmode::run_game() {
    int whosTurn = 1;
    string player1, player2;
    get_bin() >> player1 >> player2;
    Player p1{player1,20};
    Player p2{player2,20};
    std::ifstream read_deck1;
    read_deck1.open(this->getdeck1());
    std::ifstream read_deck2;
    read_deck2.open(this->getdeck2());
    string nextcard1;
    string nextcard2;
    while(getline(read_deck1,nextcard1) && getline(read_deck2,nextcard2)) {
        p1.addCard(Card(costs.find(nextcard1)->second, nextcard1), "deck");
        p2.addCard(Card(costs.find(nextcard2)->second, nextcard2), "deck");
    }

    p1.draw_card(5);
    p2.draw_card(5);

    // Take turns back and forth
    bool cont = true;
    while(cont) {
        try {
            if (whosTurn == 1) { cont = take_turn(p1,p2); }
            if (whosTurn == 2) { cont = take_turn(p2,p1); }
            whosTurn = (whosTurn % 2) + 1;
        }
        catch(const WinCondition &condition) {
            std::cout << condition.read() << std::endl;
            break;
        }
        catch(...) {
            std::cout << "turn ended pre-maturely due to an error" << std::endl;
            //break;
        }
    }
}

bool Testmode::take_turn(Player& actv, Player& inactv) {
    actv.setMaxMagic(actv.getMaxMagic() + 1);//gets 1 magic
    actv.setMagic(actv.getMaxMagic());
    actv.setMinionAction();// reset minion actions
    int drawn = actv.draw_card(1);//draws card
    if(drawn == 0 && actv.getSize("deck")==0){
        declare_winner("out of cards",inactv.getName(), actv.getName());
    }
    trigger("start_of_turn",nullptr,actv,inactv);
    trigger("fr_start_of_turn",nullptr,actv,inactv);
    trigger("op_start_of_turn",nullptr,actv,inactv);
    while(true) {
           if (getGraphics() == true) { getGraphicDisplay().draw(actv, inactv); }
        string input;
        get_bin() >> input;
        if (input == "end") {break;}
        else if (input == "play") {
            string card;
            int card_num; //= stoi(card);
            get_bin() >> card;
            while(!tryParse(card,card_num)){
                std::cout << "Bad Input" << std::endl;
                get_bin() >> card;
            };
            try {
                if(actv.getCard(card_num,"hand").getCost() <= actv.getMagic()) {
                    Card temp = actv.getCard(stoi(card), "hand");
                    bool result = play(actv, inactv, temp);
                    if(result) actv.setMagic(actv.getMagic()-temp.getCost());
                }else {
                    Card temp = actv.getCard(stoi(card), "hand");
                    bool result = play(actv, inactv, temp);
                    if(result) actv.setMagic(0);
                }
                actv.giveCard(stoi(card), "hand");
            } catch (const std::out_of_range& e) {
                std::cout << "card doesn't exist" << std::endl;
            } catch(const std::invalid_argument& e){
                std::cout << "you entered an invalid argument" << std::endl;
            }

        }
        else if (input == "use") {
            get_bin() >> input;
            int min;
            while(!tryParse(input,min)){
                std::cout << "Bad Input" << std::endl;
                get_bin() >> input;
            };
            try {
                Card ability = actv.getMinion(min, "board")->use();
                if(actv.getMinion(min, "board")->getActions() > 0) {
                    if(ability.getCost() <= actv.getMagic()) {
                        bool result = use(actv, inactv, ability, actv.getMinion(min, "board"));
                        if(result) actv.setMagic(actv.getMagic()-ability.getCost());
                    } else {
                        bool result = use(actv, inactv, ability, actv.getMinion(min, "board"));
                        if(result) actv.setMagic(0);
                    }
                    resolve(actv,inactv);
                } else cout<<"not enough actions"<<endl;
            } catch (const std::out_of_range& e) {
                std::cout << "card doesn't exist" << std::endl;
            } catch(const std::invalid_argument& e){
                std::cout << "you entered an invalid argument" << std::endl;
            }
        }
        else if (input == "attack") {
            try {
                string min1, min2;
                get_bin().getline_bin(input);
                istringstream command{input};
                command >> min1;
                if (!command.eof()) {
                    command >> min2;
                } else {
                    min2 = "";
                }
                if (actv.getMinion(stoi(min1), "board")->getActions() > 0) {
                    AbstractMinion* m1 = actv.getMinion(stoi(min1),"board");
                    if(min2 == ""){
                        inactv.setHealth(inactv.getHealth()- m1->getDamage()) ;
                    }else {
                        AbstractMinion* m2 = inactv.getMinion(stoi(min2),"board");
                        m1->setHealth(m1->getHealth() - m2->getDamage());
                        m2->setHealth(m2->getHealth() - m1->getDamage());
                    }
                    actv.getMinion(stoi(min1), "board")->setActions(actv.getMinion(stoi(min1), "board")->getActions() - 1);
                    resolve(actv, inactv);
                } else cout << "not enough actions" << endl;

            } catch (const std::out_of_range& e) {
                std::cout << "card doesn't exist" << std::endl;
            } catch(const std::invalid_argument& e){
                std::cout << "you entered an invalid argument" << std::endl;
            }
        }
        else if (input == "print") {
            print_state_testing_tool(actv,inactv);
        }
        else if (input == "hand") {
            ASCIIDisplay hand(1);
            hand.reform_to_hand(actv);
            hand.print();
        }
        else if (input == "board") {
            ASCIIDisplay board(1);
            board.reform_to_board(actv,inactv);
            board.print();
        }
        else if (input == "inspect") {
            try {
                get_bin() >> input;
                int min = stoi(input);
                ASCIIDisplay inspection(1);
                inspection.reform_to_inspect(actv.getMinion(min,"board"));
                inspection.print();
            } catch (const std::out_of_range& e) {
                std::cout << "card doesn't exist" << std::endl;
            } catch(const std::invalid_argument& e){
                std::cout << "you entered an invalid argument" << std::endl;
            }
        }
        else if (input == "help") {
            std::cout << "Commands: help -- Display this message.\n" << std::endl;
            std::cout << "\t end -- End the current player’s turn.\n" << std::endl;
            std::cout << "\t quit -- End the game.\n" << std::endl;
            std::cout << "\t attack minion other-minion -- Orders minion to attack other-minion.\n" << std::endl;
            std::cout << "\t attack minion -- Orders minion to attack the opponent.\n" << std::endl;
            std::cout << "\t play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player.\n" << std::endl;
            std::cout << "\t use minion [target-player target-card] -- Use minion’s special ability, optionally targeting target-card owned by target-player.\n" << std::endl;
            std::cout << "\t inspect minion -- View a minion’s card and all enchantments on that minion." << std::endl;
            std::cout << "\t hand -- Describe all cards in your hand." << std::endl;
            std::cout << "\t board -- Describe all cards on the board." << std::endl;
        }
        else if (input == "surrender") { declare_winner("player_died",actv.getName(), inactv.getName()); }
        else if (input == "win") { if (inactv.getHealth() <= 0) { std::cout << "the fuck" << std::endl; declare_winner("player_died",actv.getName(), inactv.getName()); }
                                    else { std::cout << "thuf fuck" << std::endl; inactv.setHealth(0);}}
        else if (input == "quit") { declare_winner("game_end",actv.getName(), inactv.getName()); }
        else if(input == "discard"){
            string card;
            get_bin()>>card;
            actv.giveCard(stoi(card),"hand");
        }
        else if(input == "draw"){
            int drawn = actv.draw_card(1);
            if(drawn == 0) cout<<"Your hand is full or deck is empty."<<endl;
        }
    }
    trigger("end_of_turn",nullptr,actv,inactv);
    trigger("fr_end_of_turn",nullptr,actv,inactv);
    trigger("op_end_of_turn",nullptr,actv,inactv);
    // check to see if somebody won.
    if ((actv.getHealth() > 0) && (inactv.getHealth() > 0)) { return true; }
    return false;
}

bool Testmode::play(Player& actv ,Player& inactv,Card card) {
    Player &p1 = getPlayer(actv, inactv, 1);
    Player &p2 = getPlayer(actv, inactv, 2);
    bool result = false;
    if ((card.getName() == "invalid card") || card.getName() == "Silence: Enchantment") {}

        // Minions ================================================================

    else if (types.find(card.getName())->second == "Minion") {
        if (actv.getSize("board") < 5) {
            AbstractMinion *m = new Minion{card.getName(),
                                           health.find(card.getName())->second,
                                           damage.find(card.getName())->second};
            actv.addMinion(m, "board");
            result = true;
            minEnterTrig(actv, inactv);
        }
    }

        // Spells =================================================================

    else if (card.getName() == "Banish") {
        string target_player;
        int targ_card;
        string target_card;
        get_bin() >> target_player;
        get_bin() >> target_card;
        if (target_card == "r") { targ_card = 6; }
        else { targ_card = stoi(target_card); }
        result = Banish(p1, p2, stoi(target_player), targ_card);
        if (result) resolve(actv, inactv);

    } else if (card.getName() == "Unsummon") {
        string target_player;
        string target_card;
        get_bin() >> target_player >> target_card;
        result = unsummon(p1, p2, stoi(target_player), stoi(target_card));
        if (result) {
            trigger("minion_exit_play", actv.getMinion(stoi(target_card), "board"), actv, inactv);
        }
    } else if (card.getName() == "Recharge") {

        try {
            result = recharge(actv, 3);
        } catch (...) {
            cout << "invalid argument" << endl;
        }

    } else if (card.getName() == "Disenchant") {
        string targetPlayer, targetMinion;
        get_bin() >> targetPlayer >> targetMinion;
        result = disenchant(p1, p2, stoi(targetPlayer), stoi(targetMinion));

    } else if (card.getName() == "Raise Dead") {
        result = raiseDead(actv);
        if (result) minEnterTrig(actv, inactv);
    } else if (card.getName() == "Blizzard") {
        result = blizzard(actv, inactv);
        resolve(actv, inactv);
    }


        // Rituals ================================================================

    else if ((card.getName() == "Dark Ritual") ||
             (card.getName() == "Aura of Power") ||
             (card.getName() == "Standstill")) {
        actv.setRitual(card.getName());
        result = true;
    }

        // Enchantments ===========================================================

    else if ((card.getName() == "Giant Strength") ||
             (card.getName() == "Enrage") ||
             (card.getName() == "Haste") ||
             (card.getName() == "Magic Fatigue") ||
             (card.getName() == "Silence")) {
        string e = card.getName();
        string targetPlayer, targetMinion;
        get_bin() >> targetPlayer >> targetMinion;

        AbstractMinion *m;
        if (stoi(targetPlayer) == 1) { m = p1.getMinion(stoi(targetMinion), "board"); }
        else { m = p2.getMinion(stoi(targetMinion), "board"); }

        if (e == "Giant Strength") { m = new GiantStrength(m); }
        else if (e == "Enrage") { m = new Enrage(m); }
        else if (e == "Haste") { m = new Haste(m); }
        else if (e == "Magic Fatigue") { m = new MagicFatigue(m); }
        else if (e == "Silence") { m = new Silence(m); }

        if (stoi(targetPlayer) == 1) {
            p1.giveMinion(stoi(targetMinion), "board");
            p1.setMinion(m, "board", stoi(targetMinion));
        } else {
            p2.giveMinion(stoi(targetMinion), "board");
            p2.setMinion(m, "board", stoi(targetMinion));
        }
        result = true;
    } else {
        cout << card.getName() << endl;
    }
    return result;
}

bool Testmode::use(Player &actv, Player &inactv, Card card, AbstractMinion *m) {
    bool result = false;
    Player& p1 = getPlayer(actv, inactv, 1);
    Player& p2 = getPlayer(actv, inactv, 2);
    int cost = card.getCost();
    // Abilities ==============================================================

    if (card.getName() == "Novice Pyromancer: Ability") {
        string target_player;
        string target_min;
        get_bin() >> target_player >> target_min;
        result = novicePyromancerAbil(p1, p2, stoi(target_player), stoi(target_min));
        if (result) {
            m->setActions(m->getActions()-1);
            resolve(actv, inactv);
        }
    }
    else if (card.getName() == "Apprentice Summoner: Ability") {
        result = apprenticeSummonerAbil(actv);
        if(result) {
            m->setActions(m->getActions()-1);
            minEnterTrig(actv, inactv);
        }
    }
    else if(card.getName() == "Master Summoner: Ability") {
        int num = masterSummonerAbil(actv);
        if(num > 0) {
            m->setActions(m->getActions()-1);
            result = true;
        }
        int size = actv.getSize("board");
        for (int i = num; i > 0; i--) {
            trigger("fr_minion_enter_play", actv.getMinion(size-i+1,"board"), actv, inactv);
            trigger("op_minion_enter_play", actv.getMinion(size-i+1,"board"), actv, inactv);
            trigger("minion_enter_play",actv.getMinion(size-i+1,"board"), actv, inactv);
        }
    }
    return result;
}


// winCondition ================================
WinCondition::WinCondition(std::string condition, std::string winner, std::string loser) {
    if (condition == "game_end") {
        message = "The game was ended pre-maturely. There was no winner";
    } else if (condition == "player_died") {
        message = winner + " has slain " + loser +".";
    } else if (condition == "milled") {
        message = winner + " won because " + loser + " ran out of cards.";
    } else if (condition == "error_occured") {
        message = "there was an issue declaring the winner";
    } else if (condition == "out of cards"){
        message = loser + " is out of cards.";
    }
}

std::string WinCondition::read() const {
    std::string rtrn = message;
    // delete(this);
    return rtrn;
}


