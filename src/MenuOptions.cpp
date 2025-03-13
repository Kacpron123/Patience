#include "MenuOptions.h"
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>

#include "Card.h"
MenuOptions::Button::Button(float x, float y, float width, float height, const std::string& label) {
   m_button.setSize(sf::Vector2f(width, height));
   m_button.setPosition(x, y);
   m_button.setFillColor(sf::Color(230, 230, 255)); // Blue button   

   m_text.setFont(m_font);
   m_text.setString(label);
   m_text.setCharacterSize(16);
   m_text.setFillColor(sf::Color::Black);
   m_text.setPosition(x + width / 2 - m_text.getLocalBounds().width / 2, y + height / 2 - m_text.getLocalBounds().height / 2); // Adjust text position
}
bool MenuOptions::Button::isClicked(sf::Vector2f mousePos) const{
   return m_button.getGlobalBounds().contains(mousePos);
}
void MenuOptions::Button::updateHover(sf::Vector2f mousePos){
   if (m_button.getGlobalBounds().contains(mousePos))
      m_button.setFillColor(sf::Color(200, 200, 255));
   else
      m_button.setFillColor(sf::Color(230, 230, 255));
}


std::string MenuOptions::m_backside;
std::string MenuOptions::m_frontside;
std::string MenuOptions::m_background;
sf::Font MenuOptions::m_font;
void MenuOptions::LoadTextures(){
   // std::unordered_map<std::string,std::string> settings;
   // std::ifstream file("settings.txt");
   // if(!file)
   //    throw std::runtime_error("Failed to load");
   // std::string line;
   // while(std::getline(file, line)){
   //    if(line.empty() || line[0]=='[')
   //       continue;
   //    std::istringstream linestream(line);
   //    std::string key, value;
   //    if(std::getline(linestream,key, '=') && std::getline(linestream,value)){
   //       settings[key]=value;
   //    }
   // }   
   // m_backside=settings["backside"];
   // m_frontside=settings["frontside"];
   // m_background=settings["background"];
   m_font.loadFromFile("resources/Trebuchet-MS-Italic.ttf");
   m_backside="resources/backside/cardBack_green2.png";
   m_frontside="resources/frontside/simple.png";
   m_background="resources/background/red-dark.jpg";
   Card::loadTexture();
}

MenuOptions::MenuOptions(){
   LoadTextures();
   m_options_window.create(800,40);
   m_buttons.push_back(Button(0, 0, 150, 40, "New Game"));
   m_buttons.push_back(Button(150, 0, 150, 40, "Restart"));
   m_buttons.push_back(Button(300, 0, 150, 40, "Settings"));
   m_buttons.push_back(Button(450, 0, 150, 40, "Exit"));
   // hint?
   // undo?
}
void MenuOptions::draw(sf::RenderTarget &target) const{
   // m_options_window.clear();
   for (const auto& button : m_buttons) {
      target.draw(button.m_button);
      target.draw(button.m_text);
   }
}
