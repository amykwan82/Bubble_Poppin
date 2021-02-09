#include "LevelD.h"

#define LEVELD_WIDTH 0
#define LEVELD_HEIGHT 0
#define LEVELD_ENEMY_COUNT 0

unsigned int levelD_data[] = {0};

void LevelD::Initialize() {
    
    state.nextScene = -1;
    
    state.map = new Map(LEVELD_WIDTH, LEVELD_HEIGHT, levelD_data, NULL, 1.0f, 4, 1);
    
    state.player = new Entity();
    state.player->isActive = false;
    
}

void LevelD::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, LEVELD_ENEMY_COUNT, state.map);
    
    if (state.hasStarted) {
        state.nextScene = 1;
    }
}

void LevelD::Render(ShaderProgram *program) {
    
    state.map->Render(program);
    state.player->Render(program);
    
    Util::DrawText(program, Util::LoadTexture("pixel_font.png"), "POP ALL BUBBLES", 0.7f, -0.07f, glm:: vec3(0.20, -0.5,0.0f));
    
    Util::DrawText(program, Util::LoadTexture("pixel_font.png"), "TO ACTIVATE", 0.7f, 0, glm:: vec3(0.9, -1.5,0.0f));
    
    Util::DrawText(program, Util::LoadTexture("pixel_font.png"), "THE PORTAL", 0.7f, -0.09, glm:: vec3(1.7, -2.5,0.0f));
    
    Util::DrawText(program, Util::LoadTexture("pixel_font.png"), "AVOID ALL MONSTERS", 0.68f, -0.15f, glm:: vec3(-0.02, -4.0,0.0f));
    
    Util::DrawText(program, Util::LoadTexture("pixel_font.png"), "GET TO THE FINAL PORTAL", 0.58f, -0.16, glm:: vec3(-0.1, -5.0,0.0f));

    
    Util::DrawText(program, Util::LoadTexture("pixel_font.png"), "PRESS ENTER TO BEGIN", 0.53f, -0.09f, glm:: vec3(0.30, -6.55,0.0f));
    
}

