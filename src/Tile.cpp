#include "Tile.h"

Tile::Tile(const std::string &path){
   setTexture(path);
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
}

void Tile::setPosition(float x,float y){
   m_sprite.setPosition(x, y);
}