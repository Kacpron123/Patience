#include "Menu.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "MenuOptions.h"
#include "Card.h"
#include "Level.h"
//testing
#include <iostream>

#define original_width 800
#define original_height 600
Menu::Menu(){
   MenuOptions::LoadTextures();

   m_window.create(sf::VideoMode(original_width,original_height), "Solitaire");

   m_window.setFramerateLimit(60);
   m_window.setKeyRepeatEnabled(false);
   m_window.setVerticalSyncEnabled(false);

   m_app_icon.loadFromFile("resources/app_icon.png");
   m_window.setIcon(m_app_icon.getSize().x,m_app_icon.getSize().y, m_app_icon.getPixelsPtr());

   sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
   m_window.setPosition(sf::Vector2i(desktop.width / 2 - m_window.getSize().x/2,desktop.height / 2 - m_window.getSize().y/2));
   m_background.setTexture(MenuOptions::m_background);
   m_background.setSize(original_width,original_height);
}

int Menu::start(){
   level.loadLevel("level/Klondike");
   MenuOptions options;
   while(m_window.isOpen()){
      game_event();
      m_window.clear(sf::Color::Black);
      m_window.draw(m_background);
      level.draw(m_window, sf::RenderStates::Default);
      // this->draw();
      MenuOptions::draw(m_window);
      m_window.display();
      sf::sleep(sf::milliseconds(20));
   }
   return EXIT_SUCCESS;
}
void Menu::game_event(){
   sf::Event ev;
   while(m_window.pollEvent(ev)){
      if (ev.type == sf::Event::Resized) {
         int x = ev.size.width;
         int y = ev.size.height;
         //if (ev.size.width < 1400)
         //      x = 1400;
         //if (ev.size.height < 900)
         //      y = 900;
         m_window.setSize(sf::Vector2u(x, y));
         sf::FloatRect visibleArea(0, 0, 800, 600);
         //m_background.setSize({static_cast<unsigned int>(x),static_cast<unsigned int>(y)});
         m_window.setView(sf::View(visibleArea));
      }
      if (ev.type == sf::Event::Closed)
         m_window.close();
      if(ev.type == sf::Event::MouseButtonPressed){
         if(ev.mouseButton.button == sf::Mouse::Left){
            sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
            sf::Vector2i mousePos2 = static_cast<sf::Vector2i>(m_window.mapPixelToCoords(mousePos));
            level.levelEvent(mousePos2);
            
         }
      }
   }
   
}
void Menu::draw(){
   // TODO: draw menu, selecting game
}