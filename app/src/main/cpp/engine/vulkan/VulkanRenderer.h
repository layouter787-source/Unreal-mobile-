#pragma once

#include <vulkan/vulkan.h>
#include <android/native_window.h>
#include <cstdint>
#include <vector>

namespace um {

class VulkanRenderer {
public:
    bool initialize(ANativeWindow* window);
    void shutdown();
    void resize(uint32_t width, uint32_t height);
    void renderFrame();
    bool isInitialized() const { return initialized_; }

private:
    bool createInstance();
    bool selectPhysicalDevice();
    bool createDevice();
    bool createSurface(ANativeWindow* window);
    bool createSwapchain();
    bool createRenderPass();
    bool createFrameResources();
    bool recreateSwapchain();
    void destroyFrameResources();
    void destroySwapchain();
    bool findQueueFamilies(uint32_t& graphicsFamily, uint32_t& presentFamily) const;

    bool initialized_ = false;
    uint32_t width_ = 0;
    uint32_t height_ = 0;
    bool swapchainDirty_ = false;
    uint32_t graphicsQueueFamily_ = UINT32_MAX;
    uint32_t presentQueueFamily_ = UINT32_MAX;

    VkInstance instance_ = VK_NULL_HANDLE;
    VkPhysicalDevice physicalDevice_ = VK_NULL_HANDLE;
    VkDevice device_ = VK_NULL_HANDLE;
    VkSurfaceKHR surface_ = VK_NULL_HANDLE;
    VkQueue graphicsQueue_ = VK_NULL_HANDLE;
    VkQueue presentQueue_ = VK_NULL_HANDLE;

    VkSwapchainKHR swapchain_ = VK_NULL_HANDLE;
    VkFormat swapchainFormat_ = VK_FORMAT_UNDEFINED;
    VkExtent2D swapchainExtent_{};
    std::vector<VkImage> swapchainImages_;
    std::vector<VkImageView> swapchainImageViews_;
    std::vector<VkFramebuffer> framebuffers_;

    VkRenderPass renderPass_ = VK_NULL_HANDLE;
    VkCommandPool commandPool_ = VK_NULL_HANDLE;
    std::vector<VkCommandBuffer> commandBuffers_;

    VkSemaphore imageAvailableSemaphore_ = VK_NULL_HANDLE;
    VkSemaphore renderFinishedSemaphore_ = VK_NULL_HANDLE;
    VkFence inFlightFence_ = VK_NULL_HANDLE;
};

} // namespace um
