#include <stdbool.h>
#include <SDL2/SDL.h>
#include "engine/window.h"
#include "engine/game_loop.h"
#include "engine/shader.h"
#include "engine/texture.h"
#include "engine/time.h"
#include "engine/sprite.h"
#include "data/list.h"
#include "data/mat4.h"
#include "data/vec3.h"
#include "util/math.h"

typedef struct GameState {
    bool running;
    Mat4 projection;
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

Sprite sprite;
GLuint spriteTexture;

void GameLoop_beforeStart()
{
    state.projection = Mat4_orthographic(0.0, Window_width(), Window_height(), 0.0, -1.0, 1.0);
    state.program = Shader_create_program("shaders/sprite_vertex.glsl", "shaders/sprite_fragment.glsl");
    state.scene = List_empty(NULL);
    sprite = Sprite_create(state.program);
    spriteTexture = Texture_load("textures/awesomeface.png");
}

void GameLoop_afterFinish()
{
    List_destroy(state.scene);
}

void GameLoop_update()
{
    glUseProgram(sprite.shader);
    Shader_setUniformMat4(sprite.shader, state.projection, "projection");
    Sprite_draw(sprite, spriteTexture, Vec2_init(200, 200), Vec2_init(300, 400), 45.0f, Vec3_init(0, 1, 0));
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