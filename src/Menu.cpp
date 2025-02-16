#include "Menu.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "MenuOptions.h"
#include "Card.h"

Menu::Menu(){
   MenuOptions::LoadTextures();

   m_window.create(sf::VideoMode(MenuOptions::window_width,MenuOptions::window_height), "Solitaire");
   m_window.setFramerateLimit(60);
   m_window.setKeyRepeatEnabled(false);

   m_app_icon.loadFromFile("resources/app_icon.png");
   m_window.setIcon(m_app_icon.getSize().x,m_app_icon.getSize().y, m_app_icon.getPixelsPtr());

   sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
   m_window.setPosition(sf::Vector2i(desktop.width / 2 - m_window.getSize().x/2,desktop.height / 2 - m_window.getSize().y/2));
   m_background.setTexture(MenuOptions::m_background);
}

int Menu::start(){
   while(m_window.isOpen()){
      game_event();
      m_window.clear(sf::Color::Black);
      this->draw();
      m_window.display();
      sf::sleep(sf::milliseconds(20));
   }
   return EXIT_SUCCESS;
}

void Menu::game_event(){
   sf::Event ev;
   Card card1(Card::Two,Card::Hearts);
   while(m_window.pollEvent(ev)){
      if (ev.type == sf::Event::Resized) {
         int x = ev.size.width;
         int y = ev.size.height;
         if (ev.size.width < 1400)
               x = 1400;
         if (ev.size.height < 900)
               y = 900;
         m_window.setSize(sf::Vector2u(x, y));
         m_background.m_sprite.setScale(static_cast<float>(x) / 1400, static_cast<float>(y) / 900);
         sf::FloatRect visibleArea(0, 0, x, y);
         m_window.setView(sf::View(visibleArea));
      }
      if (ev.type == sf::Event::Closed)
         m_window.close();
   }
   
}
#include <iostream>
void Menu::draw(){
   m_window.draw(m_background);
   Card test(Card::Nine,Card::Hearts);
   test.setPosition(100,100);
   m_window.draw(test.m_sprite);
   Card test2(Card::Rank::Jack,Card::Hearts);
   test2.setPosition(500,150);
   m_window.draw(test2.m_sprite);
}