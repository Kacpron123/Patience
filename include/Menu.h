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
   sf::RenderWindow m_window{};
   sf::Image m_app_icon{};
   Tile m_background{};
   std::vector<std::unique_ptr<Card>> to_draw;
public:
   Menu();
   ~Menu()=default;
   void game_event();
   void draw();
   int start();
};
#endif
