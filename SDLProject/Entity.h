#pragma once
#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "Map.h"

enum EntityType {PLAYER, ENEMY, GOAL, BUBBLE};

enum AIType {PATROLER, PATROLER2, PATROLER3, PATROLER4, PATROLER5, PATROLER6, PATROLER7, PATROLER8};

class Entity {
public:
    
    EntityType entityType;
    AIType aiType;
    
    glm::vec3 position;
    glm::vec3 movement;
    glm::vec3 acceleration;
    glm::vec3 velocity;
    glm::vec3 size;
    
    float width = 1;
    float height = 1;
    float speed;
    
    GLuint textureID;
    
    glm::mat4 modelMatrix;
    
    int *animRight = NULL;
    int *animLeft = NULL;
    int *animUp = NULL;
    int *animDown = NULL;
    
    int *animIndices = NULL;
    int animFrames = 0;
    int animIndex = 0;
    float animTime = 0;
    int animCols = 0;
    int animRows = 0;
    
    bool isActive = true;
    
    bool hasDied = false;
    bool gameOver = false;
    
    Entity();
    
    bool CheckCollision(Entity *other);
    
    void Update(float deltaTime, Entity *player, Entity *objects, int objectCount, Map *map);
    void Render(ShaderProgram *program);
    void DrawSpriteFromTextureAtlas(ShaderProgram *program, GLuint textureID, int index);
    
    void AI(Entity *player);
    void AIPatroler();
    void AIPatroler2();
    void AIPatroler3();
    void AIPatroler4();
    void AIPatroler5();
    void AIPatroler6();
    void AIPatroler7();
    void AIPatroler8();

};
