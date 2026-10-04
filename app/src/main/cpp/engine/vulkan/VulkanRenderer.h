#pragma once
#include <vulkan/vulkan.h>
#include <android/native_window.h>
#include <cstdint>
namespace um {
class VulkanRenderer {
public:
    bool initialize(ANativeWindow* window);
    void shutdown();
    void resize(uint32_t width, uint32_t height);
    bool isInitialized() const { return initialized_; }
private:
    bool createInstance();
    bool selectPhysicalDevice();
    bool createDevice();
    bool createSurface(ANativeWindow* window);
    bool initialized_ = false;
    uint32_t width_ = 0, height_ = 0;
    VkInstance instance_ = VK_NULL_HANDLE;
    VkPhysicalDevice physicalDevice_ = VK_NULL_HANDLE;
    VkDevice device_ = VK_NULL_HANDLE;
    VkSurfaceKHR surface_ = VK_NULL_HANDLE;
};
}