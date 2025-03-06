#ifndef CARD_H
#define CARD_H

#include "Tile.h"
#include "SFML/Graphics.hpp"
class Card : public Tile{
public:
enum Suit { Hearts, Clubs, Diamonds, Spades };
enum Rank { Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };
private:
   /// @brief rectangle for card
   sf::IntRect m_cardrect;
   static sf::Texture m_frontside;
   static sf::Texture m_backside;
protected:
   /// @brief rank of card in order: A,1,2,3,4,5,6,7,8,9,10,J,Q,K
   const Rank _rank;
   /// @brief suit of card: hearts,diamonds,clubs,spades
   const Suit _suit;
   /// @brief side of card false mean face-down
   bool _headup;
public:
   Card(int rank,int suit,bool headup=true);
   ~Card()=default;
   /// @brief reverse side of card
   void reverse();
   /// @brief operator for checking if i can grap pile depends of level::difficulty
   bool operator<(const Card& other) const;
   /// @brief operator for checking if i can place one on another
   // the same as operator<() difficulty=1
   bool operator>(const Card &other) const;
   void updateTexture(bool resetRect=true);
   static void loadTexture();
   Rank getRank() const;
   Suit getSuit() const;
};
#endif
