#include "Menu.h"

int main()
{
    try {
        Menu app;
        return app.start();
    }
    catch (...) {
        return 84;
    }
}