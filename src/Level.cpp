#include "Level.h"

#include <algorithm>
#include <random>

int Level::_difficulty=1;
void Level::shuffle(){
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(_cards.begin(), _cards.end(), g);
}       

void Level::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    for(const auto &ptr: _depots)
        ptr->draw(target,states);
}
Level::Level(){
    
}
Level::~Level(){
    for(Card* card : _cards){
        delete card;
        card = nullptr;
    }
    _cards.clear();
}
#include <ctime>
void Level::loadLevel(std::string &&levelpath){
    srand(time(NULL));
    //Klondike
    for(int i=0;i<4;i++){
        for(int j=0;j<13;j++){
            _cards.push_back(new Card(Card::Rank(j),Card::Suit(i)));
            if(rand()%2)
                _cards.back()->Reverse();
            _cards.back()->setSize(80,120);
        }
    }
    shuffle();
    for(int i=0;i<7;i++){
        _depots.push_back(std::make_unique<Depot>(sf::Vector2f(60+i*100,100),sf::Vector2f(0,35)));
        std::vector<std::unique_ptr<Card>> pack(
            std::make_move_iterator(_cards.begin()),
            std::make_move_iterator(_cards.begin()+i+1));
        _cards.erase(_cards.begin(),_cards.begin()+i+1);
        _depots.back()->place_pack(pack);
    }
    for(auto &card: _depots.back()->_pile)
        card->scale(0.5,1.5);

}
void Level::resetLevel(){
    for (auto &depot : _depots) {
        depot->_pile.clear();
    }
    _depots.clear();

    for (Card* card : _cards) {
        delete card;
        card = nullptr;
    }
    _cards.clear();
    loadLevel("correction");
}
void Level::levelEvent(sf::Vector2i mousePos){
    for(auto &depot : _depots){
        if(depot->clicked(mousePos)){
            //depot->place_pack(Depot::_pack);
            // break;
        }
    }
}