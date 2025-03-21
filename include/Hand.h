#ifndef HAND_H_
#define HAND_H_

#include "Depot.h"
#include "Tile.h"
#include "Depot.h"
#include "Tile.h"

#include <iostream>
/// @brief Singleton class that contain selected Card
class Hand{
protected:
private:
   /// @brief if true then Hand is drawn as depot in mouse location
   bool m_drawOnMouse;
   /// @brief Depot from which card is selcted
   Depot* m_sender =nullptr;
   /// @brief place at which cards are selected
   int m_place;
   Hand(){};

public:
   static Hand& getInstance();
   Hand(const Hand&) = delete;
   Hand& operator=(const Hand&) = delete;
   void selectDepot(Depot *depot,int num);
   void deselectDepot();
   Depot& getSender() {return *m_sender;}
   int getPlace() {return m_place;}
   bool isSelected() const{return m_sender!=nullptr;}
   size_t size() const{return m_sender->size()-m_place;}
   void draw(sf::RenderTarget &target,sf::RenderStates states, sf::Vector2i &mousePos) const;
   void print(){
      char rank[13]={'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
      char suit[4]={'H','D','C','S'};
      for(int i=m_place;i<m_sender->size();i++)
         (*m_sender)[i].print();
      std::cout<<"------------"<<std::endl;
      }
};
#endif
