#include <iostream>

#include "engine/Engine.h"

int main() {
    Engine* engine = new Engine(800, 600, false, true);

    engine->render();

    delete engine;
    return 0;
}
