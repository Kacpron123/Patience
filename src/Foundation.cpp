#include "Foundation.h"
#include "Hand.h"

Foundation::Foundation(sf::Vector2f position): Depot(position,{0,0}){
   foundationCard.setTexture("resources/card_foundation.png");
   foundationCard.setSize(80,120);
   foundationCard.setPosition(getPosition().x,getPosition().y);
}
void Foundation::draw(sf::RenderTarget &target,sf::RenderStates states) const{
   foundationCard.draw(target,states);
   if(!empty())
      _pile.back()->draw(target,states);
}
#include <iostream>
int Foundation::clicked(const sf::Vector2i &mousePos){
   sf::Vector2f rightdowncornerofbase=foundationCard.getPosition()+static_cast<sf::Vector2f>(foundationCard.getSize());
   if(mousePos.x>=foundationCard.getPosition().x && mousePos.x<=rightdowncornerofbase.x  && mousePos.y>=foundationCard.getPosition().y && mousePos.y<=rightdowncornerofbase.y){
      std::cout<<"foundation\n";
      if(empty())
         return -1;
      return size()-1;
   }
   return -2;
}
void Foundation::scale(float x,float y){
   foundationCard.scale(x,y);
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
   // TODO receiver
}
void Foundation::updatesender(){
   // TODO sender
}

 