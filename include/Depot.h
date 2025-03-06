#ifndef DEPOT_H
#define DEPOT_H

#include "SFML/Graphics.hpp"
#include "Card.h"

#include <vector>
#include <memory>
class Depot{
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
    Depot(sf::Vector2f position,sf::Vector2f dposition);
    ~Depot() = default;
    //getters/setters
    void setPosition(float x,float y);
    void setDPosition(float x,float y);
    inline sf::Vector2f getDPosition() const{return _dposition;}
    inline sf::Vector2f getPosition() const{return _position;}
    inline int numberofCard() const{return _pile.size();}

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void scale(float x,float y);
    /// @brief update scale/position
    void update();
    /// @brief check if depot is clicked
    /// @return -1 if not, 0 if clicked at empty depot in override, and 1+ which Card
    virtual int clicked(sf::Vector2i &mousePos) const;
    bool correctPack(int num) const;
    virtual void fillDepot(std::vector<std::unique_ptr<Card>> &pack);
    inline bool empty() const{return _pile.empty();}
    // virtual void place_pack(std::vector<std::unique_ptr<Card>> &pack);
    //virtual void remove_pack(std::vector<std::unique_ptr<Card>> &pack);
    //virtual void move_pack(Depot* receiver);
    //void piletohand()
    //hand handtopile()
    inline Card& operator[](int i){return *_pile[i];}
    friend class Level;
    void deletecard(int num){
        if(num>=0&&num<_pile.size()){
            _pile.erase(_pile.begin()+num);
        }
    update();
    }
};
#endif