#include "Foundation.h"

Foundation::Foundation(sf::Vector2f position): Depot(position,{0,0}){
   foundationCard.setTexture("resources/card_foundation.png");
   foundationCard.setSize(80,120);
   foundationCard.setPosition(getPosition().x,getPosition().y);
}
void Foundation::draw(sf::RenderTarget &target,sf::RenderStates states) const{
   foundationCard.draw(target,states);
   int n=numberofCard();
   if(n>=2)
   _pile.back()->draw(target,states);
   if(n>=1)
   const_cast<Foundation*>(this)[n-1].draw(target,states);
}
#include <iostream>
int Foundation::clicked(sf::Vector2i &mousePos) const{
   sf::Vector2f rightdowncornerofbase=foundationCard.getPosition()+static_cast<sf::Vector2f>(foundationCard.getSize());
   if(mousePos.x>=foundationCard.getPosition().x && mousePos.x<=rightdowncornerofbase.x  && mousePos.y>=foundationCard.getPosition().y && mousePos.y<=rightdowncornerofbase.y)
      std::cout<<"foundation\n";
   return -2;
}
void Foundation::scale(float x,float y){
   foundationCard.scale(x,y);
   Depot::scale(x,y);
}

 