#ifndef STOCK_H_
#define STOCK_H_

#include "Depot.h"
#include "Card.h"

#include <vector>
#include <memory>
/// class for stock
/// it is guaranteed that the card to collect is the top card in pile
class Stock: public Depot{
protected:
private:
   int m_bigrotate;
   Tile m_baseTile;
   sf::Vector2f m_wasteposition;
   /// @brief defining if cards are auto collecting from Tableau 
   bool m_autocollect();
   // int drawedCard;
   void rotate();
public:
   Stock(sf::Vector2f position);
   void draw(sf::RenderTarget &target, sf::RenderStates) const override;
   int clicked(const sf::Vector2i &mousePos) override;
   // int clicked(const sf::Vector2i &mousePos);
   void createDepot(std::vector<std::unique_ptr<Card>> &pack) override;
   bool piletohand() override;
   bool handtopile() override;
   // void update() override{Depot::update();std::cout<<"update stock"<<std::endl;};
   void updatesender() override;
   void updatereceiver() override;

};
#endif