# Unreal Mobile — Agent Instructions

## This file is mandatory

You are continuing an existing Android-first game engine/editor project. Do not treat this repository as a blank prototype and do not rely on conversational memory.

### Before touching code
1. Read `README.md` completely.
2. Inspect the actual files you intend to modify and their current Git SHA.
3. Check the latest commits on `main` when possible.
4. Identify the current stage and the exact immediate task from the README.

### After every meaningful change
Update `README.md` in the same commit/change. The README must record:
- UTC date;
- implementation completed;
- why the change was made;
- files changed;
- commit SHA when known;
- commands/tests actually executed and their real result;
- unresolved problems;
- the exact next task for the next agent.

Do not leave the repository in a state where another agent has to guess what happened.

### Verification rules
- Never say "build passed", "CI passed", "works", or "tested" without actual evidence.
- Distinguish clearly between:
  - code written;
  - locally compiled;
  - GitHub Actions compiled;
  - runtime-tested on Android hardware/emulator.
- If verification is unavailable, mark it as pending.

### Collaboration rules
- Claude, Codex, ChatGPT, or another coding agent may work on this same repository.
- Never overwrite another agent's work blindly.
- Fetch the current file and SHA immediately before updating it.
- Prefer small, coherent commits.
- Do not rewrite unrelated files merely to "clean them up".
- If a task is too large for one change, implement the next vertical slice and document the remaining work.

### Unreal Mobile product direction
This is a mobile-first game engine/editor for Android, not an official Unreal Engine port.

Long-term direction:
- real-time 2D/3D renderer;
- scene/entity/component system;
- touch/stylus-first editor;
- Outliner + Inspector + viewport + Content Browser + timeline;
- visual scripting ("Blueprint Mobile");
- animation and rigging;
- physics, particles, terrain, materials and lighting;
- profiling and optimization;
- Android APK/AAB game export.

The engine must remain modular: Android UI should not contain renderer/gameplay logic, and native engine systems should be reusable outside a single screen.

### Current technical priority
Complete a reliable Vulkan vertical slice in this order:

1. lifecycle and swapchain reliability;
2. shader compilation strategy;
3. graphics pipeline;
4. triangle;
5. depth buffer;
6. indexed cube;
7. camera + transforms;
8. editor viewport integration.

Do not skip directly to advanced editor features while the renderer cannot draw a real primitive.

### Documentation format
Use the README sections:
- Current status
- Roadmap
- Current handoff
- Change log

At the end of each meaningful change, leave a "Next agent" statement with one concrete next task.

## Golden rule

**Code + verification + README handoff are one unit of work.**
