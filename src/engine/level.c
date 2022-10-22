#include <stdio.h>
#include <stdlib.h>
#include "engine/level.h"
#include "engine/texture.h"
#include "engine/game_object.h"
#include "data/list.h"
#include "data/vec2.h"
#include "data/vec3.h"

// Temporary struct to store the contents of the file
typedef struct Bricks {
    int **brickTypes;
    int totalCount;
    int width;
    int height;
} Bricks;

void GameLevel_loadBricks(Bricks *bricks, const char *fileName)
{
    FILE *file = fopen(fileName, "r");
    if (NULL == file) {
        printf("Unable to load file: %s", fileName);
        return;
    }

    bricks->brickTypes = (int **) malloc(sizeof(int *));

    int count = 0;
    char c = EOF;
    while(EOF != (c = fgetc(file))) {
        if (c == ' ' || c == '\t' || c == '\r') {
            continue;
        }

        if (c == '\n') {
            bricks->width = count;
            bricks->height += 1;
            bricks->totalCount += count;
            count = 0;
            bricks->brickTypes = (int **) realloc(bricks->brickTypes, (bricks->height + 1) * sizeof(int *));
            continue;
        }

        int brickType = c - '0';

        if (0 == count) {
            bricks->brickTypes[bricks->height] = (int *) malloc(sizeof(int));
        } else {
            bricks->brickTypes[bricks->height] = (int *) realloc(
                bricks->brickTypes[bricks->height], (count + 1) * sizeof(int));
        }

        bricks->brickTypes[bricks->height][count] = brickType;
        count += 1;
    }

    fclose(file);
}

void GameLevel_build(
    List *dest, 
    const Bricks bricks,
    const unsigned int width, 
    const unsigned int height)
{
    float unitWidth = (float)width / bricks.width;
    float unitHeight = (float)height / bricks.height;

    for(unsigned int row = 0; row < bricks.height; ++row) {
        for(unsigned int col = 0; col < bricks.width; ++col) {
            int type = bricks.brickTypes[row][col];
            Vec2 pos = Vec2_init(unitWidth * col, unitHeight * row);
            Vec2 size = Vec2_init(unitWidth, unitHeight);

            if (1 == type) { // solid
                Texture texture = Texture_load("textures/block_solid.png", false);
                Vec3 color = Vec3_init(0.8, 0.8, 0.7);
                GameObject *object = GameObject_create(pos, size, color, texture);
                object->isSolid = true;
                List_append(dest, object);
            } else if (bricks.brickTypes[row][col] > 1) {
                Vec3 color = Vec3_ones();
                
                if (bricks.brickTypes[row][col] == 2) {
                    color = Vec3_init(0.2, 0.6, 1.0);
                } else if (bricks.brickTypes[row][col] == 3) {
                    color = Vec3_init(0.0, 0.7, 0.0);
                } else if (bricks.brickTypes[row][col] == 4) {
                    color = Vec3_init(0.8, 0.8, 0.4);
                } else if (bricks.brickTypes[row][col] == 5) {
                    color = Vec3_init(1.0, 0.5, 0.0);
                }

                Texture texture = Texture_load("textures/block.png", false);
                GameObject *object = GameObject_create(pos, size, color, texture);
                List_append(dest, object);
            }
        }
    }
}

GameLevel *GameLevel_load(const char *file, unsigned int width, unsigned int height)
{
    LCallbacks callbacks = {.lfree = GameObject_destroy};
    List *brickObjects = List_empty(&callbacks);
    Bricks bricks = {NULL, 0, 0, 0};
    GameLevel_loadBricks(&bricks, file);
    GameLevel_build(brickObjects, bricks, width, height);
    for (int i = 0; i < bricks.height; ++i) {
        free(bricks.brickTypes[i]);
    }
    free(bricks.brickTypes);
    
    GameLevel *result = (GameLevel *) malloc(sizeof(GameLevel));
    result->bricks = brickObjects;
    return result;
}

void GameLevel_destroy(GameLevel *level)
{
    if (NULL == level) {
        return;
    }

    if (NULL != level->bricks) {
        List_destroy(level->bricks);
    }

    free(level);
}

void GameLevel_draw(const Renderer *renderer, const GameLevel *level)
{
    Node *it = List_first(level->bricks);
    while (it != level->bricks->tail) {
        GameObject *object = (GameObject *) it->data;
        Renderer_draw(renderer, object);
        it = it->next;
    }
}