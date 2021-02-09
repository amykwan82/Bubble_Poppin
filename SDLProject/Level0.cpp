#include "Level0.h"

#define LEVEL0_WIDTH 0
#define LEVEL0_HEIGHT 0
#define LEVEL0_ENEMY_COUNT 0
#define LEVEL0_BUBBLE_COUNT 1

unsigned int level0_data[] = {0};



void Level0::Initialize() {
    
    state.nextScene = -1;
    
    state.map = new Map(LEVEL0_WIDTH, LEVEL0_HEIGHT, level0_data, NULL, 1.0f, 4, 1);
    
    state.player = new Entity();
    state.player->isActive = false;

    state.bubbles = new Entity[LEVEL0_BUBBLE_COUNT];
    GLuint BUBBLETextureID = Util::LoadTexture("bubble_5.png");
    
    state.bubbles[0].entityType = BUBBLE;
    state.bubbles[0].textureID = BUBBLETextureID;
    state.bubbles[0].position = glm::vec3(1.6,-2.3,0);
    state.bubbles[0].size = glm::vec3(1.75,1.75,1.0);
    
    
}

void Level0::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL0_ENEMY_COUNT, state.map);
    
    for (int i =0; i< LEVEL0_BUBBLE_COUNT; i++) {
        state.bubbles[i].Update(deltaTime, state.player, state.enemies, LEVEL0_ENEMY_COUNT, state.map);
    }
    
    
    if (state.hasStarted) {
        state.nextScene = 1; 
    }
    

}

void Level0::Render(ShaderProgram *program) {
    
    state.map->Render(program);
    state.player->Render(program);
    
    for (int i = 0; i < LEVEL0_BUBBLE_COUNT; i++ ) {
        state.bubbles[i].Render(program);
    }
    
   Util::DrawText(program, Util::LoadTexture("pixel_font.png"), "BUBBLE", 1.4f, -0.10f, glm:: vec3(0.3, -1.6,0.0f));

    Util::DrawText(program, Util::LoadTexture("pixel_font.png"), "P PPIN'", 1.4f, -0.15f, glm:: vec3(1.5, -4.0,0.0f));
    Util::DrawText(program, Util::LoadTexture("pixel_font.png"), "PRESS ENTER TO CONTINUE", 0.50f, -0.10f, glm:: vec3(0.1, -6.0,0.0f));
    
}

