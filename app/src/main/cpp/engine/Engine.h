#pragma once
#include "vulkan/VulkanRenderer.h"
namespace um {
class Engine {
public:
    bool initialize(ANativeWindow* window);
    void shutdown();
    VulkanRenderer& renderer() { return renderer_; }
private:
    VulkanRenderer renderer_;
};
}
