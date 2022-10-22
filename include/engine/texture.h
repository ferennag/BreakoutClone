#pragma once

#include <stdbool.h>
#include <glad/glad.h>

typedef GLuint Texture;

Texture Texture_load(const char *path, const bool hasAlpha);
void Texture_destroy(GLuint *texture);