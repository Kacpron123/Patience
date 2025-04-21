#include "Level.h"
#include "Depot.h"
#include "Tableau.h"
#include "Stock.h"
#include "Hand.h"
#include "Foundation.h"
#include <algorithm>
#include <random>

Level::flags Level::s_flags;
Level* Level::instance=nullptr;
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
    flags f{1,1};
    setFlags(f);
}
Level::~Level(){
    cleanLevel();
}


void Level::loadLevel(std::string &&levelpath){
    
    Card::setdefaultSize({60,90});
    int start=0;
    // //Klondike hard coded
    // flags &f=getFlags();
    // f.m_difficulty=3;
    // f.m_placingtype=3;
    // Tableau::setanyplaceable(false);
    // srand(time(NULL));
    // for(int i=3;i>=0;i--){
    //     for(int j=12;j>=0;j--){
    //         m_cards.push_back(new Card(Card::Rank(j),Card::Suit(i)));
    //         m_cards.back()->setSize(80,120);
    //     }
    // }
    // shuffle();
    // for(int i=0;i<7;i++){
    //     m_depots.push_back(std::make_unique<Tableau>(sf::Vector2f(60+i*100,200),sf::Vector2f(0,20)));
    //     std::vector<std::unique_ptr<Card>> pack(
    //         std::make_move_iterator(m_cards.begin()+start),
    //         std::make_move_iterator(m_cards.begin()+start+i+1));
    //         // m_cards.erase(m_cards.begin(),m_cards.begin()+start+i+1);
    //         m_depots.back()->createDepot(pack);
    //         start+=i+1;
    //     }
    // m_depots.push_back(std::make_unique<Stock>(sf::Vector2f(660,60)));
    // std::vector<std::unique_ptr<Card>> pack(
    //     std::make_move_iterator(m_cards.begin()+start),
    //     std::make_move_iterator(m_cards.end())); 
    // // m_cards.clear();
    // m_depots.back()->createDepot(pack);
    // for(int i=0;i<4;i++){
    //     m_depots.push_back(std::make_unique<Foundation>(sf::Vector2f(60+i*100,60)));
    // }

    //Solitaire Spider hard coded
    flags &f=getFlags();
    f.m_placingtype=1;
    f.s_autocollect=true;
    f.s_stockdeal=true;
    f.tableauplaceany=true;
    srand(time(NULL));
    for(int w=2;w--;)
    // //simple (one color)
    // f.m_difficulty=1;
    // for(int i=0;i<4;i++)
    //     for(int j=0;j<13;j++)
    //         m_cards.push_back(new Card(Card::Rank(j),Card::Suit::Clubs));
    // //two colors
    for(int i=0;i<4;i++)
        for(int j=0;j<13;j++)
            m_cards.push_back(new Card(Card::Rank(j),i%2));
    f.m_difficulty=2;

    // //four colors
    // for(int i=0;i<4;i++)
    //     for(int j=0;j<13;j++)
    //         m_cards.push_back(new Card(Card::Rank(j),i));
    shuffle();
    for(int i=0;i<10;i++){
        auto tableau = std::make_shared<Tableau> (sf::Vector2f(10+i*80,100),sf::Vector2f(0,20));
        std::vector<std::unique_ptr<Card>> pack(
            std::make_move_iterator(m_cards.begin()+start),
            std::make_move_iterator(m_cards.begin()+start+5+(i<4)));
            // m_cards.erase(m_cards.begin(),m_cards.begin()+start+5+(i<4));
            tableau->createDepot(pack);
            start+=5+(i<4);
            m_depots.push_back(tableau);
            m_tableau.push_back(tableau);
        }
    m_depots.push_back(std::make_shared<Stock>(sf::Vector2f(710,450)));
    std::vector<std::unique_ptr<Card>> pack(
        std::make_move_iterator(m_cards.begin()+start),
        std::make_move_iterator(m_cards.end())); 
    m_depots.back()->createDepot(pack);

    for(int i=0;i<8;i++){
        auto foundation=std::make_shared<Foundation>(sf::Vector2f(10+10*i,450));
        m_depots.push_back(foundation);
        m_foundation.push_back(foundation);
    }
    //m_cards.clear();

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
    m_cards.clear();
}
void Level::levelEvent(sf::Vector2i mousePos){
    if(mousePos.x>=0&&mousePos.x<=80&&mousePos.y>=0&&mousePos.y<=80){
        resetLevel();
        return;
    }
    Hand &hand = Hand::getInstance();
    // if(mousePos.x<20 && mousePos.y<20){

    //     std::cout<<"resize\n";
    //     for(Card* card: m_cards){
    //         card->setSize(40,60);
    //     }
    // }
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
                    if(cardclicked==depot->size()-1 && &hand.getSender()!= depot.get())
                        Depot::piletopile(&hand.getSender(),hand.getPlace(),depot.get());
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