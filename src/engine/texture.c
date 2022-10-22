#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include "engine/texture.h"
#include "data/hashmap.h"

static HashMap *cache = NULL;

void Texture_free(void *obj) 
{
    GLuint *texture = (GLuint *)obj;
    Texture_destroy(texture);
    free(texture);
}

Texture Texture_load(const char *path, const bool hasAlpha) 
{
    if (!cache) {
        cache = HashMap_empty(Texture_free);
    }

    void *cachedTexture = HashMap_get(cache, path);

    if (cachedTexture) {
        return *((GLuint *) cachedTexture);
    }

    SDL_Surface *img = IMG_Load(path);

    if(!img) {
        printf("Unable to load texture: %s\n", path);
        return 0;
    }

    int colorMode = hasAlpha ? GL_RGBA : GL_RGB;
    GLuint *texture = (GLuint *) malloc(sizeof(GLuint));
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);
    glTexImage2D(GL_TEXTURE_2D, 0, colorMode, img->w, img->h, 0, colorMode, GL_UNSIGNED_BYTE, img->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    SDL_FreeSurface(img);

    HashMap_put(cache, path, texture);

    return *texture;
}

void Texture_destroy(GLuint *texture)
{
    glDeleteTextures(1, texture);
}

void Texture_destroyAll()
{
    if (NULL != cache) {
        HashMap_destroy(cache);
    }
}