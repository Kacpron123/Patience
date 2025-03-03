#include "Tile.h"

Tile::Tile(const std::string &path){
   setTexture(path);
   setSize(m_texture.getSize().x,m_texture.getSize().y);
}
Tile::Tile(const std::string &path,sf::Vector2u given_size){
   setTexture(path);
   setSize(given_size.x,given_size.y);
}
void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const{
   target.draw(m_sprite, states);
}

void Tile::setTexture(const std::string &path){
   if(path.empty())
      return;
   if(!m_texture.loadFromFile(path))
      throw std::exception();
   m_texture.setSmooth(true);
   m_sprite.setTexture(m_texture, true);
   
}
void Tile::setTexture(const sf::Texture &texture){
   m_texture=texture;
   m_sprite.setTexture(m_texture, true);
}

void Tile::setPosition(float x,float y){
   m_sprite.setPosition(x, y);
}

void Tile::scale(float x,float y){  
   m_sprite.scale(x,y);
}

void Tile::setSize(float x,float y){
   m_sprite.setScale(x/m_sprite.getLocalBounds().width, y/m_sprite.getLocalBounds().height);
}
void Tile::setScale(float x,float y){
   m_sprite.setScale(x,y);
}
void Tile::setRect(sf::IntRect rect){
   m_sprite.setTextureRect(rect);
}
