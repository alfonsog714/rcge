#pragma once

#include "defines.h"

typedef struct event_context
{
    union
    {
        i64 i64[2];
        u64 u64[2];
        f64 f64[2];

        i32 i32[4];
        u32 u32[4];
        f32 f32[4];

        i16 i16[8];
        u16 u16[8];

        i8 i8[16];
        u8 u8[16];

        char c[16];
    } data;
} event_context;

// Should return true if handled.
typedef b8 (*PFN_on_event)(u16 code, void *sender, void *listener_inst, event_context data);

b8 event_initialize();
void event_shutdown();

/**
 * Registers a listener for when events are sent with the provided code.
 * @param code The event code to listen for.
 * @param listener A pointer to a listener instance. Can be 0 / NULL.
 * @param on_event The callback function pointer to be invoked when the event code is fired.
 * @returns true if the vent is successfully registered; otherwise it returns false.
 */
RCAPI b8 event_register(u16 code, void *listener, PFN_on_event on_event);

/**
 * Unregister from listening to events with provided code.
 * @param code The event code to stop listening for.
 * @param listener Pointer to a listener instance. Can be NULL / 0.
 * @param on_event Callback pointer to be unregistered.
 * @returns true if event is successfully unregistered. false otherwise.
 */
RCAPI b8 event_unregister(u16 code, void *listener, PFN_on_event on_event);

/**
 * Fires an event to listeners of the provided code.
 * @param code The event code to fire
 * @param sender A pointer to the sender. Can be NULL.
 * @param data The event data.
 * @returns true if handled, false otherwise.
 */
RCAPI b8 event_fire(u16 code, void *sender, event_context context);

// System internal event codes. Application should use codes beyond 255
typedef enum system_event_code
{
    /* Shuts down the application on the next frame.*/
    EVENT_CODE_APPLICATION_QUIT = 0x01,

    /**
     * Context usage:
     * u16 key_code = data.data.u16[0]
     */
    EVENT_CODE_KEY_PRESSED = 0x02,

    /**
     * Context usage:
     * u16 key_code = data.data.u16[0]
     */
    EVENT_CODE_KEY_RELEASED = 0x03,

    /**
     * Context usage:
     * u16 button = data.data.u16[0]
     */
    EVENT_CODE_BUTTON_PRESSED = 0x04,

    /**
     * Context usage:
     * u16 button = data.data.u16[0]
     */
    EVENT_CODE_BUTTON_RELEASED = 0x05,

    /**
     * Context usage:
     * u16 x = data.data.u16[0]
     * u16 y = data.data.u16[1]
     */

    EVENT_CODE_MOUSE_MOVED = 0x06,

    /**
     * Context usage:
     * u8 z_delta = data.data.u8[0]
     */
    EVENT_CODE_MOUSE_WHEEL = 0x07,

    /**
     * Context usage:
     * u16 width = data.data.u16[0]
     * u16 height = data.data.u16[1]
     */
    EVENT_CODE_RESIZED = 0x08,

    MAX_EVENT_CODE = 0xFF
} system_event_code;