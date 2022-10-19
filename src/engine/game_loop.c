#include <stdbool.h>
#include <SDL2/SDL.h>
#include "cglm/cglm.h"
#include "engine/window.h"
#include "engine/game_loop.h"
#include "engine/shader.h"
#include "engine/texture.h"
#include "engine/time.h"
#include "data/list.h"

typedef struct GameState {
    bool running;
    mat4 projection;
    GLuint program;
    List *scene;
} GameState;

static GameState state;
static bool running = true;

void GameLoop_handleKeydown(SDL_Event *e)
{
    switch (e->key.keysym.sym)
    {
        case SDLK_q:
        case SDLK_ESCAPE:
            running = false;
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
                running = false;
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
    glm_perspective(glm_rad(45.0f), Window_aspect(), 0.1f, 100.0f, state.projection);

    state.program = Shader_create_program("shaders/vertex.glsl", "shaders/fragment.glsl");
    state.scene = List_empty(NULL);
}

void GameLoop_afterFinish()
{
    List_destroy(state.scene);
}

void GameLoop_update()
{
    glUseProgram(state.program);
    glUseProgram(0);
}

void GameLoop_run()
{
    Uint64 msPerFrame = 1000 / 60;
    Uint64 frameStart = 0;
    
    GameLoop_beforeStart();
    while(running) {
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