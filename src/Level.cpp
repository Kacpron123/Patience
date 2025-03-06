#include "Level.h"
#include "Depot.h"
#include "Tableau.h"
#include "Stock.h"
#include "Foundation.h"
#include <algorithm>
#include <random>

int Level::_difficulty=1;
void Level::shuffle(){
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(_cards.begin(), _cards.end(), g);
}       
void Level::selectedPack::draw(sf::RenderTarget &target,sf::RenderStates states) const{
    if(toMouse){

    }
    else{
        
    }
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
void Level::loadLevel(std::string &&levelpath){
    srand(time(NULL));
    //Klondike
    for(int i=3;i>=0;i--){
        for(int j=12;j>=0;j--){
            _cards.push_back(new Card(Card::Rank(j),Card::Suit(i)));
            _cards.back()->setSize(80,120);
        }
    }
    shuffle();
    for(int i=0;i<7;i++){
        _depots.push_back(std::make_unique<Tableau>(sf::Vector2f(60+i*100,200),sf::Vector2f(0,35)));
        std::vector<std::unique_ptr<Card>> pack(
            std::make_move_iterator(_cards.begin()),
            std::make_move_iterator(_cards.begin()+i+1));
            _cards.erase(_cards.begin(),_cards.begin()+i+1);
            _depots.back()->fillDepot(pack);
        }
    _depots.push_back(std::make_unique<Stock>(sf::Vector2f(660,60)));
    std::vector<std::unique_ptr<Card>> pack(
        std::make_move_iterator(_cards.begin()),
        std::make_move_iterator(_cards.end()));
        _cards.clear();
        _depots.back()->fillDepot(pack);
    for(int i=0;i<4;i++){
        _depots.push_back(std::make_unique<Foundation>(sf::Vector2f(60+i*100,60)));
    }
    // for(auto &card: _depots.back()->_pile)
    //     card->scale(0.5,1.5);

}
void Level::resetLevel(){
    clean();
    loadLevel("correction");
}
void Level::clean(){
    for (auto &depot : _depots) {
        depot->_pile.clear();
    }
    _depots.clear();

    for (Card* card : _cards) {
        delete card;
        card = nullptr;
    }
    _cards.clear();
}
void Level::levelEvent(sf::Vector2i mousePos){
    for(auto &depot : _depots){
        int cardclicked=0;
        if(cardclicked=depot->clicked(mousePos)){
            if(cardclicked>0)
                depot->deletecard(cardclicked-1);
            continue;
        }
        //place back;
    }
}