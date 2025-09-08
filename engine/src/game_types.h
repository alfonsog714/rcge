#pragma once

#include "core/application.h"

/**
 * Representation of the basic game state.
 */
typedef struct game
{
    // Configuration struct for the application.
    application_config app_config;

    // Function pointer to game's init function.
    b8 (*initialize)(struct game *game_inst);

    // Function pointer to the game's update function.
    b8 (*update)(struct game *game_inst, f32 delta_time);

    // Function pointer to the game's render function.
    b8 (*render)(struct game *game_inst, f32 delta_time);

    // Function pointer to the game's function that'll handle resize.
    void (*on_resize)(struct game *game_inst, u32 width, u32 height);

    // State that should be created and managed by the game.
    void *state;

} game;