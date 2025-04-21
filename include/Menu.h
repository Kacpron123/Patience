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

class Menu: public MenuOptions {
private:
   static Menu* instance;
   Level& level = Level::getInstance();
   /// @brief window
   sf::RenderWindow m_window{};
   /// @brief app icon
   sf::Image m_app_icon{};
   /// @brief background texture
   Tile m_background{};
   Menu();
   Menu(const Menu&) = delete; // Delete Copy Constructor
   Menu& operator=(const Menu&) = delete; // Delete Copy Assignment Operator
public:
   static Menu& getInstance();
   ~Menu() = default;
   /// @brief main game loop
   void game_event();
   /// @brief menu
   void draw();
   /// @brief main loop
   int start();
   static sf::RenderWindow& getWindow(){return getInstance().m_window;}
};
#endif

