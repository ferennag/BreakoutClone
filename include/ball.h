#pragma once

#include <stdbool.h>
#include "data/vec2.h"
#include "engine/texture.h"
#include "engine/game_object.h"

typedef struct Ball {
    GameObject *object;
    bool stuck;
    float radius;

} Ball;

Ball *Ball_create(Vec2 position, float radius, Vec2 velocity);
void Ball_destroy(void *obj);
void Ball_move(Ball *ball, Time64 dt, unsigned int maxX, unsigned int maxY);
void Ball_reset(Ball *ball, const GameObject *player, Vec2 velocity);
void Ball_resetPosition(Ball *ball, const GameObject *player);
bool Ball_checkCollision(const Ball *ball, const GameObject *object);