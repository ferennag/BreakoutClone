#include <stdbool.h>
#include <SDL2/SDL.h>
#include "engine/window.h"
#include "engine/game_loop.h"
#include "engine/shader.h"
#include "engine/texture.h"
#include "engine/time.h"
#include "engine/sprite.h"
#include "engine/game_object.h"
#include "engine/level.h"
#include "engine/renderer.h"
#include "data/list.h"
#include "data/mat4.h"
#include "data/vec3.h"
#include "util/math.h"

typedef struct GameState {
    bool running;
    List *scene;
    GameLevel *level;
    Texture background;
} GameState;

static GameState state;
static Renderer *renderer;

void GameLoop_handleKeydown(SDL_Event *e)
{
    switch (e->key.keysym.sym)
    {
        case SDLK_q:
        case SDLK_ESCAPE:
            state.running = false;
            break;

        default:
            break;
    }
}

void GameLoop_handleMouseMotion(SDL_Event *e)
{
    // const float sensitivity = 0.1f;
    // float dx = e->motion.xrel * sensitivity;
    // float dy = e->motion.yrel * sensitivity;
}

void GameLoop_pollEvents()
{
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        switch (e.type)
        {
            case SDL_QUIT:
                state.running = false;
                break;

            case SDL_KEYDOWN:
                GameLoop_handleKeydown(&e);
                break;

            case SDL_MOUSEMOTION:
                GameLoop_handleMouseMotion(&e);
                break;
            
            default:
                break;
        }
    }
}

void GameLoop_beforeStart()
{
    state.running = true;
    state.scene = List_empty(NULL);
    state.level = GameLevel_load("levels/level1.txt", Window_width(), Window_height() / 2);
    state.background = Texture_load("textures/background.jpg", false);
    renderer = Renderer_create();
}

void GameLoop_afterFinish()
{
    List_destroy(state.scene);
    GameLevel_destroy(state.level);
    Renderer_destroy(renderer);
}

void GameLoop_update()
{
    GameLevel_draw(renderer, state.level);
    Renderer_drawTexture(renderer, state.background, Vec2_init(0, 0), Vec2_init(Window_width(), Window_height()), 0.0f, Vec3_init(1, 1, 1));
}

void GameLoop_run()
{
    Uint64 msPerFrame = 1000 / 60;
    Uint64 frameStart = 0;
    
    GameLoop_beforeStart();
    while(state.running) {
        frameStart = Time_getTicks();

        GameLoop_pollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        GameLoop_update();
        Window_update();

        Uint64 frameTime = Time_getTicks() - frameStart;
        if (frameTime < msPerFrame) {
            Time_delay(msPerFrame - frameTime);
        }
    }
    GameLoop_afterFinish();
}