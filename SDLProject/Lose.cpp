#include "Lose.h"

#define LOSE_WIDTH 0
#define LOSE_HEIGHT 0
#define LOSE_ENEMY_COUNT 0

unsigned int lose_data[] = {0};

void Lose::Initialize() {
    
    state.nextScene = -1;
    
    state.map = new Map(LOSE_WIDTH, LOSE_HEIGHT, lose_data, NULL, 1.0f, 4, 1);
    
    state.player = new Entity();
    state.player->isActive = false;
    
}

void Lose::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, LOSE_ENEMY_COUNT, state.map);
}

void Lose::Render(ShaderProgram *program) {
    
    state.map->Render(program);
    state.player->Render(program);
    
    Util::DrawText(program, Util::LoadTexture("pixel_font.png"), "YOU LOST", 1.4f, -0.15f, glm:: vec3(0.2, -2,0.0f));
    Util::DrawText(program, Util::LoadTexture("pixel_font.png"), "YOU HAD NO LIVES", 0.65f, -0.05f, glm:: vec3(0, -4.5,0.0f));
    Util::DrawText(program, Util::LoadTexture("pixel_font.png"), "REMAINING", 0.65f, -0.05f, glm:: vec3(1.9, -5.5,0.0f));
        
    
}

