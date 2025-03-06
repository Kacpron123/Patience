#ifndef FOUNDATION_H_
#define FOUNDATION_H_

#include "Depot.h"
#include "Tile.h"
class Foundation : public Depot{
   private:
   bool autocollect=false;
   Tile foundationCard;
protected:
public:
   Foundation(sf::Vector2f position);
   void draw(sf::RenderTarget &target,sf::RenderStates states) const override;
   int clicked(sf::Vector2i &mousePos) const override;
   void scale(float x,float y) override;
};
#endif
