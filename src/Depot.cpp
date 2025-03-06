#include "Depot.h"
#include "Card.h"

Depot::Depot(sf::Vector2f position,sf::Vector2f dposition):_position(position),_dposition(dposition){}

void Depot::draw(sf::RenderTarget &target, sf::RenderStates states) const{
   for(const auto &card : _pile)
      card->draw(target,states);
}
int Depot::clicked(sf::Vector2i &mousePos) const{
   sf::Vector2f rightdowncorner=_pile.back()->getPosition()+_pile.back()->getSize();
   if(mousePos.x>=_position.x && mousePos.x<=rightdowncorner.x  &&
      mousePos.y>=_position.y && mousePos.y<=rightdowncorner.y){
         float absmouseposy=mousePos.y-_position.y;
      int res=absmouseposy/_dposition.y;
      res=(res>=_pile.size()) ? _pile.size() : res+1;
      return res;
   }
   else
   return -1;
}
bool Depot::correctPack(int num) const{
   for(int i=num;i<_pile.size();i++){
         if(!(*_pile[i-1]<*_pile[i])){
            return false;
         }
      }
   return true;
}
void Depot::update(){
   int i=0;
   for(auto &card : _pile){
      card->setPosition(_position.x+_dposition.x*i,_position.y+_dposition.y*i);
      i++;
   }
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
   _dposition.x*=x;
   _dposition.y*=y;
   for(auto &card : _pile)
   card->scale(x,y);
}
void Depot::fillDepot(std::vector<std::unique_ptr<Card>> &pack){
   _pile.reserve(_pile.size()+pack.size());
   for(auto &card : pack)
      _pile.push_back(std::move(card));
   update();
   pack.clear();
}
