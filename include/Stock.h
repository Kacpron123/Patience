#ifndef STOCK_H_
#define STOCK_H_

#include "Depot.h"
#include "Card.h"

#include <vector>
#include <memory>
class Stock: public Depot{
protected:
private:
/// card to collect
/// it is guaranteed that the card to collect is the top card in pilec
class Waste{
   private:
   sf::Vector2f _position;
   public:
} waste;
   /// @brief defining if cards are auto collecting from Tableau 
   bool autocollect();
   // int drawedCard;
public:
   Stock(sf::Vector2f position);
   void draw(sf::RenderTarget &target, sf::RenderStates) const override;
   int clicked(sf::Vector2i &mousePos) const override;
   void rotate();
};
#endif
