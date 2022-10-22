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
#include "engine/keyboard.h"
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
static GameObject *player;

void GameLoop_handleInput(Uint64 dtMs)
{
    if (Keyboard_isPressed(ESC) || Keyboard_isPressed(Q)) {
        state.running = false;
        return;
    }

    if (Keyboard_isPressed(LEFT) && player->position.x >= 0.0f) {
        const Vec2 velocity = Vec2_divs(Vec2_muls(player->velocity, dtMs), 500.0f);
        player->position.x -= velocity.x;
    }

    if (Keyboard_isPressed(RIGHT) && player->position.x <= (Window_width() - player->size.x)) {
        const Vec2 velocity = Vec2_divs(Vec2_muls(player->velocity, dtMs), 500.0f);
        player->position.x += velocity.x;
    }
}

void GameLoop_handleMouseMotion(SDL_Event *e, Uint64 dtMs)
{
    // const float sensitivity = 0.1f;
    // float dx = e->motion.xrel * sensitivity;
    // float dy = e->motion.yrel * sensitivity;
}

void GameLoop_pollEvents(Uint64 dtMs)
{
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        switch (e.type)
        {
            case SDL_QUIT:
                state.running = false;
                break;

            case SDL_KEYUP:
                Keyboard_handleKeyup(&e);
                break;

            case SDL_KEYDOWN:
                Keyboard_handleKeydown(&e);
                break;

            case SDL_MOUSEMOTION:
                GameLoop_handleMouseMotion(&e, dtMs);
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

    const Vec2 playerSize = Vec2_init(100.0f, 20.0f);
    Vec2 playerPos = Vec2_init(
        Window_width() / 2.0f  - playerSize.x / 2.0f,
        Window_height() - playerSize.y - 5
    );

    player = GameObject_create(playerPos, playerSize, Vec3_ones(), Texture_load("textures/paddle.png", true));
    player->velocity = Vec2_init(500.0f, 0.0f);
}

void GameLoop_afterFinish()
{
    List_destroy(state.scene);
    GameLevel_destroy(state.level);
    Renderer_destroy(renderer);
    Texture_destroyAll();
}

void GameLoop_update(Uint64 dtMs)
{
    GameLoop_handleInput(dtMs);
    Renderer_drawTexture(renderer, state.background, Vec2_init(0, 0), Vec2_init(Window_width(), Window_height()), 0.0f, Vec3_init(1, 1, 1));
    GameLevel_draw(state.level, renderer);
    Renderer_draw(renderer, player);
}

void GameLoop_run()
{
    Uint64 msPerFrame = 1000 / 60;
    Uint64 frameStart = 0;
    Uint64 lastFrame = 0.0f;
    
    GameLoop_beforeStart();
    while(state.running) {
        frameStart = Time_getTicks();
        Uint64 dt = frameStart - lastFrame;
        lastFrame = frameStart;

        GameLoop_pollEvents(dt);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        GameLoop_update(dt);
        Window_update();

        Uint64 frameTime = Time_getTicks() - frameStart;
        dt = frameTime;
        if (frameTime < msPerFrame) {
            Time_delay(msPerFrame - frameTime);
        }
    }
    GameLoop_afterFinish();
}