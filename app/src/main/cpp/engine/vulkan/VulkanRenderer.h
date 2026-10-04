#pragma once

#include <vulkan/vulkan.h>
#include <android/native_window.h>

namespace um {

class VulkanRenderer {
public:
    bool initialize(ANativeWindow* window);
    void shutdown();
    bool isInitialized() const { return initialized_; }

private:
    bool createInstance();
    bool selectPhysicalDevice();
    bool createDevice();
    bool createSurface(ANativeWindow* window);
    bool initialized_ = false;

    VkInstance instance_ = VK_NULL_HANDLE;
    VkPhysicalDevice physicalDevice_ = VK_NULL_HANDLE;
    VkDevice device_ = VK_NULL_HANDLE;
    VkSurfaceKHR surface_ = VK_NULL_HANDLE;
};

} // namespace um
