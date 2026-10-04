package com.layos.unrealmobile

import android.content.Context
import android.graphics.*
import android.view.MotionEvent
import android.view.View
import kotlin.math.max
import kotlin.math.min

class EditorView(context: Context) : View(context) {
    private val paint = Paint(Paint.ANTI_ALIAS_FLAG)
    private var selected = false
    private var cubeX = 0f
    private var cubeY = 0f

    init {
        paint.typeface = Typeface.create("sans", Typeface.NORMAL)
    }

    override fun onDraw(canvas: Canvas) {
        super.onDraw(canvas)

        canvas.drawColor(Color.rgb(18, 18, 20))

        val w = width.toFloat()
        val h = height.toFloat()

        // Top editor bar
        paint.color = Color.rgb(28, 28, 31)
        canvas.drawRect(0f, 0f, w, 64f, paint)

        paint.color = Color.WHITE
        paint.textSize = 22f
        canvas.drawText("Unreal Mobile", 24f, 41f, paint)

        paint.textSize = 15f
        canvas.drawText("▣  Save", 220f, 40f, paint)
        canvas.drawText("▶  Play", 315f, 40f, paint)

        // Viewport
        val viewportRight = w - 300f
        paint.color = Color.rgb(32, 32, 36)
        canvas.drawRect(0f, 64f, viewportRight, h, paint)

        // Simple ground grid
        paint.color = Color.rgb(55, 55, 60)
        paint.strokeWidth = 1f
        var x = 0f
        while (x < viewportRight) {
            canvas.drawLine(x, 64f, x, h, paint)
            x += 48f
        }
        var y = 96f
        while (y < h) {
            canvas.drawLine(0f, y, viewportRight, y, paint)
            y += 48f
        }

        // Scene object
        if (cubeX == 0f && cubeY == 0f) {
            cubeX = viewportRight / 2f
            cubeY = h / 2f
        }

        paint.color = Color.rgb(100, 150, 230)
        canvas.drawRect(cubeX - 55f, cubeY - 55f, cubeX + 55f, cubeY + 55f, paint)

        if (selected) {
            paint.style = Paint.Style.STROKE
            paint.color = Color.WHITE
            paint.strokeWidth = 3f
            canvas.drawRect(cubeX - 62f, cubeY - 62f, cubeX + 62f, cubeY + 62f, paint)
            paint.style = Paint.Style.FILL
        }

        // Outliner
        paint.color = Color.rgb(25, 25, 28)
        canvas.drawRect(viewportRight, 64f, w, h, paint)

        paint.color = Color.WHITE
        paint.textSize = 17f
        canvas.drawText("OUTLINER", viewportRight + 18f, 96f, paint)

        paint.textSize = 15f
        canvas.drawText("▾ Scene", viewportRight + 18f, 132f, paint)
        canvas.drawText("   Camera", viewportRight + 34f, 162f, paint)
        canvas.drawText("   Light", viewportRight + 34f, 190f, paint)

        paint.color = if (selected) Color.rgb(60, 90, 130) else Color.rgb(42, 42, 46)
        canvas.drawRect(viewportRight + 8f, 202f, w - 8f, 238f, paint)

        paint.color = Color.WHITE
        canvas.drawText("   Cube", viewportRight + 34f, 226f, paint)

        paint.color = Color.rgb(25, 25, 28)
        canvas.drawRect(viewportRight, 270f, w, h, paint)

        paint.color = Color.WHITE
        paint.textSize = 17f
        canvas.drawText("INSPECTOR", viewportRight + 18f, 302f, paint)

        paint.textSize = 14f
        canvas.drawText("Transform", viewportRight + 18f, 338f, paint)
        canvas.drawText("Position     X 0   Y 0   Z 0", viewportRight + 18f, 368f, paint)
        canvas.drawText("Rotation     X 0   Y 0   Z 0", viewportRight + 18f, 396f, paint)
        canvas.drawText("Scale        X 1   Y 1   Z 1", viewportRight + 18f, 424f, paint)
    }

    override fun onTouchEvent(event: MotionEvent): Boolean {
        when (event.actionMasked) {
            MotionEvent.ACTION_DOWN -> {
                val dx = event.x - cubeX
                val dy = event.y - cubeY
                selected = dx * dx + dy * dy <= 70f * 70f
                invalidate()
                return true
            }
            MotionEvent.ACTION_MOVE -> {
                if (selected && event.x < width - 300f) {
                    cubeX = min(width - 360f, max(60f, event.x))
                    cubeY = min(height - 70f, max(120f, event.y))
                    invalidate()
                }
                return true
            }
        }
        return true
    }
}
