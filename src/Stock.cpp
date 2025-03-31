#include "Stock.h"
#include "Hand.h"

Stock::Stock(sf::Vector2f position): Depot(position,{0,0}), m_bigrotate(0){
   m_wasteposition={position.x-100,position.y};
   m_baseTile.setTexture("resources/card_blank.png");
   m_baseTile.setSize(80,120);
   m_baseTile.setPosition(getPosition().x,getPosition().y);
}
void Stock::createDepot(std::vector<std::unique_ptr<Card>> &pack){
   Depot::fillDepot(pack);
   m_bigrotate=size()-1;
   for(int i=0;i<size();i++){
      _pile[i]->reverse();

   }
   // _pile[m_bigrotate]->setPosition(m_wasteposition.x,m_wasteposition.y);
   
}
void Stock::draw(sf::RenderTarget & target,sf::RenderStates states) const{
   m_baseTile.draw(target,states);
   Depot::draw(target,states);
}
int Stock::clicked(const sf::Vector2i &mousePos){
   if(!empty()){
      sf::Vector2f rightdowncornerofbase=_pile[0]->getSize();
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
      for(int i=m_bigrotate;i<size()-1;i++)
      std::swap(_pile[i],_pile[i+1]);
      m_bigrotate--;
      _pile[size()-1]->reverse();
      _pile[size()-1]->setPosition(m_wasteposition.x,m_wasteposition.y);
   }
   else{
      _pile[size()-1]->deselect();
      int n=size()-1;
      for(int i=0;i<=n/2;i++)
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