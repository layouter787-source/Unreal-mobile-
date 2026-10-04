#include <jni.h>
#include <android/native_window_jni.h>
#include <android/log.h>
#include "engine/Engine.h"

namespace {
um::Engine* gEngine = nullptr;
ANativeWindow* gWindow = nullptr;

void logError(const char* message) {
    __android_log_print(ANDROID_LOG_ERROR, "UnrealMobile", "%s", message);
}
}

extern "C" JNIEXPORT void JNICALL
Java_com_layos_unrealmobile_VulkanView_nativeInit(JNIEnv* env, jobject, jobject surface) {
    if (gEngine != nullptr) return;

    gWindow = ANativeWindow_fromSurface(env, surface);
    if (gWindow == nullptr) {
        logError("Failed to acquire ANativeWindow from Surface");
        return;
    }

    gEngine = new um::Engine();
    if (!gEngine->initialize(gWindow)) {
        logError("Vulkan engine initialization failed");
        delete gEngine;
        gEngine = nullptr;
        ANativeWindow_release(gWindow);
        gWindow = nullptr;
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_layos_unrealmobile_VulkanView_nativeResize(JNIEnv*, jobject, jint width, jint height) {
    if (gEngine == nullptr || !gEngine->renderer().isInitialized()) return;
    gEngine->renderer().resize(static_cast<uint32_t>(width), static_cast<uint32_t>(height));
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
