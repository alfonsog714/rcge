#include "application.h"
#include "game_types.h"
#include "logger.h"

#include "platform/platform.h"
#include "core/rcmemory.h"
#include "core/event.h"
#include "core/input.h"
#include "core/clock.h"

#include "renderer/renderer_frontend.h"

typedef struct application_state
{
    game *game_inst;
    b8 is_running;
    b8 is_suspended;
    platform_state platform;
    i16 width;
    i16 height;
    clock clock;
    f64 last_time;
} application_state;

static b8 initialized = false;
static application_state app_state;

// Event handlers
b8 application_on_event(u16 code, void *sender, void *listener_inst, event_context context);
b8 application_on_key(u16 code, void *sender, void *listener_inst, event_context context);
b8 application_on_resized(u16 code, void *sender, void *listener_inst, event_context context);

b8 application_create(game *game_inst)
{
    if (initialized)
    {
        RCERROR("application_create called more than once.");
        return false;
    }

    app_state.game_inst = game_inst;

    // Initialize sub-systems.
    initialize_logging();
    input_initialize();

    app_state.is_running = true;
    app_state.is_suspended = false;

    if (!event_initialize())
    {
        RCERROR("Event system failed to initialize. Application cannot continue.");
        return false;
    }

    event_register(EVENT_CODE_APPLICATION_QUIT, 0, application_on_event);
    event_register(EVENT_CODE_KEY_PRESSED, 0, application_on_key);
    event_register(EVENT_CODE_KEY_RELEASED, 0, application_on_key);
    event_register(EVENT_CODE_RESIZED, 0, application_on_resized);

    if (!platform_startup(
            &app_state.platform,
            game_inst->app_config.name,
            game_inst->app_config.start_pos_x,
            game_inst->app_config.start_pos_y,
            game_inst->app_config.start_width,
            game_inst->app_config.start_height))
    {
        return false;
    }

    if (!renderer_initialize(game_inst->app_config.name, &app_state.platform))
    {
        RCFATAL("Renderer failed to initialize. Aborting application.");
        return false;
    }

    if (!app_state.game_inst->initialize(app_state.game_inst))
    {
        RCFATAL("Game failed to initialize.");
        return false;
    }

    app_state.game_inst->on_resize(app_state.game_inst, app_state.width, app_state.height);

    initialized = true;
    return true;
}

b8 application_run()
{
    clock_start(&app_state.clock);
    clock_update(&app_state.clock);
    app_state.last_time = app_state.clock.elapsed;
    f64 running_time = 0;
    u64 frame_count = 0;
    f64 target_frame_seconds = 1.0f / 60;

    RCINFO(get_mem_usage_str());

    while (app_state.is_running)
    {
        if (!platform_pump_messages(&app_state.platform))
        {
            app_state.is_running = false;
        }

        if (!app_state.is_suspended)
        {
            clock_update(&app_state.clock);
            f64 current_time = app_state.clock.elapsed;
            f64 delta = (current_time - app_state.last_time);
            f64 frame_start_time = platform_get_absolute_time();

            if (!app_state.game_inst->update(app_state.game_inst, (f32)delta))
            {
                RCFATAL("Game update failed, shutting down.");
                app_state.is_running = false;
                break;
            }

            if (!app_state.game_inst->render(app_state.game_inst, (f32)delta))
            {
                RCFATAL("Game render failed, shutting down.");
                app_state.is_running = false;
                break;
            }

            // TODO: actual create a packet with real data
            render_packet packet;
            packet.delta_time = delta;
            renderer_draw_frame(&packet);

            // Calculations for how long the frame took
            f64 frame_end_time = platform_get_absolute_time();
            f64 frame_elapsed_time = frame_end_time - frame_start_time;
            running_time += frame_elapsed_time;
            f64 remaining_seconds = target_frame_seconds - frame_elapsed_time;

            if (remaining_seconds > 0)
            {
                u64 remaining_ms = (remaining_seconds * 1000);

                b8 limit_frames = false;
                if (remaining_ms > 0 && limit_frames)
                {
                    platform_sleep(remaining_ms - 1);
                }

                frame_count++;
            }

            // input is processed at the end of the frame so that its output can be utilized next frame
            input_update(delta);

            app_state.last_time = current_time;
            // TODO: remove
            if (frame_count % 60 == 0 && running_time) // putting this bc the compiler will complain if we dont use these vars
            {
                // RCDEBUG("Frames: %u, Running time: %f", frame_count, running_time);
            }
        }
    }

    app_state.is_running = false;

    event_unregister(EVENT_CODE_APPLICATION_QUIT, 0, application_on_event);
    event_unregister(EVENT_CODE_KEY_PRESSED, 0, application_on_key);
    event_unregister(EVENT_CODE_KEY_RELEASED, 0, application_on_key);
    event_unregister(EVENT_CODE_RESIZED, 0, application_on_resized);
    event_shutdown();
    input_shutdown();

    renderer_shutdown();
    platform_shutdown(&app_state.platform);

    return true;
}

void application_get_framebuffer_size(u32 *width, u32 *height)
{
    *width = app_state.width;
    *height = app_state.height;
}

b8 application_on_event(u16 code, void *sender, void *listener_inst, event_context context)
{
    switch (code)
    {
    case EVENT_CODE_APPLICATION_QUIT:
    {
        RCINFO("EVENT_CODE_APPLICATION_QUIT received, shutting application down.\n");
        app_state.is_running = false;
        return true;
    }
    }

    return false;
}

b8 application_on_key(u16 code, void *sender, void *listener_inst, event_context context)
{
    if (code == EVENT_CODE_KEY_PRESSED)
    {
        u16 key_code = context.data.u16[0];

        if (key_code == KEY_ESCAPE)
        {
            event_context data = {};
            event_fire(EVENT_CODE_APPLICATION_QUIT, 0, data);

            return true;
        }
        else if (key_code == KEY_A)
        {
            RCDEBUG("Explicit check for the A key.");
        }
        else
        {
            RCDEBUG("'%c' key pressed in window.", key_code);
        }
    }
    else if (code == EVENT_CODE_KEY_RELEASED)
    {
        u16 key_code = context.data.u16[0];
        if (key_code == KEY_B)
        {
            RCDEBUG("Explicit check for release of B key.");
        }
        else
        {
            RCDEBUG("'%c' key released in window.", key_code);
        }
    }

    return false;
}

b8 application_on_resized(u16 code, void *sender, void *listener_inst, event_context context)
{
    if (code == EVENT_CODE_RESIZED)
    {
        u16 width = context.data.u16[0];
        u16 height = context.data.u16[1];

        if (width != app_state.width || height != app_state.height)
        {
            app_state.width = width;
            app_state.height = height;

            RCDEBUG("Window resize: %i %i", width, height);

            if (width == 0 || height == 0)
            {
                RCINFO("Window has been minimized, suspending application.");
                app_state.is_suspended = true;
                return true;
            }
            else
            {
                if (app_state.is_suspended)
                {
                    RCINFO("Window has been restored, resuming application.");
                    app_state.is_suspended = false;
                }

                app_state.game_inst->on_resize(app_state.game_inst, width, height);
                renderer_on_resized(width, height);
            }
        }
    }

    return false;
}