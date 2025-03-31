#include "Foundation.h"
#include "Hand.h"

Foundation::Foundation(sf::Vector2f position): Depot(position,{0,0}){
   m_foundationCard.setTexture("resources/card_foundation.png");
   m_foundationCard.setSize(80,120);
   m_foundationCard.setPosition(getPosition().x,getPosition().y);
}
void Foundation::draw(sf::RenderTarget &target,sf::RenderStates states) const{
   m_foundationCard.draw(target,states);
   if(!empty())
      _pile.back()->draw(target,states);
}
int Foundation::clicked(const sf::Vector2i &mousePos){
   sf::Vector2f rightdowncornerofbase=m_foundationCard.getPosition()+static_cast<sf::Vector2f>(m_foundationCard.getSize());
   if(mousePos.x>=m_foundationCard.getPosition().x && mousePos.x<=rightdowncornerofbase.x  && mousePos.y>=m_foundationCard.getPosition().y && mousePos.y<=rightdowncornerofbase.y){
      if(empty())
         return -1;
      return size()-1;
   }
   return -2;
}
void Foundation::scale(float x,float y){
   m_foundationCard.scale(x,y);
   Depot::scale(x,y);
}
bool Foundation::piletohand(){
   return true;
}
bool Foundation::handtopile(){
   Hand &hand=Hand::getInstance();
   if(hand.size()!=1)
      return false;
   const Card& tophand=hand.getSender()[hand.getPlace()];
   if(empty()){
      if(tophand.getRank()==Card::Ace)
         return true;
      return false;
   }
   else{
      const Card& topcard=*_pile[size()-1].get();
      if(tophand.getSuit()==topcard.getSuit() && tophand.getRank()-1==topcard.getRank())
         return true;
   }
   return false;
}
void Foundation::updatereceiver(){
   // actually not needed
}
void Foundation::updatesender(){
   // actually not needed
}

 