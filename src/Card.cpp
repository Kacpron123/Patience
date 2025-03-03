#include "Card.h"
#include "Level.h"
#include "MenuOptions.h"

sf::Texture Card::m_frontside;
sf::Texture Card::m_backside;
Card::Card(int rank, int suit,bool headup): _rank(static_cast<Card::Rank>(rank)), _suit(static_cast<Card::Suit>(suit)),_headup(headup),Tile("",{135,189}){
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

Card::Rank Card::getRank() const{return _rank;}
Card::Suit Card::getSuit() const{return _suit;}

bool Card::operator<(const Card& other) const{
   switch(Level::_difficulty){
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
bool Card::operator>(const Card &other) const{
   return this->_rank>other._rank;
}
void Card::Reverse(){
   _headup^=1;
   setTexture((_headup) ? m_frontside : m_backside);
   updateTexture();
   if(_headup)
      setRect(m_cardrect);  
   setSize(135,185);
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
   
}
void Card::loadTexture(){
   m_frontside.loadFromFile(MenuOptions::m_frontside);
   m_backside.loadFromFile(MenuOptions::m_backside);
}