#ifndef TABLEAU_H
#define TABLEAU_H

#include "Depot.h"
#include "Tile.h"

#include <vector>
#include <memory>
class Tableau: public Depot{
private:
   /// @brief true if can place any kard else only King
   bool _placeableAny;
   Tile baseTile;
public:
   Tableau(sf::Vector2f position,sf::Vector2f size);
   ~Tableau() = default;
   void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
   int clicked(sf::Vector2i &mousePos) const override;
   void scale(float x,float y) override;
   void fillDepot(std::vector<std::unique_ptr<Card>> &pack) override;
};
#endif