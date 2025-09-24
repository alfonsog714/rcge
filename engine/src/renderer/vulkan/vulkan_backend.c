#include "vulkan_backend.h"
#include "vulkan_types.inl"
#include "vulkan_platform.h"
#include "core/logger.h"
#include "core/rcstring.h"
#include "containers/darray.h"

static vulkan_context context;

b8 vulkan_renderer_backend_initialize(renderer_backend *backend, const char *application_name, struct platform_state *plat_state)
{
    // TODO: custom allocator
    context.allocator = 0;

    VkApplicationInfo app_info = {VK_STRUCTURE_TYPE_APPLICATION_INFO};
    app_info.apiVersion = VK_API_VERSION_1_2;
    app_info.pApplicationName = application_name;
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName = "RC Game Engine";
    app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);

    VkInstanceCreateInfo create_info = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
    create_info.pApplicationInfo = &app_info;

    const char **required_extensions = darray_create(const char *);

    /* Generic surface extension*/
    darray_push(required_extensions, &VK_KHR_SURFACE_EXTENSION_NAME);

    /* Platform specific extensions*/
    platform_get_required_extension_names(&required_extensions);

    /* Debug utilities*/
#if defined(_DEBUG)
    darray_push(required_extensions, &VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    RCDEBUG("Required extensions:");
    u32 length = darray_length(required_extensions);
    for (u32 i = 0; i < length; ++i)
    {
        RCDEBUG(required_extensions[i]);
    }
#endif

    create_info.enabledExtensionCount = darray_length(required_extensions);
    create_info.ppEnabledExtensionNames = required_extensions;

    /* Validation layers */
    const char **required_validation_layer_names = 0;
    u32 required_validation_layer_count = 0;

/**
 * Validation layers should only be enabled for non-release builds.
 * This will get a list of the required validation layer names.
 */
#if defined(_DEBUG)
    RCINFO("Validation layers enabled. Enumerating...");

    // Getting the list of validation layers required.
    required_validation_layer_names = darray_create(const char *);
    darray_push(required_validation_layer_names, &"VK_LAYER_KHRONOS_validation");
    required_validation_layer_count = darray_length(required_validation_layer_names);

    // Obtaining the list of available validation layers.
    u32 available_layer_count = 0;
    VK_CHECK(vkEnumerateInstanceLayerProperties(&available_layer_count, 0));
    VkLayerProperties *available_layers = darray_reserve(VkLayerProperties, available_layer_count);
    VK_CHECK(vkEnumerateInstanceLayerProperties(&available_layer_count, available_layers));

    // Verifying that all required layers are available.
    for (u32 i = 0; i < required_validation_layer_count; ++i)
    {
        RCINFO("Searching for layer: %s...", required_validation_layer_names[i]);
        b8 found = FALSE;
        for (u32 j = 0; j < available_layer_count; ++j)
        {
            if (strings_equal(required_validation_layer_names[i], available_layers[j].layerName))
            {
                found = TRUE;
                RCINFO("Found.");
                break;
            }
        }

        if (!found)
        {
            RCFATAL("Required validation layer is missing: %s", required_validation_layer_names[i]);
            return FALSE;
        }
    }

    RCINFO("All required validation layers are present.");
#endif

    create_info.enabledLayerCount = required_validation_layer_count;
    create_info.ppEnabledLayerNames = required_validation_layer_names;

    VK_CHECK(vkCreateInstance(&create_info, context.allocator, &context.instance));
    RCINFO("Vulkan renderer initialized successfully.");
    return TRUE;
}

void vulkan_renderer_backend_shutdown(renderer_backend *backend)
{
}

void vulkan_renderer_backend_on_resized(renderer_backend *backend, u16 width, u16 height)
{
}

b8 vulkan_renderer_backend_begin_frame(renderer_backend *backend, f32 delta_time)
{
    return TRUE;
}

b8 vulkan_renderer_backend_end_frame(renderer_backend *backend, f32 delta_time)
{
    return TRUE;
}