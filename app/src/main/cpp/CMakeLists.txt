cmake_minimum_required(VERSION 3.22.1)
project(UnrealMobileEngine)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_library(unreal_mobile_engine SHARED
    engine/Engine.cpp
    engine/vulkan/VulkanRenderer.cpp
)
find_library(LOG_LIB log)
find_library(ANDROID_LIB android)
find_library(VULKAN_LIB vulkan)
target_include_directories(unreal_mobile_engine PRIVATE .)
target_link_libraries(unreal_mobile_engine ${LOG_LIB} ${ANDROID_LIB} ${VULKAN_LIB})
