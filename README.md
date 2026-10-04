# Unreal Mobile

A mobile-first game engine and editor designed to create games directly on Android.

## Unreal Mobile 0.1

Current foundation:

- Native Android project
- Landscape editor shell
- 3D viewport placeholder
- Scene Outliner
- Inspector
- Select and drag scene object
- Initial project structure

## Architecture

```
Android App
  └── Editor
      ├── Viewport
      ├── Outliner
      ├── Inspector
      └── Project System

Future Engine
  ├── Renderer (Vulkan)
  ├── Scene System
  ├── Asset System
  ├── Physics
  ├── Animation
  ├── Blueprint Mobile
  ├── Profiler
  └── Android Build Pipeline
```

## Roadmap

1. Real project save/load
2. Real 3D renderer
3. Camera/navigation controls
4. Scene objects and transforms
5. GLTF/GLB asset import
6. Materials and lighting
7. Blueprint Mobile
8. Physics
9. Animation and rigging
10. Android game packaging
