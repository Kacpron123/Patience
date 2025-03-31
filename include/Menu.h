#ifndef MENU_H
#define MENU_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "MenuOptions.h"
#include "Tile.h"
#include "Card.h"
#include "Level.h"

#include <vector>
#include <memory>


class Menu: public MenuOptions{
private:
   Level level;
   /// @brief window
   sf::RenderWindow m_window{};
   /// @brief app icon
   sf::Image m_app_icon{};
   /// @brief background texture
   Tile m_background{};
public:
   Menu();
   ~Menu()=default;
   /// @brief main game loop
   void game_event();
   /// @brief menu
   void draw();
   /// @brief main loop
   int start();
};
#endif
