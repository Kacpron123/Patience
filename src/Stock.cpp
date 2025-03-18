#include "Stock.h"

Stock::Stock(sf::Vector2f position): Depot(position,{0,0}){
   // waste.baseTile.setTexture("resources/card_blank.png");
   // waste.baseTile.setSize(80,120);
   // waste.baseTile.setPosition(getPosition().x,getPosition().y);
}

void Stock::draw(sf::RenderTarget & target,sf::RenderStates states) const{
   // waste.baseTile.draw(target,states);
   Depot::draw(target,states);
}

int Stock::clicked(sf::Vector2i &mousePos) const{
   // return (waste.basteTile.)
   return -2;
}