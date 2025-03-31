#include "Depot.h"
#include "Card.h"
#include "Hand.h"

Depot::Depot(sf::Vector2f position,sf::Vector2f dposition):m_position(position),m_dposition(dposition){}

void Depot::setPosition(float x,float y){
   m_position.x=x;
   m_position.y=y;
}
void Depot::setDPosition(float x,float y){
   m_dposition.x=x;
   m_dposition.y=y;
}
void Depot::draw(sf::RenderTarget &target, sf::RenderStates states) const{
   for(const auto &card : _pile)
      card->draw(target,states);
}
int Depot::clicked(const sf::Vector2i &mousePos){
   sf::Vector2f rightdowncorner=_pile.back()->getPosition()+_pile.back()->getSize();
   if(mousePos.x>=m_position.x && mousePos.x<=rightdowncorner.x  &&
      mousePos.y>=m_position.y && mousePos.y<=rightdowncorner.y){
         float absmouseposy=mousePos.y-m_position.y;
      int res=absmouseposy/m_dposition.y;
      res=(res>=_pile.size()) ? _pile.size() : res+1;
      return res-1;
   }
   else
   return -2;
}
bool Depot::correctPack(int num) const{
   if(num<0 || num>_pile.size())
      throw(std::out_of_range("Depot::correctPack: index out of range"));
   for(int i=num+1;i<_pile.size();i++){
         if(!(*_pile[i-1]<<*_pile[i])){
            return false;
         }
      }
   return true;
}
void Depot::update(){
   int i=0;
   for(auto &card : _pile){
      card->setPosition(m_position.x+m_dposition.x*i,m_position.y+m_dposition.y*i);
      i++;
   }
}
void Depot::scale(float x,float y){
   m_dposition.x*=x;
   m_dposition.y*=y;
   for(auto &card : _pile)
   card->scale(x,y);
}
void Depot::fillDepot(std::vector<std::unique_ptr<Card>> &pack){
   _pile.reserve(_pile.size()+pack.size());
   int i=size();
   for(auto &card : pack){
      _pile.push_back(std::move(card));
      _pile.back()->setPosition(m_position.x+m_dposition.x*i,m_position.y+m_dposition.y*i);
      i++;
   }
   // update();
   pack.clear();
   // std::cout<<"Depot filled"<<std::endl;
}
Card& Depot::operator[](int j){
   if(j<0 || j>=_pile.size())
      throw std::out_of_range("Depot::operator[]: index out of range");
   return *_pile[j];
}
Card& Depot::operator[](int j) const{
   if(j<0 || j>=_pile.size())
      throw std::out_of_range("Depot::operator[]: index out of range");
   return *_pile[j];
}
void Depot::createDepot(std::vector<std::unique_ptr<Card>> &pack){
   Depot::fillDepot(pack);
}   
void Depot::piletopile(Depot *sender,int num,Depot *receiver){
   if(!sender || !receiver)
      return;
   for(int i=num;i<sender->size();i++)
      (*sender)[i].deselect();
   //accepting the move
   if(!(sender->piletohand() && receiver->handtopile()))
      return;
   // moving
   std::vector<std::unique_ptr<Card>> pack(std::make_move_iterator(sender->_pile.begin()+num),std::make_move_iterator(sender->_pile.end()));
   sender->_pile.erase(sender->_pile.begin() + num, sender->_pile.end());
   receiver->fillDepot(pack);
   //updating
   sender->updatesender();
   receiver->updatereceiver();
}
