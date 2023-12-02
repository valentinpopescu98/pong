#include <iostream>

#include "Engine.h"

int main() {
    Engine engine(800, 600, false);
    engine.enableVsync(true);

    engine.render();

    return 0;
}
