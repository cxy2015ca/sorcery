#include "player.h"

int Player::players = 0;

Player::Player(string n, int i): rit{"none"} {
    name = n;
    player_num = players +1;
    players += 1;
    health = 20;
    magic = 3;
    maxMagic = 3;
}

Player::~Player() {
    for(auto x:board){
        delete x;
    }
    for(auto x:grave) {
        delete x;
    }
}

//*******************  player get set functions   ***********

string Player::getName() const {
    return name;
}

void Player::setName(string s) {
    name = s;
}

int Player::getHealth() const {
    return health;
}

void Player::setHealth(int n) {
    health = n;
}

void Player::setRitual(string r) {
    rit = Ritual(r);
}

Ritual& Player::getRitual() {
    return rit;
}

int Player::getMagic() const {
    return magic;
}

void Player::setMagic(int n) {
    magic = n;
}

int Player::getPlayerNum() {
    return player_num;
}

void Player::setMaxMagic(int i){
    maxMagic = i;
}

int Player::getMaxMagic() {
    return maxMagic;
}

//*******************  vector manip  ***************************

int Player::getSize(string s) const {
    if (s == "deck") return deck.size();
    if (s == "hand") return hand.size();
    if (s == "board") return board.size();
    if (s == "grave") return grave.size();
    return -1;
}

void Player::addCard(Card c, string s) {
    if (s == "deck") deck.push_back(c);
    if (s == "hand") hand.push_back(c);
}

void Player::addMinion(AbstractMinion* m, string s) {
    if (s == "board") board.push_back(m);
    if (s == "grave") grave.push_back(m);
}

Card& Player::getCard(int n, string s) {
    if (s == "deck") return deck.at(n - 1);
    if (s == "hand") return hand.at(n - 1);
    //return Card(0, "invalid card");
}

AbstractMinion* Player::getMinion(int n, string s) {
    if (s == "board") return board.at(n - 1);
    if (s == "grave") return grave.at(n - 1);
}

void Player::setMinion(AbstractMinion* m, string s, int i) {
    if (s == "board") { board.insert(board.begin() + i - 1, m); }
    if (s == "grave") { grave.insert(board.begin() + i - 1, m); }
}

Card Player::giveCard(int n, string s) {
    if (s == "deck") {
        Card c = deck.at(n - 1);
        deck.erase(deck.begin() + n - 1);
        deck.shrink_to_fit();
        return c;
    }
    if (s == "hand") {
        Card c = hand.at(n - 1);
        hand.erase(hand.begin() + n - 1);
        hand.shrink_to_fit();
        return c;
    }
    return Card(0, "invalid card");
}

AbstractMinion* Player::giveMinion(int n, string s) {
    if (s == "board") {
        AbstractMinion *c = board.at(n - 1);
        board.erase(board.begin() + n - 1);
        board.shrink_to_fit();
        return c;
    }
    if (s == "grave") {
        AbstractMinion *c = grave.at(n - 1);
        grave.erase(grave.begin() + n - 1);
        grave.shrink_to_fit();
        return c;
    }
    //return Card(0, "invalid card");
}

void Player::setCard(int i, Card c, string s) {
    if (s == "deck") deck.insert(deck.begin() + i - 1, c);
    if (s == "hand") hand.insert(hand.begin() + i - 1, c);
}

void Player::setCard(int i, AbstractMinion *c, string s) {
    if (s == "board") board.insert(board.begin() + i - 1, c);
    if (s == "grave") grave.insert(grave.begin() + i - 1, c);
}

void Player::shuffleCards(string s) {
    if (s=="deck") std::random_shuffle(deck.begin(), deck.end());
    if (s=="hand") std::random_shuffle(hand.begin(), hand.end());
}

// check magic  =========================================
bool Player::checkMagic(int cost) {
    if (cost > magic) return false;
    return true;
}

bool Player::checkAction(int cost, int ith) {
    AbstractMinion* min = getMinion(ith, "board");
    if (cost > min->getActions()) return false;
    return true;
}

void Player::setMinionAction() {
    for(int i = 1; i <= getSize("board"); i++){
        this->getMinion(i, "board")->setActions(this->getMinion(i, "board")->getMaxActions());
    }
}




// adding cards and attacking =================================================



// draw card from deck, returns actual amount drawn
int Player::draw_card(int n) {
    int i = 0;
    for (;(i < n && this->getSize("hand") < 5 && this->getSize("deck")>0); i++) {
        this->addCard(this->giveCard(this->getSize("deck"), "deck"),"hand");
    }
    return i;
}
