#include <SDL2/SDL.h>
#include "engine/keyboard.h"
#include "data/hashmap.h"

typedef enum KeyboardState {
    RELEASED,
    PRESSED
} KeyboardState;

static KeyboardState keyboardState[128] = { RELEASED };

Keycode Keyboard_translate(const SDL_Keycode sdlKeycode) 
{
    switch (sdlKeycode)
    {
        case SDLK_LEFT:
            return LEFT;
        case SDLK_RIGHT:
            return RIGHT;
        case SDLK_UP:
            return UP;
        case SDLK_DOWN:
            return DOWN;
        case SDLK_a:
            return A;
        case SDLK_d:
            return D;
        case SDLK_w:
            return W;
        case SDLK_s:
            return S;
        case SDLK_SPACE:
            return SPACE;
        case SDLK_q:
            return Q;
        case SDLK_ESCAPE:
            return ESC;
        default:
            return UNKNOWN;
    }
}

void Keyboard_handleKeydown(const SDL_Event *e)
{
    SDL_Keycode pressed = e->key.keysym.sym;
    Keycode keycode = Keyboard_translate(pressed);
    keyboardState[keycode] = PRESSED;
}

void Keyboard_handleKeyup(const SDL_Event *e)
{
    SDL_Keycode released = e->key.keysym.sym;
    Keycode keycode = Keyboard_translate(released);
    keyboardState[keycode] = RELEASED;
}

bool Keyboard_isPressed(const Keycode keycode)
{
    return keyboardState[keycode] == PRESSED;
}