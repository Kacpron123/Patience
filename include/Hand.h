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
   /// @brief select card from selected depot
   void deselectDepot();
   /// @brief get pointer to selected depot 
   Depot& getSender() {return *m_sender;}
   /// @brief get place at which cards are selected 
   int getPlace() {return m_place;}
   /// @brief check if hand is selected 
   bool isSelected() const{return m_sender!=nullptr;}
   /// @brief get size of hand 
   size_t size() const{return m_sender->size()-m_place;}
   /// @brief draw hand
   void draw(sf::RenderTarget &target,sf::RenderStates states, sf::Vector2i &mousePos) const;
};
#endif
