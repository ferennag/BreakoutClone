#pragma once

#include <glad/glad.h>
#include "data/mat4.h"

GLuint Shader_create_program(const char *vertex_shader, const char *fragment_shader);
void Shader_use(const GLuint shader);
void Shader_setUniformMat4(const GLuint program, const Mat4 matrix, const char *name);
void Shader_setUniformVec3(const GLuint program, const Vec3 vec, const char *name);