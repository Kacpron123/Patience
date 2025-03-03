#ifndef TABLEAU_H
#define TABLEAU_H

#include "Depot.h"
#include "Tile.h"
class Tableau: public Depot{
private:
   /// @brief mean if can place any kard or only King
   bool _placeableAny;
   Tile depot;
public:
   Tableau(sf::Vector2f position,sf::Vector2f size);
   ~Tableau() = default;
   void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
#endif