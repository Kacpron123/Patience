#ifndef MENUOPTIONS_H
#define MENUOPTIONS_H

#include "SFML/Graphics.hpp"
#include <string>
#include <vector>
#include <functional>
class MenuOptions{
private:
struct Button{
   sf::RectangleShape m_button{};
   sf::Text m_text{};
   Button(float x, float y, float width, float height, const std::string& label);
   bool isClicked(sf::Vector2f mousePos) const;
   void updateHover(sf::Vector2f mousePos);
   std::function<void()> onClick = nullptr;
};
/**
 *  TODO: buttons
 *  new game
 *  restart game
 *  difficulty? {rather new game->select game with diccipulty}
 *  sound
 *  hint
 *  undo-move
 *  change-texture
 *     frontside
 *     backside 
 *     background
 *  exit
 * 
 */
std::vector<Button> m_buttons;
public:
   static std::string m_backside;
   static std::string m_frontside;
   static std::string m_background;
   static bool m_Pause;
   static int m_Volume;
   static sf::Font m_font;
   static void LoadTextures();
   sf::RenderTexture m_options_window{};
   MenuOptions();
   void draw(sf::RenderTarget &target) const;
   void click();
   void resize();

};
#endif
