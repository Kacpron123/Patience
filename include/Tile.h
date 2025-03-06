#ifndef TILE_H
#define TILE_H

#include "SFML/Graphics.hpp"  
#include <string>
/// @brief class definnig drawing sprite
class Tile : public sf::Drawable{
private:
   sf::Texture m_texture{};
   sf::Sprite m_sprite{};
public:
   Tile() = default;
   Tile(const std::string &path);
   Tile(const Tile &other,sf::Vector2u size);
   Tile(const std::string &path,sf::Vector2u size);
   ~Tile() override = default;
   Tile& operator=(const Tile &other); 
   //bool isClicked()
   void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
   void setTexture(const std::string &path);
   void setTexture(const sf::Texture &texture);
   inline sf::Vector2f getPosition() const{return m_sprite.getPosition();}
   inline sf::Vector2f getSize() {
      sf::FloatRect rect(m_sprite.getGlobalBounds());
      return sf::Vector2f(rect.width,rect.height);}
   void setRect(sf::IntRect rect);
   void setSize(float x,float y);
   sf::Vector2u getSize() const;
   void setPosition(float x,float y);
   void setScale(float x,float y);
   void scale(float x,float y);
};
#endif
