#pragma once

#include <stdbool.h>
#include "data/vec2.h"
#include "data/vec3.h"
#include "engine/texture.h"

typedef struct GameObject {
    Vec2 position, size, velocity;
    Vec3 color;
    float rotation;
    bool isSolid;
    bool isDestroyed;
    Texture sprite;
} GameObject;

GameObject *GameObject_create(const Vec2 position, const Vec2 size, const Vec3 color, Texture texture);
void GameObject_destroy(void *obj);