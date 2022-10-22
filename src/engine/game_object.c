#include <stdbool.h>
#include <stdlib.h>
#include "data/vec2.h"
#include "data/vec3.h"
#include "engine/game_object.h"
#include "engine/texture.h"

GameObject *GameObject_create(const Vec2 position, const Vec2 size, const Vec3 color, Texture texture)
{
    GameObject *object = (GameObject *) malloc(sizeof(GameObject));
    object->position = position;
    object->color = color;
    object->size = size;
    object->sprite = texture;
    object->isSolid = false;
    object->isDestroyed = false;
    object->velocity = Vec2_init(0, 0);
    object->rotation = 0;
    return object;
}

void GameObject_destroy(void *obj)
{
    if (NULL == obj) {
        return;
    }

    free((GameObject *) obj);
}