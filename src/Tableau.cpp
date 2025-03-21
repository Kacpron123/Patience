#include "Tableau.h"
#include "Level.h"
#include "Hand.h"
Tableau::Tableau(sf::Vector2f position,sf::Vector2f dposition):Depot(position,dposition){
   baseTile.setTexture("resources/card_blank.png");
   baseTile.setSize(80,120);
   baseTile.setPosition(getPosition().x,getPosition().y);
}
void Tableau::draw(sf::RenderTarget &target, sf::RenderStates states) const{
   baseTile.draw(target,states);
   Depot::draw(target,states);
}
#include <iostream>
int Tableau::clicked(const sf::Vector2i &mousePos){
   if(empty()){
      sf::Vector2f rightdowncornerofbase=baseTile.getPosition()+static_cast<sf::Vector2f>(baseTile.getSize());
      if(mousePos.x>=baseTile.getPosition().x && mousePos.x<=rightdowncornerofbase.x  && mousePos.y>=baseTile.getPosition().y && mousePos.y<=rightdowncornerofbase.y)
         return -1;
      return -2;
   }
   else
   return Depot::clicked(mousePos);
}
void Tableau::scale(float x,float y){
   baseTile.scale(x,y);
   Depot::scale(x,y);
}
void Tableau::createDepot(std::vector<std::unique_ptr<Card>> &pack){   
   fillDepot(pack);
   int n=size()-1;
   for(int i=0;i<n;i++)
      _pile[i]->reverse();
}
bool Tableau::piletohand(){
   // if(empty())
   //    return false;
   return true;
   Card &topcard = (*this)[size()-1];
   std::cout<<topcard;
   std::cout<<"hm\n";
   if(!topcard.getHeadup())
      topcard.reverse();
}
bool Tableau::handtopile(){
   if(empty()){
      const Card& tophand=Hand::getInstance().getSender()[Hand::getInstance().getPlace()]; 
      if(tophand.getRank()==Card::King)
         return true;
      return false;
   }
   if((Hand::getInstance().getSender())[Hand::getInstance().getPlace()]>(*this)[size()-1])
      return true;
   return false;
}
void Tableau::updatereceiver(){
   // TODO : update receiver, add resize     
}
void Tableau::updatesender(){
   if(empty())
      return;
   Card &topcard = (*this)[size()-1];
   if(!topcard.getHeadup())
      topcard.reverse();
}