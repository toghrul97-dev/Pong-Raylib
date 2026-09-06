#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "game.h"


int main() {

    Game game;
    game.init();
    game.startBall();

    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        game.update();
        game.draw();
    }
    
    game.clean();
    return 0;
}