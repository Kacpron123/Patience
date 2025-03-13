#include "Level.h"
#include "Depot.h"
#include "Tableau.h"
#include "Stock.h"
#include "Foundation.h"
#include <algorithm>
#include <random>

int Level::m_difficulty;
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
    cleanLevel();
}
void Level::loadLevel(std::string &&levelpath){
    Level::m_difficulty=1;
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
    cleanLevel();
    loadLevel("correction");
    Hand::getInstance().deselectDepot();
}
void Level::cleanLevel(){
    for (auto &depot : _depots) {
        depot->clearDepot();
    }
    _depots.clear();

    for (Card* card : _cards) {
        delete card;
        card = nullptr;
    }
    _cards.clear();
}
#include <iostream>
void Level::levelEvent(sf::Vector2i mousePos){
    if(mousePos.x>=0&&mousePos.x<=80&&mousePos.y>=0&&mousePos.y<=80){
        std::cout<<"reset\n";
        resetLevel();
        return;
    }
    Hand &hand = Hand::getInstance();
    for(auto &depot : _depots){
        int cardclicked=0;
        if((cardclicked=depot->clicked(mousePos))>=-1){
            if(cardclicked>=0){
                // std::cout<<"clicked "<<cardclicked<<"\n";
                if(!hand.isSelected()){
                    if(depot->correctPack(cardclicked)){
                        // std::cout<<"correct\n";
                        int n=depot->size()-cardclicked;
                        while(n--){
                            hand.selectDepot(depot.get(),cardclicked);
                            hand.print();
                            (*depot)[cardclicked+n].select();
                            // sf::sleep(sf::milliseconds(800));
                            // hand.deselectDepot();
                            // depot->deletecard(cardclicked);
                        }
                        return;
                    }
                    
                }
                else{
                    if(cardclicked==depot->size()-1){
                        std::cout<<"placing\n";
                        // && (*depot)[cardclicked]<hand[0]
                        Depot::piletopile(hand.getSender(),hand.getPlace(),depot.get());
                        // Hand::getInstance().piletoPile(depot.get());
                        // depot->handtopile();
                        // depot->deletecard(cardclicked-1);
                    }
                    hand.deselectDepot();
                }
                // else
            }
            else if(cardclicked==-1 && hand.isSelected()){
                Depot::piletopile(hand.getSender(),hand.getPlace(),depot.get());
                hand.deselectDepot();
            }
        }
        //place back;
    }
    hand.deselectDepot();
}