#ifndef DEPOT_H
#define DEPOT_H

#include "SFML/Graphics.hpp"
#include "Card.h"

#include <vector>
#include <memory>
#include <iostream>
class Depot{
private:
protected:
    /// @brief position of depot
    sf::Vector2f _position;
    /// @brief diffrences between Card
    sf::Vector2f _dposition;
    /// @brief pile of Cards
    std::vector<std::unique_ptr<Card>> _pile;
    virtual void update();
    /// @brief what happened after cards are moved from sender
    virtual bool piletohand() = 0;
    /// @brief what happened after cards are moved to receiver
    virtual bool handtopile() = 0;
    virtual void updatesender(){};
    virtual void updatereceiver(){};
public:
    /// @brief pack for containing pack of card, if needed it is placed in place of mouse
    static std::vector<std::unique_ptr<Card>> _pack;
    Depot():Depot({0,0},{0,0}){};
    Depot(sf::Vector2f position,sf::Vector2f dposition);
    virtual ~Depot() = default;
    //getters/setters
    void setPosition(float x,float y);
    void setDPosition(float x,float y);
    inline sf::Vector2f getDPosition() const{return _dposition;}
    inline sf::Vector2f getPosition() const{return _position;}

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void scale(float x,float y);
    /// @brief check if depot is clicked
    /// @return -2 if not, -1 if clicked at empty depot in override, and 1+ which Card
    virtual int clicked(const sf::Vector2i &mousePos);
    bool correctPack(int num) const;
    void fillDepot(std::vector<std::unique_ptr<Card>> &pack);
    virtual void createDepot(std::vector<std::unique_ptr<Card>> &pack);
    inline bool empty() const{return _pile.empty();}
    inline size_t size() const{return _pile.size();}
    // virtual void place_pack(std::vector<std::unique_ptr<Card>> &pack);
    //virtual void remove_pack(std::vector<std::unique_ptr<Card>> &pack);
    //virtual void move_pack(Depot* receiver);
    
    //to delete
    static void piletopile(Depot* sender, int num, Depot* receiver); 
    // virtual void piletopile(Depot* receiver, int num);
    /// @brief operator for accesing i-element from pile 
    Card& operator[](int);
    Card& operator[](int) const;
    /// @brief accessing for for-each loop 
    auto begin(){return _pile.begin();}
    auto begin() const{return _pile.cbegin();}
    auto end(){return _pile.end();}
    auto end() const{return _pile.cend();}
    /// @brief clear pile
    void clearDepot(){_pile.clear();}
    void deletecard(int num){
        if(num>=0&&num<_pile.size()){
            _pile.erase(_pile.begin()+num);
        }else
            throw std::out_of_range("Depot::deletecard: index out of range");
    update();
    }
};
#endif