#include "Level4.h"

#define LEVEL4_WIDTH 12
#define LEVEL4_HEIGHT 8

#define LEVEL4_ENEMY_COUNT 6
#define LEVEL4_BUBBLE_COUNT 5

unsigned int level4_data[] = {
    68, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 70,
    85, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 87,
    85, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 87,
    85, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 87,
    85, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 87,
    85, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 87,
    85, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 87,
    102, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 104,
};

void Level4::Initialize() {
    
    state.nextScene = -1;
    GLuint mapTextureID = Util::LoadTexture("mapPack_tilesheet.png");
    
    state.map = new Map(LEVEL4_WIDTH, LEVEL4_HEIGHT, level4_data, mapTextureID, 1.0f, 17, 12);
    
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(5.5,-6.3,0);
    state.player->movement = glm::vec3(0);
    state.player->speed = 2.0f;
    state.player->textureID = Util::LoadTexture("frank.png");
    
    state.player->animRight = new int[4] {8, 9, 10, 11};
    state.player->animLeft = new int[4] {4, 5, 6, 7};
    state.player->animUp = new int[4] {12, 13, 14, 15};
    state.player->animDown = new int[4] {0, 1, 2, 3};
    
    state.player->animIndices = state.player->animRight;
    state.player->animFrames = 4;
    state.player->animIndex = 0;
    state.player->animTime = 0;
    state.player->animCols = 4;
    state.player->animRows = 4;
    
    state.player->height = 0.8f;
    state.player->width = 0.65f;
    
    state.enemies = new Entity[LEVEL4_ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("slime.png");
    
    state.enemies[0].entityType = ENEMY;
    state.enemies[0].textureID = enemyTextureID;
    state.enemies[0].position = glm::vec3(3.5,-0.1,0);
    state.enemies[0].aiType = PATROLER4;
    state.enemies[0].speed = 1.5;
    
    state.enemies[1].entityType = ENEMY;
    state.enemies[1].textureID = enemyTextureID;
    state.enemies[1].position = glm::vec3(10.5,-7,0);
    state.enemies[1].aiType = PATROLER2;
    state.enemies[1].speed = 3.5;
    
    state.enemies[2].entityType = ENEMY;
    state.enemies[2].textureID = enemyTextureID;
    state.enemies[2].position = glm::vec3(11.5,-6.5,0);
    state.enemies[2].aiType = PATROLER5;
    state.enemies[2].speed = 3;
    
    state.enemies[3].entityType = ENEMY;
    state.enemies[3].textureID = enemyTextureID;
    state.enemies[3].position = glm::vec3(0.5,-7.5,0);
    state.enemies[3].aiType = PATROLER2;
    state.enemies[3].speed = 3.5;
    
    state.enemies[4].entityType = ENEMY;
    state.enemies[4].textureID = enemyTextureID;
    state.enemies[4].position = glm::vec3(11.5,-1,0);
    state.enemies[4].aiType = PATROLER5;
    state.enemies[4].speed = 3;
    
    state.enemies[5].entityType = ENEMY;
    state.enemies[5].textureID = enemyTextureID;
    state.enemies[5].position = glm::vec3(-0.2,-3.5,0);
    state.enemies[5].aiType = PATROLER5;
    state.enemies[5].speed = 3;

    
 
    state.goal = new Entity();
    state.goal->entityType = GOAL;
    state.goal->textureID = Util::LoadTexture("portal.png");
    state.goal->position = glm::vec3(5.5,-0.1,0);
    
    if (state.temp != NULL) {
        for (int i =0; i< LEVEL4_BUBBLE_COUNT; i++) {
            state.bubbles[i] = state.temp[i];
        }
    }
    else {
        state.bubbles = new Entity[LEVEL4_BUBBLE_COUNT];
        GLuint BUBBLETextureID = Util::LoadTexture("bubble_5.png");
        
        state.bubbles[0].entityType = BUBBLE;
        state.bubbles[0].textureID = BUBBLETextureID;
        state.bubbles[0].position = glm::vec3(0.5,-0.3,0);
        
        state.bubbles[1].entityType = BUBBLE;
        state.bubbles[1].textureID = BUBBLETextureID;
        state.bubbles[1].position = glm::vec3(10.5,-0.3,0);
        
        state.bubbles[2].entityType = BUBBLE;
        state.bubbles[2].textureID = BUBBLETextureID;
        state.bubbles[2].position = glm::vec3(10.5,-6.5,0);
        
        state.bubbles[3].entityType = BUBBLE;
        state.bubbles[3].textureID = BUBBLETextureID;
        state.bubbles[3].position = glm::vec3(0.5,-6.5,0);
        
        state.bubbles[4].entityType = BUBBLE;
        state.bubbles[4].textureID = BUBBLETextureID;
        state.bubbles[4].position = glm::vec3(5.5,-3.5,0);
        
        
    }
    
    
}

void Level4::Update(float deltaTime) {
    
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL4_ENEMY_COUNT, state.map);
    state.goal->Update(deltaTime, state.player, state.enemies, LEVEL4_ENEMY_COUNT, state.map);
    
    for (int i =0; i< LEVEL4_ENEMY_COUNT; i++) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, LEVEL4_ENEMY_COUNT, state.map);
    }
    
    for (int i =0; i< LEVEL4_BUBBLE_COUNT; i++) {
        state.bubbles[i].Update(deltaTime, state.player, state.enemies, LEVEL4_ENEMY_COUNT, state.map);
    }
    
    for (int i =0; i< LEVEL4_BUBBLE_COUNT; i++) {
        if (state.player->CheckCollision(&state.bubbles[i])) {
            state.numOfPoints ++;
            state.bubbles[i].isActive = false;
            state.touchedBubble = true;
        }
    }
    
    for (int i =0; i< LEVEL4_ENEMY_COUNT; i++) {
        if (state.player->CheckCollision(&state.enemies[i])) {
            state.numOfLives--;
            
            state.temp = new Entity[LEVEL4_BUBBLE_COUNT];
            for (int i =0; i< LEVEL4_BUBBLE_COUNT; i++) {
                state.temp[i] = state.bubbles[i];
            }
            
            state.touchedMonster = true;
            
            if (state.numOfLives != 0) {
                state.nextScene = 4;
            }
            else {
                state.nextScene = 6;
            }
            
        }
    }
    
    if (state.player-> CheckCollision(state.goal) && state.numOfPoints == 13) {
        state.nextScene = 5;
    }
    
}

void Level4::Render(ShaderProgram *program) {
    
    state.map->Render(program);
    state.goal->Render(program);
    
    for (int i = 0; i < LEVEL4_BUBBLE_COUNT; i++ ) {
        state.bubbles[i].Render(program);
    }
    
    for (int i = 0; i < LEVEL4_ENEMY_COUNT; i++ ) {
        state.enemies[i].Render(program);
    }
    state.player->Render(program);
    
    float text_y = -0.5;
    
    if (state.player->position.y > -3.0f) {
        text_y = 0;
    }
    else {
        text_y = -0.5;
    }
    
    if (state.player->position.x > 3.5) {
        Util::DrawText(program, Util::LoadTexture("font2.png"), "Lives:" + std::to_string(state.numOfLives) , 0.5f, -0.2f, glm:: vec3(9.3, text_y,0.0f));
        
        Util::DrawText(program, Util::LoadTexture("font2.png"), "Bubbles:" + std::to_string(state.numOfPoints) , 0.5f, -0.2f, glm:: vec3(2.0, text_y,0.0f));
    }
    else if (state.player->position.x > 1.5) {
        Util::DrawText(program, Util::LoadTexture("font2.png"), "Lives:" + std::to_string(state.numOfLives) , 0.5f, -0.2f, glm:: vec3(state.player->position.x+5.8, text_y,0.0f));
        
        Util::DrawText(program, Util::LoadTexture("font2.png"), "Bubbles:" + std::to_string(state.numOfPoints) , 0.5f, -0.2f, glm:: vec3(state.player->position.x-1.5, text_y,0.0f));
    }
    else {
        Util::DrawText(program, Util::LoadTexture("font2.png"), "Lives:" + std::to_string(state.numOfLives) , 0.5f, -0.2f, glm:: vec3(7.3, text_y,0.0f));
        
        Util::DrawText(program, Util::LoadTexture("font2.png"), "Bubbles:" + std::to_string(state.numOfPoints) , 0.5f, -0.2f, glm:: vec3(0, text_y,0.0f));
    }
    
    
}
