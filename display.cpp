#include "display.h"

const int max_min = 5;
const int card_height = 11;
const int card_width = 33;
const char VBC = '|'; //Vertical Border Char
const char HBC = '-'; //Horizontal Border Char
const string space = " ";


Player& getPlayer(Player& actv,Player& inactv,int p) {
    if (actv.getPlayerNum() == p) {return actv;}
    else { return inactv; }
}

string create_line(char c, int num) {
    string str;
    for (int i = 0; i < num; i++){
        str += c;
    }
    return str;
}

ASCIIDisplay::ASCIIDisplay(string type) {
    if (type == "full_blank") {
        for (int i = 0; i < card_height; i++){
            line.push_back(create_line(' ',card_width));
        }
    }
    else if (type == "full_line_blank") {
        for (int i = 0; i < card_height; i++){
            line.push_back(create_line(' ',card_width*5));
        }
    }
    else if (type == "semi_blank") {
        for (int i = 0; i < card_height; i++){
            line.push_back(VBC + create_line(' ', card_width-2) + VBC);
        }
        line[0] = VBC + create_line('-',card_width-2) + VBC;
        line[card_height -1] = VBC + create_line('-',card_width-2) + VBC;
    }
}

ASCIIDisplay::ASCIIDisplay(int lines) {
    for (int i = 0; i < lines; i++){
        line.push_back("");
    }
}



void ASCIIDisplay::print() {
    for(int i = 0; i < line.size(); i ++) {
        cout << line[i] << endl;
    }
}

int ASCIIDisplay::getSize() {
    return line.size();
}

string ASCIIDisplay::getLine(int n) {
    return line[n];
}

void ASCIIDisplay::add(ASCIIDisplay& other, int offset) {
    if (offset + other.getSize() > getSize()) {
        while (offset + other.getSize() > getSize()) {
            line.emplace_back("");
        }
    }
    for (int i = 0; i < other.getSize(); i++) {
        line[i+offset] += other.getLine(i);
    }
}


void ASCIIDisplay::reform_to_board(Player & actv, Player & inactv) {
    Player& p1 = getPlayer(actv,inactv,1);
    Player& p2 = getPlayer(actv,inactv,2);
    line.clear();
    for (int i = 0; i < card_height*5 + 2; i++){
        line.push_back("|");
    }
    line[0] += create_line('-',(card_width*max_min));
    int num_min1 = 0;
    int num_min2 = 0;
    ASCIIDisplay space("full_blank");
    ASCIIDisplay semispace("semi_blank");
    ASCIIDisplay plr1(p1);
    ASCIIDisplay plr2(p2);
    Ritual& p1rit = p1.getRitual();
    Ritual& p2rit = p2.getRitual();
    ASCIIDisplay rit1(1);
    ASCIIDisplay rit2(1);
    ASCIIDisplay grave1(1);
    ASCIIDisplay grave2(1);
    if (p1rit.getCard().getName() != "invalid card") {
        ASCIIDisplay newrit1(p1rit);
        rit1.add(newrit1,0);
    } else {
        rit1.add(semispace,0);
    }
    if (p2rit.getCard().getName() != "invalid card") {
        ASCIIDisplay newrit2(p2rit);
        rit2.add(newrit2,0);
    } else {
        rit2.add(semispace,0);
    }
    if (p1.getSize("grave") != 0) {
        ASCIIDisplay newgrv(p1.getMinion(p1.getSize("grave"),"grave"));
        grave1.add(newgrv,0);
    } else {
        grave1.add(semispace,0);
    }
    if (p2.getSize("grave") != 0) {
        ASCIIDisplay newgrv(p2.getMinion(p2.getSize("grave"),"grave"));
        grave2.add(newgrv,0);
    } else {
        grave2.add(semispace,0);
    }
    add(rit1,1); add(space,1); add(plr1,1); add(space,1); add(grave1,1);
    for(int i = 1; i <= p1.getSize("board"); i++){
        ASCIIDisplay m1(p1.getMinion(i,"board"));
        if (i <= max_min) { add(m1,card_height+1); };
        num_min1 += 1;
    }
    for(int i = 0; i < max_min - num_min1; i++){
        add(semispace,card_height+1);
    }
    for(int i = 0; i < max_min; i++){
        add(space,(card_height*2)+1);
    }
    for(int i = 1; i <= p2.getSize("board"); i++){
        ASCIIDisplay m2(p2.getMinion(i,"board"));
        if (i <= max_min) { add(m2,(card_height*3)+1); };
        num_min2 += 1;
    }
    for(int i = 0; i < max_min - num_min2; i++){
        add(semispace,(card_height*3)+1);
    }
    add(rit2,(card_height*4)+1); add(space,(card_height*4)+1);
    add(plr2,(card_height*4)+1);
    add(space,(card_height*4)+1); add(grave2,(card_height*4)+1);
    line[56] += create_line('-',(card_width*max_min));
    for (int i = 0; i < 57; i++){
        line[i] += VBC;
    }
}


void ASCIIDisplay::reform_to_hand(Player& p) {
    line.clear();
    ASCIIDisplay card_holder(1);
    for(int i = 1; i <= p.getSize("hand"); i++){
        ASCIIDisplay next(p.getCard(i, "hand"));
        card_holder.add(next,0);
    }
    this->add(card_holder,0);
}

void ASCIIDisplay::reform_to_inspect(AbstractMinion* m) {
    line.clear();
    ASCIIDisplay card_holder(1);
    ASCIIDisplay minion(m);
    card_holder.add(minion,0);
    istringstream iss{m->getEnchant()};
    string next;
    getline(iss,next);
    int offset = 0;
    int count = 0;
    while (next != "base") {
        if ((count % 5) == 0) { offset += card_height; }
        Card temp_card{costs.find(next)->second,next};
        ASCIIDisplay ench(temp_card);
        card_holder.add(ench,offset);
        count += 1;
        getline(iss,next);
    }
    this->add(card_holder,0);
}

ASCIIDisplay::ASCIIDisplay(vector<string> card_template){
    line = card_template;
}


ASCIIDisplay::ASCIIDisplay(Player& plr) {
    line = display_player_card(plr.getPlayerNum(),plr.getName(),
                               plr.getHealth(),plr.getMagic());
}

ASCIIDisplay::ASCIIDisplay(Ritual& rit) {
    string name = rit.getCard().getName();
    line = display_ritual(rit.getCard().getName(),
                          costs.find(name)->second,
                          abilitys.find(name)->second.getCost(),
                          descriptions.find(name)->second,
                          rit.getCharge());
}


ASCIIDisplay::ASCIIDisplay(Card& card) {

    int cost = card.getCost();
    string name = card.getName();
    string type = types.find(name)->second;

    if (type == "Ritual") {
        line = display_ritual(name,cost,
                              abilitys.find(name)->second.getCost(),
                              descriptions.find(name)->second,
                              charges.find(name)->second);
    } else if (type == "Minion") {
        string next_line;
        string desc;
        int attack = damage.find(name)->second;
        int defense = health.find(name)->second;
        string abil = abilitys.find(name)->second.getName();
        int abil_cost;
        string trig = trigger_list.find(name)->second.getTriggerSpell();
        if (abil != "invalid card") {
            desc = descriptions.find(abil)->second;
            abil_cost = abilitys.find(name)->second.getCost();
            line = display_minion_activated_ability(name,cost,attack,defense,abil_cost,desc);
        } else if (trig != "invalid card") {
            desc = descriptions.find(trig)->second;
            line = display_minion_triggered_ability(name,cost,attack,defense,desc);
        } else {
            line = display_minion_no_ability(name,cost,attack,defense);
        }
    } else if (type == "Enchantment") {
        string desc = descriptions.find(name)->second;
        if (name == "Giant Strength") {
            line = display_enchantment_attack_defence(name,cost,desc,"+2","+2");
        } else if (name == "Enrage") {
            line = display_enchantment_attack_defence(name,cost,desc,"*2","*2");
        } else {
            line = display_enchantment(name,cost,desc);
        }
    } else if (type == "Spell") {
        string desc = descriptions.find(name)->second;
        line = display_spell(name,cost,desc);
    }
}


ASCIIDisplay::ASCIIDisplay(AbstractMinion* m) {
    for (int i = 0; i < card_height; i++){
        line.push_back("");
    }


    string name = m->getName();
    int name_len = name.length();
    string type = types.find(name)->second;
    int type_len = type.length();
    string cost = to_string(costs.find(name)->second);
    int cost_len = cost.length();

    line[0] += VBC + create_line(HBC,(card_width -2)) + VBC;
    line[1] += VBC + space + name + create_line(' ',(card_width - name_len - 9))
               + VBC + create_line(' ', 4 - cost_len) + cost + space + VBC;
    line[2] += VBC + create_line(HBC,(card_width -2)) + VBC;
    line[3] += VBC + create_line(' ',card_width - type_len - 3) + type + space + VBC;
    line[4] += VBC + create_line(HBC,(card_width -2)) + VBC;

    //part II

    string next_line;
    string desc;
    string attack = to_string(m->getDamage());
    int atk_len = attack.length();
    string defense = to_string(m->getHealth());
    int def_len = defense.length();
    string abil = m->getAbil(m->getSize("abilities")).getName();
    string abil_cost;
    int abil_cost_len;
    string trig;
    if (abil != "invalid card") {
        desc = descriptions.find(abil)->second;
        abil_cost = to_string(m->getAbil(m->getSize("abilities")).getCost());
        abil_cost_len = abil_cost.length();
    } else {
        trig = m->getTrig(m->getSize("triggers")).getTriggerSpell();
        desc = descriptions.find(trig)->second;
    }
    for (int i = 5; i < 7; i++) {
        int indent = 0;
        if (abil != "invalid card") {
            if (i == 5) {
                line[i] += VBC + space + abil_cost + create_line(' ', 4 - abil_cost_len) + VBC + space;
            } else if (i == 6) {
                line[i] += VBC + create_line('-', 6) + space;
            }
            else { line[i] += VBC + space; }
            indent = 10;
        }
        else {
            indent = 4;
            line[i] += VBC + space;
        }
        if (desc.length() > (card_width - indent)) {
            next_line = desc.substr(0,(card_width - indent));
            desc = desc.substr((card_width - indent),desc.length() - (card_width - indent));
        } else {
            next_line = (desc + create_line(' ',(card_width-indent) - desc.length()));
            desc = "";
        }
        line[i] += next_line + space + VBC;
    }
    for (int i = 7; i < (card_height -3); i++) {
        line[i] += VBC + space;
        if (desc.length() > (card_width - 4)) {
            next_line = desc.substr(0,(card_width - 4));
            desc = desc.substr((card_width - 4),desc.length() - (card_width - 4));
        } else {
            next_line = (desc + create_line(' ',(card_width-4) - desc.length()));
            desc = "";
        }
        line[i] += next_line + space + VBC;
    }
    line[card_height - 3] += VBC + create_line('-',6) + create_line(' ',card_width - 14) + create_line('-', 6)
                             + VBC;
    line[card_height - 2] += VBC + space + attack + create_line(' ',4 - atk_len) + VBC +
                             create_line(' ',card_width - 14) + VBC + create_line(' ', 4 - def_len) + defense + space + VBC;
    line[card_height - 1] += VBC + create_line(HBC,(card_width -2)) + VBC;
}
