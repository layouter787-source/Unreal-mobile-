package com.layos.unrealmobile

import android.content.Context
import android.view.Surface
import android.view.SurfaceHolder
import android.view.SurfaceView

class VulkanView(context: Context) : SurfaceView(context), SurfaceHolder.Callback {
    init { holder.addCallback(this); isFocusable = true }

    override fun surfaceCreated(holder: SurfaceHolder) { nativeInit(holder.surface) }
    override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int) {
        nativeResize(width, height)
    }
    override fun surfaceDestroyed(holder: SurfaceHolder) { nativeShutdown() }
    override fun onDetachedFromWindow() {
        nativeShutdown()
        super.onDetachedFromWindow()
    }

    private external fun nativeInit(surface: Surface)
    private external fun nativeResize(width: Int, height: Int)
    private external fun nativeShutdown()

    companion object {
        init { System.loadLibrary("unreal_mobile_engine") }
    }
}
