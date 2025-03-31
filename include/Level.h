#ifndef LEVEL_H
#define LEVEL_H

#include <memory>
#include <string>
#include "Depot.h"
class Level{
private:
    std::string m_levelpath;
    // Hand hand;
    /// @brief vector of cards in game
    /// used in drawing and scaling
    std::vector<Card*> m_cards;
    std::vector<std::shared_ptr<Depot>> m_depots; 
    /// @brief which depot can be moved
    static int m_difficulty;
    /// @brief which type of card can be placed one on another
    static int m_placingtype;
public:
    Level();
    ~Level();
    /// @brief load level
    /// @param levelpath name of level file 
    void loadLevel(std::string &&levelpath);
    /// @brief reset level
    void resetLevel();
    /// @brief clean level
    void cleanLevel();
    /// @brief draw level
    void draw(sf::RenderTarget &target,sf::RenderStates states) const;
    /// @brief shuffle cards
    void shuffle();
    /// @brief deal cards
    void dealCards();
    /// @brief scale level
    void scale(float x,float y);
    /// @brief handle level events
    void levelEvent(sf::Vector2i mousePos);
    friend class Card;
};
#endif
