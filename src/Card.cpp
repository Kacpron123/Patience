#include "Card.h"
#include "Level.h"
#include "MenuOptions.h"

sf::Texture Card::m_frontside;
sf::Texture Card::m_backside;
Card::Card(int rank, int suit,bool headup): _rank(static_cast<Card::Rank>(rank)), _suit(static_cast<Card::Suit>(suit)),_headup(headup),Tile("",{135,189}){
   if(rank<0||rank>12||suit<0||suit>3)
      throw std::invalid_argument("Card must have rank between 0 and 12 and suit between 0 and 3");
   //laodTexture();
   //if(headup){
   //   m_sprite.setTexture(m_frontside);
   //   sf::Vector2u texturesize=m_frontside.getSize();
   //   int width=texturesize.x/13;
   //   int height=texturesize.y/4;
   //   m_cardrect=sf::IntRect( width*rank , height*suit , width , height );
   //   m_sprite.setTextureRect(m_cardrect);
   //   _size=m_frontside.getSize();
   //}
   //float scaleX = _card_size.x / m_sprite.getLocalBounds().width;
   //float scaleY = _card_size.y / m_sprite.getLocalBounds().height;
   //m_sprite.setScale(scaleX,scaleY);
   updateTexture();
   if(_headup)
      setRect(m_cardrect);
   setSize(135,185);
}
bool Card::operator<<(const Card& other) const{
   if(_rank-other._rank!=1)
      return false;
   switch(Level::m_difficulty){
      case 1:
         return true;
         break;
         case 2:
         return _suit%2==other._suit%2;
         break;
         case 3:
         return _suit%2!=other._suit%2;
         break;
         case 4:
         return _suit==other._suit;
         break;
      }
      return false;
   }
bool Card::operator<(const Card &other) const{
   if(_rank-other._rank!=1)
      return false;
   switch(Level::m_placingtype){
      case 1:
         return true;
         break;
      case 2:
         return _suit%2==other._suit%2;
         break;
      case 3:
         return _suit%2!=other._suit%2;
         break;
      case 4:
         return _suit==other._suit;
         break;
      }
   return false;
}
void Card::reverse(){
   sf::Vector2f currentsize=getSize();
   _headup^=1;
   setTexture((_headup) ? m_frontside : m_backside);
   updateTexture();
   setSize(currentsize.x,currentsize.y);
}

void Card::updateTexture(bool resetRect){
   loadTexture();
   m_frontside.setSmooth(resetRect);
   m_backside.setSmooth(resetRect);
   sf::Vector2u texturesize=m_frontside.getSize();
   int width=texturesize.x/13;
   int height=texturesize.y/4;
   m_cardrect=sf::IntRect( width*_rank , height*_suit , width , height );
   setTexture((_headup) ? m_frontside : m_backside);
   if(_headup)
      setRect(m_cardrect);
}
void Card::loadTexture(){
   m_frontside.loadFromFile(MenuOptions::m_frontside);
   m_backside.loadFromFile(MenuOptions::m_backside);
}
   

#include <string>
std::ostream& operator<<(std::ostream& os, const Card& card){
   std::string suit[4]={"Hearts","Clubs","Diamonds","Spades"};
   char rank[13]={'A','2','3','4','5','6','7','8','9','T','J','Q','K'};

   os<<suit[card._suit]<<" "<<rank[card._rank];
   return os;
}
void Card::print() const{
   std::cout<<*this<<std::endl;
}