#include "VulkanRenderer.h"
#include <algorithm>
#include <vector>
namespace um {
bool VulkanRenderer::initialize(ANativeWindow* window) {
    if (initialized_ || window == nullptr) return initialized_;
    if (!createInstance() || !createSurface(window) || !selectPhysicalDevice() || !createDevice()) {
        shutdown(); return false;
    }
    initialized_ = true; return true;
}
void VulkanRenderer::shutdown() {
    if (device_ != VK_NULL_HANDLE) { vkDeviceWaitIdle(device_); vkDestroyDevice(device_, nullptr); device_ = VK_NULL_HANDLE; }
    if (surface_ != VK_NULL_HANDLE && instance_ != VK_NULL_HANDLE) { vkDestroySurfaceKHR(instance_, surface_, nullptr); surface_ = VK_NULL_HANDLE; }
    if (instance_ != VK_NULL_HANDLE) { vkDestroyInstance(instance_, nullptr); instance_ = VK_NULL_HANDLE; }
    physicalDevice_ = VK_NULL_HANDLE; initialized_ = false; width_ = height_ = 0;
}
void VulkanRenderer::resize(uint32_t width, uint32_t height) { width_ = width; height_ = height; }
bool VulkanRenderer::createInstance() {
    VkApplicationInfo appInfo{}; appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Unreal Mobile"; appInfo.applicationVersion = VK_MAKE_VERSION(0,1,0);
    appInfo.pEngineName = "Unreal Mobile Engine"; appInfo.engineVersion = VK_MAKE_VERSION(0,1,0);
    appInfo.apiVersion = VK_API_VERSION_1_1;
    const std::vector<const char*> extensions = {VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_ANDROID_SURFACE_EXTENSION_NAME};
    VkInstanceCreateInfo info{}; info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    info.pApplicationInfo = &appInfo; info.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    info.ppEnabledExtensionNames = extensions.data();
    return vkCreateInstance(&info, nullptr, &instance_) == VK_SUCCESS;
}
bool VulkanRenderer::createSurface(ANativeWindow* window) {
    VkAndroidSurfaceCreateInfoKHR info{}; info.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR; info.window = window;
    return vkCreateAndroidSurfaceKHR(instance_, &info, nullptr, &surface_) == VK_SUCCESS;
}
bool VulkanRenderer::selectPhysicalDevice() {
    uint32_t count = 0;
    if (vkEnumeratePhysicalDevices(instance_, &count, nullptr) != VK_SUCCESS || count == 0) return false;
    count = std::min(count, 16u); std::vector<VkPhysicalDevice> devices(count);
    if (vkEnumeratePhysicalDevices(instance_, &count, devices.data()) != VK_SUCCESS) return false;
    physicalDevice_ = devices[0]; return physicalDevice_ != VK_NULL_HANDLE;
}
bool VulkanRenderer::createDevice() {
    uint32_t count = 0; vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice_, &count, nullptr);
    if (count == 0) return false;
    std::vector<VkQueueFamilyProperties> families(count);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice_, &count, families.data());
    uint32_t graphicsFamily = UINT32_MAX;
    for (uint32_t i=0;i<count;++i) if (families[i].queueCount && (families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)) { graphicsFamily=i; break; }
    if (graphicsFamily == UINT32_MAX) return false;
    const float priority=1.0f; VkDeviceQueueCreateInfo queue{}; queue.sType=VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue.queueFamilyIndex=graphicsFamily; queue.queueCount=1; queue.pQueuePriorities=&priority;
    VkDeviceCreateInfo info{}; info.sType=VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO; info.queueCreateInfoCount=1; info.pQueueCreateInfos=&queue;
    return vkCreateDevice(physicalDevice_, &info, nullptr, &device_) == VK_SUCCESS;
}
}