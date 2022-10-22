#pragma once

#include "glad/glad.h"
#include "data/vec2.h"
#include "data/vec3.h"
#include "data/mat4.h"
#include "engine/sprite.h"
#include "engine/texture.h"
#include "engine/game_object.h"

typedef struct Renderer
{
    GLuint shaderProgram;
    Mat4 projection;
    Sprite sprite;
} Renderer;

Renderer *Renderer_create();
void Renderer_destroy(Renderer *renderer);
void Renderer_draw(const Renderer *renderer, const GameObject *object);
void Renderer_drawTexture(const Renderer *renderer, const Texture texture, Vec2 pos, Vec2 size, float rotation, Vec3 color);