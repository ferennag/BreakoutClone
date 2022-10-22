#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>

typedef enum Keycode {
    UNKNOWN,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    A,
    D,
    W,
    S,
    Q,
    ESC
} Keycode;


void Keyboard_handleKeydown(const SDL_Event *e);
void Keyboard_handleKeyup(const SDL_Event *e);
bool Keyboard_isPressed(const Keycode keycode);