#ifndef LEVEL_H
#define LEVEL_H

#include <memory>
#include <string>
#include "Depot.h"
#include "Hand.h"
class Level{
private:
    std::string _levelpath;
    // Hand hand;
    /// @brief vector of cards in game
    /// used in drawing and scaling
    std::vector<Card*> _cards;
    std::vector<std::shared_ptr<Depot>> _depots; 
    /// @brief which depot can be moved
    static int m_difficulty;
    /// @brief which type of card can be placed one on another
    static int m_placingtype;
public:
    Level();
    ~Level();

    void loadLevel(std::string &&levelpath);
    void resetLevel();
    void cleanLevel();
    void draw(sf::RenderTarget &target,sf::RenderStates states) const;
    void shuffle();
    void dealCards();
    void scale(float x,float y);
    void levelEvent(sf::Vector2i mousePos);
    friend class Card;
};
#endif
