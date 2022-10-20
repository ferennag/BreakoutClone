#pragma once

#include "glad/glad.h"
#include "data/vec2.h"
#include "data/vec3.h"
#include "data/vec3.h"

typedef struct Sprite {
    GLuint vao;
    GLuint vbo;
    GLuint shader;
} Sprite;

Sprite Sprite_create(GLuint shader);
void Sprite_draw(const Sprite sprite, GLuint texture, Vec2 pos, Vec2 size, float rotate, Vec3 color);