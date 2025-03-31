#include "Level.h"
#include "Depot.h"
#include "Tableau.h"
#include "Stock.h"
#include "Hand.h"
#include "Foundation.h"
#include <algorithm>
#include <random>

int Level::m_difficulty;
int Level::m_placingtype;
void Level::shuffle(){
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(m_cards.begin(), m_cards.end(), g);
}       
void Level::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    for(const auto &ptr: m_depots)
        ptr->draw(target,states);
}
Level::Level(){
}
Level::~Level(){
    cleanLevel();
}
void Level::loadLevel(std::string &&levelpath){
    m_difficulty=3;
    m_placingtype=3;
    srand(time(NULL));
    //Klondike hard coded
    for(int i=3;i>=0;i--){
        for(int j=12;j>=0;j--){
            m_cards.push_back(new Card(Card::Rank(j),Card::Suit(i)));
            m_cards.back()->setSize(80,120);
        }
    }
    shuffle();
    for(int i=0;i<7;i++){
        m_depots.push_back(std::make_unique<Tableau>(sf::Vector2f(60+i*100,200),sf::Vector2f(0,20)));
        std::vector<std::unique_ptr<Card>> pack(
            std::make_move_iterator(m_cards.begin()),
            std::make_move_iterator(m_cards.begin()+i+1));
            m_cards.erase(m_cards.begin(),m_cards.begin()+i+1);
            m_depots.back()->createDepot(pack);
        }
    m_depots.push_back(std::make_unique<Stock>(sf::Vector2f(660,60)));
    std::vector<std::unique_ptr<Card>> pack(
        std::make_move_iterator(m_cards.begin()),
        std::make_move_iterator(m_cards.end())); 
        m_cards.clear();
        m_depots.back()->createDepot(pack);
    for(int i=0;i<4;i++){
        m_depots.push_back(std::make_unique<Foundation>(sf::Vector2f(60+i*100,60)));
    }

}
void Level::resetLevel(){
    // TODO: contain seed to restart game with same cards
    cleanLevel();
    loadLevel("correction");
    Hand::getInstance().deselectDepot();
}
void Level::cleanLevel(){
    for (auto &depot : m_depots) {
        depot->clearDepot();
    }
    m_depots.clear();

    for (Card* card : m_cards) {
        delete card;
        card = nullptr;
    }
    m_cards.clear();
}
void Level::levelEvent(sf::Vector2i mousePos){
    if(mousePos.x>=0&&mousePos.x<=80&&mousePos.y>=0&&mousePos.y<=80){
        resetLevel();
        return;
    }
    Hand &hand = Hand::getInstance();
    for(auto &depot : m_depots){
        int cardclicked=0;
        if((cardclicked=depot->clicked(mousePos))>=-1){
            if(cardclicked>=0){
                if(!hand.isSelected()){
                    if(depot->correctPack(cardclicked) && (*depot)[cardclicked].getHeadup()){
                        int n=depot->size()-cardclicked;
                        while(n--){
                            hand.selectDepot(depot.get(),cardclicked);
                            (*depot)[cardclicked+n].select();
                        }
                        return;
                    }
                    
                }
                else{
                    if(cardclicked==depot->size()-1 && &hand.getSender()!= depot.get()){
                        Depot::piletopile(&hand.getSender(),hand.getPlace(),depot.get());
                    }
                    hand.deselectDepot();
                }
            }
            else if(cardclicked==-1 && hand.isSelected()){
                Depot::piletopile(&hand.getSender(),hand.getPlace(),depot.get());
            }
            hand.deselectDepot();
        }
    }
    hand.deselectDepot();
}