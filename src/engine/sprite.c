#include "glad/glad.h"
#include "engine/sprite.h"
#include "data/vec2.h"
#include "data/vec3.h"
#include "data/mat4.h"
#include "util/math.h"
#include "engine/shader.h"

Sprite Sprite_create(GLuint shader)
{
    Sprite sprite;
    sprite.shader = shader;
    float vertices[] = { 
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 
    
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &sprite.vao);
    glGenBuffers(1, &sprite.vbo);
    
    glBindBuffer(GL_ARRAY_BUFFER, sprite.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(sprite.vao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);  
    glBindVertexArray(0);
    
    return sprite;
}

void Sprite_draw(const Sprite sprite, GLuint texture, Vec2 pos, Vec2 size, float rotate, Vec3 color)
{
    Mat4 model = Mat4_identity();
    model = Mat4_mul(model, Mat4_translate(Vec3_init(pos.x, pos.y, 0)));
    model = Mat4_mul(model, Mat4_translate(Vec3_init(0.5 * size.x, 0.5 * size.y, 0)));
    model = Mat4_mul(model, Mat4_rotateZ(deg_to_rad(rotate)));
    model = Mat4_mul(model, Mat4_translate(Vec3_init(-0.5 * size.x, -0.5 * size.y, 0)));
    model = Mat4_mul(model, Mat4_scale(Vec3_init(size.x, size.y, 1)));

    glUseProgram(sprite.shader);
    Shader_setUniformMat4(sprite.shader, model, "model");
    Shader_setUniformVec3(sprite.shader, color, "spriteColor");

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(sprite.vao);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glBindVertexArray(0);
    glUseProgram(0);
}