#pragma once

#include "data/list.h"
#include "engine/renderer.h"

typedef struct GameLevel {
    List *bricks;
} GameLevel;

GameLevel *GameLevel_load(const char *file, unsigned int width, unsigned int height);
void GameLevel_destroy(GameLevel *level);
void GameLevel_draw(const Renderer *renderer, const GameLevel *level);