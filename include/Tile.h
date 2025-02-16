#ifndef TILE_H
#define TILE_H

#include "SFML/Graphics.hpp"  
#include <string>
/// @brief class definnig drawing sprite
class Tile : public sf::Drawable{
public:
   sf::Texture m_texture{};
   sf::Sprite m_sprite{};

   Tile() = default;
   Tile(const Tile &other);
   Tile(const std::string &path);
   ~Tile() override = default;
   Tile& operator=(const Tile &other); 
   void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
   void setTexture(const std::string &path);
   void setTexture(const sf::Texture &texture);
   void setPosition(float x,float y);
};
#endif
