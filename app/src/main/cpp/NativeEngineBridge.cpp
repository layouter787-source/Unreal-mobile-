#include <jni.h>
#include <android/native_window_jni.h>
#include <android/log.h>
#include "engine/Engine.h"

namespace {
um::Engine* gEngine = nullptr;
ANativeWindow* gWindow = nullptr;
}

extern "C" JNIEXPORT void JNICALL
Java_com_layos_unrealmobile_VulkanView_nativeInit(JNIEnv* env, jobject, jobject surface) {
    if (gEngine != nullptr) return;
    gWindow = ANativeWindow_fromSurface(env, surface);
    if (gWindow == nullptr) {
        __android_log_print(ANDROID_LOG_ERROR, "UnrealMobile", "ANativeWindow acquisition failed");
        return;
    }
    gEngine = new um::Engine();
    if (!gEngine->initialize(gWindow)) {
        __android_log_print(ANDROID_LOG_ERROR, "UnrealMobile", "Vulkan initialization failed");
        delete gEngine;
        gEngine = nullptr;
        ANativeWindow_release(gWindow);
        gWindow = nullptr;
        return;
    }
    gEngine->renderer().renderFrame();
}

extern "C" JNIEXPORT void JNICALL
Java_com_layos_unrealmobile_VulkanView_nativeResize(JNIEnv*, jobject, jint width, jint height) {
    if (gEngine == nullptr || !gEngine->renderer().isInitialized()) return;
    gEngine->renderer().resize(static_cast<uint32_t>(width), static_cast<uint32_t>(height));
    gEngine->renderer().renderFrame();
}

extern "C" JNIEXPORT void JNICALL
Java_com_layos_unrealmobile_VulkanView_nativeRender(JNIEnv*, jobject) {
    if (gEngine != nullptr && gEngine->renderer().isInitialized()) {
        gEngine->renderer().renderFrame();
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_layos_unrealmobile_VulkanView_nativeShutdown(JNIEnv*, jobject) {
    if (gEngine != nullptr) {
        gEngine->shutdown();
        delete gEngine;
        gEngine = nullptr;
    }
    if (gWindow != nullptr) {
        ANativeWindow_release(gWindow);
        gWindow = nullptr;
    }
}
