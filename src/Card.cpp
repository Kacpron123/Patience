#include "Card.h"
#include "Level.h"
#include "MenuOptions.h"

#include <iostream>
int difficulty=1;
Card::Card(int rank, int suit,bool side): _rank(static_cast<Card::Rank>(rank)), _suit(static_cast<Card::Suit>(suit)),
      _side(side),Tile(MenuOptions::m_frontside){
   
   m_frontside.loadFromFile(MenuOptions::m_frontside);
   sf::Vector2u texturesize=m_frontside.getSize();
   
   int width=texturesize.x/13;
   int height=texturesize.y/4;
   m_cardrect=sf::IntRect( width*rank , height*suit , width , height );
   m_sprite.setTextureRect(m_cardrect);
}

Card::Rank Card::GetRank() const{return _rank;}
Card::Suit Card::GetSuit() const{return _suit;}
bool Card::operator<(const Card& other) const{
   switch(difficulty){
      case 1:
         return this->_rank<other._rank;
      break;
      case 2:
         return this->_suit%2==other._suit%2 && this->_rank<other._rank;
      break;
      case 3:
         return this->_suit%2!=other._suit%2 && this->_rank<other._rank;
      break;
      case 4:
         return this->_suit==other._suit && this->_rank<other._rank;
      break;
   }
   return 0;
}
      
