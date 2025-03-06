#include "Stock.h"

Stock::Stock(sf::Vector2f position): Depot(position,{0,0}){
   baseTile.setTexture("resources/card_blank.png");
   baseTile.setSize(80,120);
   baseTile.setPosition(getPosition().x,getPosition().y);
   drawedCard=0;
}

void Stock::draw(sf::RenderTarget & target,sf::RenderStates states) const{
   baseTile.draw(target,states);
   Depot::draw(target,states);
}
int Stock::clicked(sf::Vector2i &mousePos) const{
   return 0;
}