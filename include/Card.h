#ifndef CARD_H
#define CARD_H

#include "Tile.h"
#include "MenuOptions.h"
#include "SFML/Graphics.hpp"
class Card : public Tile{
public:
enum Suit { Hearts, Clubs, Diamonds, Spades };
enum Rank { Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };
protected:
   /// @brief rank of card in order: A,1,2,3,4,5,6,7,8,9,10,J,Q,K
   const Rank _rank;
   /// @brief suit of card: hearts,diamonds,clubs,spades
   const Suit _suit;
   /// @brief side of card
   bool _side;
   /// @brief rectangle for card
   sf::IntRect m_cardrect;
   sf::Texture m_frontside;

   public:
   Card(int rank,int suit,bool side=false);
   ~Card()=default;
   /// @brief reverse side of card
   void Reverse();   
   bool operator<(const Card& other) const;
   inline bool operator>(const Card &other) const{return other>*this;}
   Card::Rank GetRank() const;
   Card::Suit GetSuit() const;

};
#endif
