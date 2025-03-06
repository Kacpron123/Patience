#ifndef LEVEL_H
#define LEVEL_H

#include <memory>
#include <string>
#include "Depot.h"
class Level{
private:
    class selectedPack{
    private:
        Depot* sender;
        int cardNum;
        /// @brief true if the card is to be sent to the mouse
        bool toMouse;
    public:
        void draw(sf::RenderTarget &target,sf::RenderStates states) const;
        friend void select(Depot* receiver, int cardnum);
        void deselect();
    };
    std::string _levelpath;
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
    void clean();
    void draw(sf::RenderTarget &target,sf::RenderStates states) const;
    void shuffle();
    void dealCards();
    void scale(float x,float y);
    void levelEvent(sf::Vector2i mousePos);
    // friend class Card;
};
#endif
