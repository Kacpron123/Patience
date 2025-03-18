#include "Hand.h"

Hand& Hand::getInstance(){
   static Hand instance;
   return instance;
}
void Hand::selectDepot(Depot *depot,int num){
   m_sender=depot;
   m_place=num;
}
void Hand::deselectDepot(){
   if(m_sender==nullptr)
      return;
   int n=m_sender->size()-m_place;
   while(n--){
      (*m_sender)[m_place+n].deselect();
      }
   m_sender=nullptr;
   m_place=0;
}
void Hand::draw(sf::RenderTarget &target,sf::RenderStates states, sf::Vector2i &mousePos) const{
   if(m_sender!=nullptr){
      if(m_drawOnMouse){} //draw on mouse, moving cards
      else{
         for(int i=m_place;i<m_sender->size();i++)
            (*m_sender)[i].draw(target,states);
      }
   }
}  