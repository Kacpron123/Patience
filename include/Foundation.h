#ifndef FOUNDATION_H_
#define FOUNDATION_H_

#include "Depot.h"
#include "Tile.h"
class Foundation : public Depot{
   private:
   /// @brief determine if card are collected automatically
   //like in Spider Solitaire
   bool m_autocollect=false;
   /// @brief back tile to foundation
   Tile m_foundationCard;
protected:
public:
   Foundation(sf::Vector2f position);
   void draw(sf::RenderTarget &target,sf::RenderStates states) const override;
   int clicked(const sf::Vector2i &mousePos) override;
   void scale(float x,float y) override;
   bool piletohand() override;
   bool handtopile() override;
   void updatereceiver() override;
   void updatesender() override;
};
#endif
