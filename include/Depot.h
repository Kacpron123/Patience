#ifndef DEPOT_H
#define DEPOT_H

#include "SFML/Graphics.hpp"
#include "Card.h"

#include <vector>
#include <memory>
class Depot{
private:

protected:
    /// @brief position of depot
    sf::Vector2f _position;
    /// @brief diffrences between Card
    sf::Vector2f _dposition;
    /// @brief pile of Cards
    std::vector<std::unique_ptr<Card>> _pile;
public:
    /// @brief pack for containing pack of card, if needed it is placed in place of mouse
    static std::vector<std::unique_ptr<Card>> _pack;
    Depot(sf::Vector2f position,sf::Vector2f dposition,std::vector<std::unique_ptr<Card>> pile);
    Depot(sf::Vector2f position,sf::Vector2f dposition);
    ~Depot() = default;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void setPosition(float x,float y);
    void setDPosition(float x,float y);
    inline sf::Vector2f getDPosition() const{return _dposition;}
    inline sf::Vector2f getPosition() const{return _position;}
    void scale(float x,float y);
    /// @brief check if depot is clicked
    /// @return -1 if not, 0 if clicked at empty depot, and 1+ which Card
    virtual int clicked(sf::Vector2i &mousePos) const;
    void place_pack(std::vector<std::unique_ptr<Card>> &pack);
    //void remove_pack(std::vector<std::unique_ptr<Card>> &pack);
    //void move_pack(std::vector<std::unique_ptr<Card>> &pack);
    inline Card& operator[](int i){return *_pile[i];}
    friend class Level;
};
#endif