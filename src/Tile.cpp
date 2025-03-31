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

bool Tile::clicked(const sf::Vector2i &MousePos){
   sf::Vector2f pos=m_sprite.getPosition();
   sf::FloatRect siz=m_sprite.getGlobalBounds();
   if(MousePos.x>=pos.x && MousePos.x<=pos.x+siz.width &&
      MousePos.y>=pos.y && MousePos.y<=pos.y+siz.height)
      return true;
   return false;
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
sf::Vector2f Tile::getSize() const{
   sf::FloatRect rect(m_sprite.getGlobalBounds());
   return sf::Vector2f(rect.width,rect.height);
}
void Tile::setScale(float x,float y){
   m_sprite.setScale(x,y);
}
void Tile::setRect(sf::IntRect rect){
   m_sprite.setTextureRect(rect);
}
void Tile::select(){
   m_sprite.setColor(sf::Color(190, 190, 190, 255));  // Cyan with 75% transparency

}
void Tile::deselect(){
   m_sprite.setColor(sf::Color(255,255,255,255));  // Reset to original color (no tint) and full opacity

}