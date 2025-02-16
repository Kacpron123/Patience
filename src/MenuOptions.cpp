#include "MenuOptions.h"
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>

int MenuOptions::window_width=1400;
int MenuOptions::window_height=900;
std::string MenuOptions::m_backside;
std::string MenuOptions::m_frontside;
std::string MenuOptions::m_background;
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

   m_backside="resources/backside/card_black.png";
   m_frontside="resources/frontside/cards.png";
   m_background="resources/background/red-dark.jpg";
}