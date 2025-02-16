#ifndef MENU_H
#define MENU_H

#include "MenuOptions.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Tile.h"

class Menu: public MenuOptions{
private:
   sf::RenderWindow m_window{};
   sf::Image m_app_icon{};
   Tile m_background{};

public:
   Menu();
   ~Menu()=default;
   void game_event();
   void draw();
   int start();
};
#endif
