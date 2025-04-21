#include "Menu.h"

int main()
{
    try {
        Menu &app=Menu::getInstance();
        return app.start();
    }
    catch (...) {
        return 84;
    }
}