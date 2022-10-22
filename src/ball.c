#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "data/vec2.h"
#include "engine/game_object.h"
#include "engine/texture.h"
#include "engine/time.h"
#include "util/math.h"
#include "ball.h"

Ball *Ball_create(Vec2 position, float radius, Vec2 velocity)
{
    Ball *ball = (Ball *) malloc(sizeof(Ball));
    Texture texture = Texture_load("textures/ball.png", true);
    ball->radius = radius;
    ball->stuck = false;
    ball->object = GameObject_create(position, Vec2_init(radius * 2, radius * 2), Vec3_ones(), texture);
    ball->object->velocity = velocity;
    return ball;
}

void Ball_destroy(void *obj)
{
    if(NULL == obj) {
        return;
    }

    Ball *ball = (Ball *) obj;

    GameObject_destroy(ball->object);
    free(ball);
}

void Ball_move(Ball *ball, Time64 dt, unsigned int maxX, unsigned int maxY)
{
    if (ball->stuck) {
        return;
    }

    ball->object->position = Vec2_add(ball->object->position, Vec2_muls(ball->object->velocity, dt / 1000.0f));

    if (ball->object->position.x <= 0.0f) {
        ball->object->velocity.x *= -1;
        ball->object->position.x = 0.0f;
    } else if (ball->object->position.x + ball->object->size.x >= maxX) {
        ball->object->velocity.x *= -1;
        ball->object->position.x = maxX - ball->object->size.x;
    }

    if (ball->object->position.y <= 0.0f) {
        ball->object->velocity.y *= -1;
        ball->object->position.y = 0.0f;
    }
}

void Ball_reset(Ball *ball, const GameObject *player, Vec2 velocity)
{
    Ball_resetPosition(ball, player);
    ball->object->velocity = velocity;
    ball->stuck = true;
}

void Ball_resetPosition(Ball *ball, const GameObject *player)
{
    ball->object->position = Vec2_add(player->position, 
        Vec2_init(player->size.x / 2.0f - ball->radius, -ball->radius * 2.0f));
}

bool Ball_checkCollision(const Ball *ball, const GameObject *object)
{
    Vec2 center = Vec2_adds(ball->object->position, ball->radius);
    Vec2 aabb_half_extents = Vec2_init(object->size.x / 2.0f, object->size.y / 2.0f);
    Vec2 aabb_center = Vec2_add(object->position, aabb_half_extents);

    Vec2 difference = Vec2_sub(center, aabb_center);
    Vec2 clamped = Vec2_clamp(difference, Vec2_negate(aabb_half_extents), aabb_half_extents);
    Vec2 closest = Vec2_add(aabb_center, clamped);
    difference = Vec2_sub(closest, center);
    return Vec2_magnitude(difference) < ball->radius;
}