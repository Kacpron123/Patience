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
int Tableau::clicked(sf::Vector2i &mousePos) const{
   if(empty()){
      sf::Vector2f rightdowncornerofbase=baseTile.getPosition()+static_cast<sf::Vector2f>(baseTile.getSize());
      if(mousePos.x>=baseTile.getPosition().x && mousePos.x<=rightdowncornerofbase.x  && mousePos.y>=baseTile.getPosition().y && mousePos.y<=rightdowncornerofbase.y)
         std::cout<<"-1\n";
         return -1;
   }
   else
   return Depot::clicked(mousePos);
}
void Tableau::scale(float x,float y){
   baseTile.scale(x,y);
   Depot::scale(x,y);
}
void Tableau::piletohand(){
   // std::vector<std::unique_ptr<Card>> pack;
   // Hand &hand = Hand::getInstance();
   // Card &topcard = (*this)[num-1];
   // if(!topcard.getHeadup())
   //    topcard.reverse();
   // if(num < size() ){
   //    pack.push_back(std::move(_pile[num]));
   //    num++;
   // }
   
   // return pack;
}
void Tableau::handtopile(){
   Card &topcard = (*this)[numberofCard()-1];
   if(!topcard.getHeadup())
      topcard.reverse();
}

void Tableau::fillDepot(std::vector<std::unique_ptr<Card>> &pack){
   Depot::fillDepot(pack);
   int n=numberofCard()-1;
   // for(int i=0;i<n;i++)
   //    _pile[i]->reverse();
}