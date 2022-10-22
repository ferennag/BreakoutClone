#include <stdlib.h>
#include "glad/glad.h"
#include "engine/shader.h"
#include "engine/renderer.h"
#include "engine/texture.h"
#include "engine/game_object.h"
#include "engine/window.h"
#include "data/vec2.h"
#include "data/vec3.h"
#include "data/mat4.h"

Renderer *Renderer_create()
{
    Renderer *renderer = (Renderer *) malloc(sizeof(Renderer));
    renderer->shaderProgram = Shader_create_program("shaders/sprite_vertex.glsl", "shaders/sprite_fragment.glsl");
    renderer->projection = Mat4_orthographic(0.0, Window_width(), Window_height(), 0.0, -1.0, 1.0);
    renderer->sprite = Sprite_create(renderer->shaderProgram);
    return renderer;

}

void Renderer_destroy(Renderer *renderer)
{
    if (NULL == renderer) {
        return;
    }

    free(renderer);
}

void Renderer_draw(const Renderer *renderer, const GameObject *object)
{
    glUseProgram(renderer->shaderProgram);
    Shader_setUniformMat4(renderer->shaderProgram, renderer->projection, "projection");
    Sprite_draw(
        renderer->sprite, 
        object->sprite, 
        object->position, 
        object->size, 
        object->rotation, 
        object->color
    );
    glUseProgram(0);
}

void Renderer_drawTexture(const Renderer *renderer, const Texture texture, Vec2 pos, Vec2 size, float rotation, Vec3 color)
{
    glUseProgram(renderer->shaderProgram);
    Shader_setUniformMat4(renderer->shaderProgram, renderer->projection, "projection");
    Sprite_draw(
        renderer->sprite, 
        texture, 
        pos, 
        size, 
        rotation, 
        color
    );
    glUseProgram(0);
}