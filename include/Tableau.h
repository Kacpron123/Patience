#ifndef TABLEAU_H
#define TABLEAU_H

#include "Depot.h"
#include "Tile.h"

#include <vector>
#include <memory>
class Tableau: public Depot{
private:
   /// @brief true if can place any kard else only King
   bool m_placeableAny;
   Tile m_baseTile;
public:
   Tableau(sf::Vector2f position,sf::Vector2f size);
   ~Tableau() override = default;
   void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
   int clicked(const sf::Vector2i &mousePos) override;
   void scale(float x,float y) override;
   bool piletohand() override;
   bool handtopile() override;
   void createDepot(std::vector<std::unique_ptr<Card>> &pack) override;
   void updatereceiver() override;
   void updatesender() override;
};
#endif