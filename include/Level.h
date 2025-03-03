#ifndef LEVEL_H
#define LEVEL_H

#include <memory>
#include <string>

#include "Tableau.h"
#include "Stock.h"
class Level{
private:
    std::string(_levelpath);
    /// @brief vector of cards in game
    /// used in drawing and scaling
    std::vector<Card*> _cards;
    std::vector<std::unique_ptr<Depot>> _depots; 
public:
    Level();
    ~Level();
    static int _difficulty;
    void loadLevel(std::string &&levelpath);
    void resetLevel();
    void draw(sf::RenderTarget &target,sf::RenderStates states) const;
    void shuffle();
    void dealCards();
    void scale(float x,float y);
    void levelEvent(sf::Vector2i mousePos);
    friend class Card;
};
#endif
