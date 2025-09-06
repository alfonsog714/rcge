#include <core/logger.h>
#include <core/asserts.h>

// TODO: Test
#include <platform/platform.h>

int main(void) {
    RCFATAL("A test message: %f", 3.14f);
    RCERROR("A test message: %f", 3.14f);
    RCWARN("A test message: %f", 3.14f);
    RCINFO("A test message: %f", 3.14f);
    RCDEBUG("A test message: %f", 3.14f);
    RCTRACE("A test message: %f", 3.14f);

    platform_state state;
    if (platform_startup(&state, "RCGE Testbed", 100, 100, 1280, 720)) {
        while (TRUE) {
            platform_pump_messages(&state);
        }
    }

    platform_shutdown(&state);
    return 0;
}