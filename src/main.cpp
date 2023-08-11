#include <iostream>

#include "Engine.h"

int main() {
    Engine engine;
    engine.createWindow(800, 600, false);
    engine.render();

    return 0;
}
