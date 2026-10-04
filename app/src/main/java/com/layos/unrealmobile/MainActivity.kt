package com.layos.unrealmobile

import android.app.Activity
import android.os.Bundle
import android.view.Window
import android.view.WindowManager

class MainActivity : Activity() {
    private lateinit var vulkanView: VulkanView
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        requestWindowFeature(Window.FEATURE_NO_TITLE)
        window.setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN)
        vulkanView = VulkanView(this)
        setContentView(vulkanView)
    }
    override fun onDestroy() {
        vulkanView.holder.removeCallback(vulkanView)
        super.onDestroy()
    }
}