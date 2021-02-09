#include "Win.h"

#define WIN_WIDTH 0
#define WIN_HEIGHT 0
#define WIN_ENEMY_COUNT 0

unsigned int win_data[] = {0};

void Win::Initialize() {
    
    state.nextScene = -1;
    
    state.map = new Map(WIN_WIDTH, WIN_HEIGHT, win_data, NULL, 1.0f, 4, 1);
    
    state.player = new Entity();
    state.player->isActive = false;
    
}

void Win::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, WIN_ENEMY_COUNT, state.map);
}

void Win::Render(ShaderProgram *program) {
    
    state.map->Render(program);
    state.player->Render(program);
    
    Util::DrawText(program, Util::LoadTexture("pixel_font.png"), "CONGRATULATIONS.", 0.82f, -0.20f, glm:: vec3(0, -2,0.0f));
    Util::DrawText(program, Util::LoadTexture("pixel_font.png"), "YOU JUST WON.", 0.7f, -0.10f, glm:: vec3(1, -4.5,0.0f));
    
}

