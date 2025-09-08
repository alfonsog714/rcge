#pragma once

#include "core/application.h"
#include "core/logger.h"
#include "core/rcmemory.h"
#include "game_types.h"

extern b8 create_game(game *out_game);

/**
 * The main entry point of the application.
 */
int main(void)
{
    initialize_memory();

    game game_inst;
    if (!create_game(&game_inst))
    {
        RCFATAL("Could not create game!");
        return -1;
    }

    // Ensure that the mandatory functions are defined and assigned.
    if (!game_inst.initialize || !game_inst.on_resize || !game_inst.render || !game_inst.update)
    {
        RCFATAL("All game function pointers must be assigned!");
        return -2;
    }

    // Initialize the game.
    if (!application_create(&game_inst))
    {
        RCINFO("Application failed to create!");
        return 1;
    }

    // Begins the game loop.
    if (!application_run())
    {
        RCINFO("Application run failed!");
        return 2;
    }

    shutdown_memory();
    return 0;
}