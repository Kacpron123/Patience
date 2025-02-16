#ifndef MENUOPTIONS_H
#define MENUOPTIONS_H

#include "SFML/Graphics.hpp"
#include <string>
class MenuOptions{
public:
   static int window_width;
   static int window_height;
   static std::string m_backside;
   static std::string m_frontside;
   static std::string m_background;
   static bool _Pause;
   static int _Volume;
   
   static void LoadTextures();

};
#endif
