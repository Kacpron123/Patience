#ifndef STOCK_H_
#define STOCK_H_

#include "Depot.h"
#include "Card.h"

#include <vector>
#include <memory>
class Stock: public Depot{
protected:
private:
class Waste{
   private:
   sf::Vector2f _position;
   public:
   void select();
};
   Tile baseTile;
   int drawedCard;
public:
   Stock(sf::Vector2f position);
   void draw(sf::RenderTarget &target, sf::RenderStates) const override;
   int clicked(sf::Vector2i &mousePos) const override;
   void peeking();
};
#endif
