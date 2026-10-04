#include "VulkanRenderer.h"

namespace um {
bool VulkanRenderer::initialize(ANativeWindow* window) {
    if (!window || !createInstance() || !createSurface(window) ||
        !selectPhysicalDevice() || !createDevice()) {
        shutdown();
        return false;
    }
    initialized_ = true;
    return true;
}

void VulkanRenderer::shutdown() {
    if (device_ != VK_NULL_HANDLE) { vkDeviceWaitIdle(device_); vkDestroyDevice(device_, nullptr); device_ = VK_NULL_HANDLE; }
    if (surface_ != VK_NULL_HANDLE) { vkDestroySurfaceKHR(instance_, surface_, nullptr); surface_ = VK_NULL_HANDLE; }
    if (instance_ != VK_NULL_HANDLE) { vkDestroyInstance(instance_, nullptr); instance_ = VK_NULL_HANDLE; }
    physicalDevice_ = VK_NULL_HANDLE;
    initialized_ = false;
}

bool VulkanRenderer::createInstance() {
    VkApplicationInfo app{VK_STRUCTURE_TYPE_APPLICATION_INFO};
    app.pApplicationName = "Unreal Mobile";
    app.applicationVersion = VK_MAKE_VERSION(0,1,0);
    app.pEngineName = "Unreal Mobile Engine";
    app.engineVersion = VK_MAKE_VERSION(0,1,0);
    app.apiVersion = VK_API_VERSION_1_1;

    const char* extensions[] = { VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_ANDROID_SURFACE_EXTENSION_NAME };
    VkInstanceCreateInfo info{VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
    info.pApplicationInfo = &app;
    info.enabledExtensionCount = 2;
    info.ppEnabledExtensionNames = extensions;
    return vkCreateInstance(&info, nullptr, &instance_) == VK_SUCCESS;
}

bool VulkanRenderer::createSurface(ANativeWindow* window) {
    VkAndroidSurfaceCreateInfoKHR info{VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR};
    info.window = window;
    return vkCreateAndroidSurfaceKHR(instance_, &info, nullptr, &surface_) == VK_SUCCESS;
}

bool VulkanRenderer::selectPhysicalDevice() {
    uint32_t count = 0;
    if (vkEnumeratePhysicalDevices(instance_, &count, nullptr) != VK_SUCCESS || count == 0) return false;
    VkPhysicalDevice devices[16];
    count = count > 16 ? 16 : count;
    if (vkEnumeratePhysicalDevices(instance_, &count, devices) != VK_SUCCESS) return false;
    physicalDevice_ = devices[0];
    return true;
}

bool VulkanRenderer::createDevice() {
    uint32_t count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice_, &count, nullptr);
    if (!count) return false;
    VkQueueFamilyProperties queues[32];
    count = count > 32 ? 32 : count;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice_, &count, queues);

    uint32_t family = UINT32_MAX;
    for (uint32_t i=0; i<count; ++i) if (queues[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) { family=i; break; }
    if (family == UINT32_MAX) return false;

    float priority = 1.0f;
    VkDeviceQueueCreateInfo q{VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO};
    q.queueFamilyIndex=family; q.queueCount=1; q.pQueuePriorities=&priority;
    VkDeviceCreateInfo d{VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO};
    d.queueCreateInfoCount=1; d.pQueueCreateInfos=&q;
    return vkCreateDevice(physicalDevice_, &d, nullptr, &device_) == VK_SUCCESS;
}
}
