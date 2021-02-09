#include "Entity.h"

Entity::Entity()
{
    position = glm::vec3(0);
    movement = glm::vec3(0);
    size = glm::vec3(1,1,1);
    acceleration = glm::vec3(0);
    velocity = glm::vec3(0);
    speed = 0;
    modelMatrix = glm::mat4(1.0f);
}

bool Entity:: CheckCollision(Entity *other) {
    
    if (other == this) return false;
    
    if (isActive == false || other->isActive == false ) return false;
    
    float xdist = fabs(position.x - other->position.x) - ((width + other->width) / 2.0f);
    float ydist = fabs(position.y - other->position.y) - ((height + other->height) / 2.0f);
    
    if (xdist < 0 && ydist < 0) return true;
    
    return false;
}

void Entity::AIPatroler() {
    
    if (position.x <= 4.0) {
        movement = glm::vec3(0.8,0,0);
    }
    else if (position.x > 9.5) {
        movement = glm::vec3(-0.8,0,0);
    }
    
}

void Entity::AIPatroler2() {
    
    if (position.y <= -6.5 ) {
        movement = glm::vec3(0,0.8,0);
    }
    else if (position.y > 0.0) {
        movement = glm::vec3(0,-0.8,0);
    }
    
}

void Entity::AIPatroler3() {
    
    if (position.x <= 7.0) {
        movement = glm::vec3(0.8,0,0);
    }
    else if (position.x > 9.0) {
        movement = glm::vec3(-0.8,0,0);
    }
    
}

void Entity::AIPatroler4() {
    
    if (position.x <= 4.0) {
        movement = glm::vec3(0.8,0,0);
    }
    else if (position.x > 7.0) {
        movement = glm::vec3(-0.8,0,0);
    }
    
}

void Entity::AIPatroler5() {
    
    if (position.x <= 0) {
        movement = glm::vec3(0.8,0,0);
    }
    else if (position.x > 11) {
        movement = glm::vec3(-0.8,0,0);
    }
    
}

void Entity::AIPatroler6() {
    
    if (position.x <= 5.5) {
        movement = glm::vec3(0.8,0,0);
    }
    else if (position.x > 11) {
        movement = glm::vec3(-0.8,0,0);
    }
    
}

void Entity::AIPatroler7() {
    
    if (position.x <= 0) {
        movement = glm::vec3(0.8,0,0);
    }
    else if (position.x > 5.5) {
        movement = glm::vec3(-0.8,0,0);
    }
    
}

void Entity::AIPatroler8() {
    
    if (position.y <= -3) {
        movement = glm::vec3(0,0.8,0);
    }
    else if (position.y > 0) {
        movement = glm::vec3(0,-0.8,0);
    }
    
}


void Entity::AI(Entity *player) {
    switch(aiType) {
        case PATROLER:
            AIPatroler();
            break;
            
        case PATROLER2:
            AIPatroler2();
            break;
        
        case PATROLER3:
            AIPatroler3();
            break;
            
        case PATROLER4:
            AIPatroler4();
            break;
    
        case PATROLER5:
            AIPatroler5();
            break;
            
        case PATROLER6:
            AIPatroler6();
            break;
            
        case PATROLER7:
            AIPatroler7();
            break;
            
        case PATROLER8:
            AIPatroler8();
            break;
    }
}

void Entity::Update(float deltaTime, Entity *player, Entity *objects, int objectCount, Map *map)
{
    if (isActive == false) return;
        
    if (entityType == ENEMY) {
        AI(player);
    }
        
    if (animIndices != NULL) {
        if (glm::length(movement) != 0) {
            animTime += deltaTime;
            if (animTime >= 0.25f) {
                animTime = 0.0f;
                animIndex++;
                
                if (animIndex >= animFrames) {
                    animIndex = 0;
                }
            }
                
        } else {
            animIndex = 0;
        }
    }
        
    velocity.x = movement.x * speed;
    velocity.y = movement.y * speed;
    velocity += acceleration * deltaTime;
        
    position.y += velocity.y * deltaTime;
    position.x += velocity.x * deltaTime;

    modelMatrix = glm:: mat4(1.0f);
    modelMatrix = glm::scale(modelMatrix,size);
    modelMatrix = glm::translate(modelMatrix,position);
    
    
}

void Entity::DrawSpriteFromTextureAtlas(ShaderProgram *program, GLuint textureID, int index)
{
    float u = (float)(index % animCols) / (float)animCols;
    float v = (float)(index / animCols) / (float)animRows;
    
    float width = 1.0f / (float)animCols;
    float height = 1.0f / (float)animRows;
    
    float texCoords[] = { u, v + height, u + width, v + height, u + width, v,
        u, v + height, u + width, v, u, v};
    
    float vertices[]  = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->positionAttribute);
    
    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program->texCoordAttribute);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);
}

void Entity::Render(ShaderProgram *program) {
    
    if (isActive == false) return;
    
    program->SetModelMatrix(modelMatrix);
    
    if (animIndices != NULL) {
        DrawSpriteFromTextureAtlas(program, textureID, animIndices[animIndex]);
        return;
    }
    
    float vertices[]  = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
    
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->positionAttribute);
    
    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program->texCoordAttribute);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);
}
