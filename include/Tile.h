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
   /// @brief default constructor
   Tile() = default;
   Tile(const std::string &path);
   Tile(const Tile &other,sf::Vector2u size);
   Tile(const std::string &path,sf::Vector2u size);
   ~Tile() override = default;
   Tile& operator=(const Tile &other); 
   /// @brief check if tile is clicked
   bool clicked(const sf::Vector2i &MousePos);
   /// @brief draw tile
   void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
   /// @brief  set texture
   void setTexture(const std::string &path);
   /// @brief  set texture
   void setTexture(const sf::Texture &texture);
   /// @brief get position 
   inline sf::Vector2f getPosition() const{return m_sprite.getPosition();}
   /// @brief get size of tile 
   sf::Vector2f getSize() const;
   /// @brief set FloatRect
   void setRect(sf::IntRect rect);
   /// @brief set size
   void setSize(float x,float y);
   /// @brief set size
   void setPosition(float x,float y);
   void setScale(float x,float y);
   void scale(float x,float y);
   virtual void select();
   void deselect();
};
#endif
