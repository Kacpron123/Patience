#include "Stock.h"
#include "Hand.h"
#include "Level.h"
#include "Tableau.h"
#include "Menu.h"

Stock::Stock(sf::Vector2f position): Depot(position,{0,0}), m_bigrotate(0){
   m_wasteposition={position.x-100,position.y};
   m_baseTile.setTexture("resources/card_blank.png");
   m_baseTile.setSize(80,120);
   m_baseTile.setPosition(getPosition().x,getPosition().y);
   drawtile=!Level::getFlags().s_stockdeal;
}
void Stock::createDepot(std::vector<std::unique_ptr<Card>> &pack){
   Depot::fillDepot(pack);
   m_bigrotate=size()-1;
   for(int i=0;i<size();i++){
      _pile[i]->reverse();
   }
   //TODO make drawing only 10 cards
}
void Stock::draw(sf::RenderTarget & target,sf::RenderStates states) const{
   if(drawtile)
      m_baseTile.draw(target,states);
   Depot::draw(target,states);
}
int Stock::clicked(const sf::Vector2i &mousePos){
   if(!empty()){
      sf::Vector2f rightdowncornerofbase=_pile[0]->getSize();
      //stock auto dealing
      if(Level::getFlags().s_stockdeal){
         if(!(mousePos.x >= m_position.x && mousePos.x <= m_position.x + rightdowncornerofbase.x && mousePos.y >= m_position.y && mousePos.y <= m_position.y + rightdowncornerofbase.y))
            return -2;
         Depot &sender=Hand::getInstance().getSender();
         if(&sender){
            Hand::getInstance().deselectDepot();
            sender.draw(Menu::getWindow(),sf::RenderStates::Default);
            Menu::getWindow().display();
         }
         std::vector<Tableau*> tableaus;
         for(auto &depot: Level::getInstance().m_depots){
            Tableau* tableau=dynamic_cast<Tableau*>(depot.get());
            if(tableau)
               tableaus.push_back(tableau);
         }
         int n=std::min(tableaus.size(),size());
         Hand &hand=Hand::getInstance();
         for(int i=0;i<n;i++){
            hand.selectDepot(this,size()-1);
            _pile[size()-1]->reverse();
            Depot::piletopile(this,size()-1,tableaus[i],true);
            (*tableaus[i])[tableaus[i]->size()-1].draw(Menu::getWindow(),sf::RenderStates::Default);
            sf::sleep(sf::milliseconds(60));
            Menu::getWindow().display();
            //TODO making Menu::draw
         }

         return -2;
      }
      if(mousePos.x>=m_wasteposition.x && mousePos.x<=m_wasteposition.x+rightdowncornerofbase.x  && mousePos.y>=m_wasteposition.y && mousePos.y<=m_wasteposition.y+rightdowncornerofbase.y)
         {
            if(m_bigrotate==size()-1)
               return -2;
            return size()-1;
         }   
      if(mousePos.x>=m_position.x && mousePos.x<=m_position.x+rightdowncornerofbase.x  && mousePos.y>=m_position.y && mousePos.y<=m_position.y+rightdowncornerofbase.y)
         {
            rotate();
            return -2;
         }
   }
   return -2;
}
void Stock::rotate(){
   if(m_bigrotate>=0){
      _pile[size()-1]->deselect();
      int n=size()-1;
      for(int i=m_bigrotate;i<n;i++)
      std::swap(_pile[i],_pile[i+1]);
      m_bigrotate--;
      _pile[size()-1]->reverse();
      _pile[size()-1]->setPosition(m_wasteposition.x,m_wasteposition.y);
   }
   else{
      _pile[size()-1]->deselect();
      int n=size()-1;
      for(int i=0;i<n/2;i++)
         std::swap(_pile[i],_pile[n-i]);
      for(auto &card: _pile){
         card->reverse();
         card->setPosition(m_position.x,m_position.y);
      }
      m_bigrotate=size()-1;
   }
}
bool Stock::piletohand(){
   return true;
}
bool Stock::handtopile(){
   //stock cannot accept card;
   return false;
}
void Stock::updatesender(){
   if(m_bigrotate==size())
      m_bigrotate--;
}
void Stock::updatereceiver(){}