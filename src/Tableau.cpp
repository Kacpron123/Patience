#include "Tableau.h"
#include "Level.h"
#include "Hand.h"

Tableau::Tableau(sf::Vector2f position,sf::Vector2f dposition):Depot(position,dposition){
   m_baseTile.setTexture("resources/card_blank.png");
   m_baseTile.setSize(Card::defaultsize.x,Card::defaultsize.y);
   m_baseTile.setPosition(getPosition().x,getPosition().y);
}
void Tableau::draw(sf::RenderTarget &target, sf::RenderStates states) const{
   m_baseTile.draw(target,states);
   Depot::draw(target,states);
}
int Tableau::clicked(const sf::Vector2i &mousePos){
   if(empty()){
      sf::Vector2f rightdowncornerofbase=m_baseTile.getPosition()+static_cast<sf::Vector2f>(m_baseTile.getSize());
      if(mousePos.x>=m_baseTile.getPosition().x && mousePos.x<=rightdowncornerofbase.x  && mousePos.y>=m_baseTile.getPosition().y && mousePos.y<=rightdowncornerofbase.y)
         return -1;
      return -2;
   }
   else
   return Depot::clicked(mousePos);
}
void Tableau::scale(float x,float y){
   m_baseTile.scale(x,y);
   Depot::scale(x,y);
}
void Tableau::createDepot(std::vector<std::unique_ptr<Card>> &pack){   
   fillDepot(pack);
   int n=size()-1;
   for(int i=0;i<n;i++)
      _pile[i]->reverse();
}
bool Tableau::piletohand(){
   return true;
}
bool Tableau::handtopile(){
   if(empty()){
      if(Level::getFlags().tableauplaceany)
         return true;
      const Card& tophand=Hand::getInstance().getSender()[Hand::getInstance().getPlace()];
      return tophand.getRank()==Card::King;
   }
   if((Hand::getInstance().getSender())[Hand::getInstance().getPlace()]>(*this)[size()-1])
      return true;
   return false;
}
void Tableau::updatereceiver(){
   if(Level::getFlags().s_autocollect){
      int s=size();
      if(s>=13 && _pile[s-13]->getHeadup() && correctPack(s-13)){
         std::shared_ptr<Depot> foundation=nullptr;
         for(auto &f:Level::getInstance().m_foundation){
            if(f && f->empty()){
               foundation=f;
               break;
            }
         }
         Hand &hand=Hand::getInstance();
         hand.selectDepot(this,s-13);
         Depot::piletopile(this,s-13,foundation.get(),true);
      }   
   }
   // TODO : update receiver, add resize     
}
void Tableau::updatesender(){
   if(empty())
      return;
   Card &topcard = (*this)[size()-1];
   if(!topcard.getHeadup())
      topcard.reverse();
}