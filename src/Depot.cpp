#include "Depot.h"
#include "Card.h"

Depot::Depot(sf::Vector2f position,sf::Vector2f dposition,std::vector<std::unique_ptr<Card>> pile):_position(position),_dposition(dposition){
   _pile.reserve(pile.size());
   std::move(pile.begin(),pile.end(),std::back_inserter(_pile));
   pile.clear();
}
Depot::Depot(sf::Vector2f position,sf::Vector2f dposition):_position(position),_dposition(dposition){}

void Depot::draw(sf::RenderTarget &target, sf::RenderStates states) const{
   for(const auto &card : _pile)
      card->draw(target,states);
}
void Depot::place_pack(std::vector<std::unique_ptr<Card>> &pack){
   _pile.reserve(_pile.size()+pack.size());
   int i=0;
   for(auto &card : pack){
      card->setPosition(_position.x+_dposition.x*i,_position.y+_dposition.y*i);
      _pile.push_back(std::move(card));
      i++;
   }
   pack.clear();
}
#include <iostream>
int Depot::clicked(sf::Vector2i &mousePos) const{
   sf::Vector2f rightdowncorner=_pile.back()->getPosition()+_pile.back()->getSize();
   if(mousePos.x>=_position.x && mousePos.x<=rightdowncorner.x  &&
      mousePos.y>=_position.y && mousePos.y<=rightdowncorner.y){
      std::cout<<"click ";
      int cardclicked=0;
      
      std::cout<<cardclicked<<std::endl;
      return cardclicked;
      }
   else
      return -1;
}
void Depot::setPosition(float x,float y){
   _position.x=x;
   _position.y=y;
}
void Depot::setDPosition(float x,float y){
   _dposition.x=x;
   _dposition.y=y;
}
void Depot::scale(float x,float y){
   for(auto &card : _pile)
      card->scale(x,y);
}
// void Depot::resize(){
//    int i=0;
//    for(auto &card : _pile){
//       card->setPosition(_position.x+_dposistion.x*i,_position.y+_dposistion.y*i);
//       card->resize();
//       i++;
//    }
// }