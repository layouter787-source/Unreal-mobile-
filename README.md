# Unreal Mobile

**Unreal Mobile** is an Android-first game engine/editor prototype. It is an independent project inspired by the workflow of professional engines, not an official Unreal Engine port.

## Current status (living handoff)

**Current stage:** native Android + Vulkan presentation foundation, with persistent multi-agent handoff rules.

Implemented in repository:
- Android Gradle/Kotlin application scaffold (Java 17, compile/target SDK 35, min SDK 26).
- Native C++ engine entry point and JNI bridge.
- Vulkan instance/surface/device selection.
- Swapchain, image views, render pass, framebuffers, command buffers and frame synchronization.
- A first render path that clears the swapchain to a dark color and presents it.
- Swapchain dirty flag and recreation path for resize / `VK_ERROR_OUT_OF_DATE_KHR` / `VK_SUBOPTIMAL_KHR`.
- GitHub Actions workflows for debug CI and manually triggered release builds.

**Not yet implemented:** a graphics pipeline, shaders, a triangle/cube, depth buffer, camera, scene serialization, asset importing, editor overlay UI, and APK build verification. The current Vulkan output is only a clear color; do not describe it as a working 3D renderer yet.

## Mandatory collaboration handoff for Cloud / Claude / any coding agent

This README is the persistent project handoff. Every agent working on this repository MUST follow these rules:

1. **Before editing:** read this README and inspect the actual current files and latest commits. Do not assume an earlier chat summary is current.
2. **After every meaningful change:** update this README in the same change/commit. Record:
   - date (UTC),
   - what changed and why,
   - files changed,
   - commit SHA if known,
   - build/test commands actually run and their real results,
   - known bugs, limitations, and the exact next steps.
3. **Never claim tests/builds passed unless they were actually run and the logs support that claim.** If no Android device/SDK/build runner is available, state that verification is pending.
4. **Do not overwrite another agent's work.** Fetch the latest branch/file SHA before modifying files; make small, coherent changes and inspect the diff/commit afterwards.
5. **Keep this handoff truthful and concise.** Move completed tasks into “Completed”; keep unverified tasks in “Pending verification”.
6. **Do not try to implement the entire roadmap in one giant patch.** Build a testable vertical slice at a time and leave a clear next action.
7. If working with another agent (Cloud/Claude), communicate the exact commit SHA, changed paths, verification status and next task in the handoff. The agents cannot assume they share conversational memory.

## Architecture

```text
Android app (Kotlin)
  └── VulkanView / Surface lifecycle
      └── JNI bridge (NativeEngineBridge.cpp)
          └── Engine
              └── VulkanRenderer
                  ├── instance / physical + logical device
                  ├── Android surface + swapchain
                  ├── image views / render pass / framebuffers
                  ├── command buffers + synchronization
                  └── clear-and-present frame
```

## Roadmap (ordered)

### Stage 0 — Build and lifecycle reliability
- [x] Android/Kotlin/C++ scaffolding.
- [x] Vulkan clear-and-present path (implementation present; device/build verification pending).
- [x] Initial swapchain recreation logic.
- [ ] Run GitHub Actions and fix actual build failures.
- [ ] Audit Vulkan failure cleanup and surface lifecycle.
- [ ] Add logging with actionable VkResult messages.

### Stage 1 — First actual 3D primitive
- [ ] Add shader compilation/build integration appropriate for Android.
- [ ] Create shader modules and graphics pipeline.
- [ ] Add vertex/index buffers and draw a triangle first.
- [ ] Add depth attachment and draw a cube.
- [ ] Add basic camera matrices and resize-aware viewport.
- [ ] Verify on at least one Android Vulkan-capable device or emulator.

### Stage 2 — Engine foundations
- [ ] Scene/entity/component model and transform hierarchy.
- [ ] Project and scene serialization with versioned file format.
- [ ] Camera/input abstraction and touch gestures.
- [ ] Resource lifetime and renderer diagnostics.

### Stage 3 — Editor
- [ ] Editor UI layered around the Vulkan viewport.
- [ ] Scene Outliner and Inspector backed by actual scene data.
- [ ] Select/move/rotate/scale gizmos.
- [ ] Undo/redo and autosave.

### Stage 4 — Content and gameplay
- [ ] GLTF/GLB import first, then OBJ/FBX assessment.
- [ ] Materials, textures, lighting and environment.
- [ ] Blueprint Mobile visual scripting.
- [ ] Physics, animation/rigging, particles and terrain.

### Stage 5 — Build and release
- [ ] Reliable APK/AAB export for games made in the editor.
- [ ] Profiling: FPS, CPU, GPU, RAM, draw calls and triangles.
- [ ] Device compatibility, performance and crash testing.
- [ ] Signing, release documentation and sample projects.

## Repository map

- `app/src/main/java/com/layos/unrealmobile/MainActivity.kt` — Android entry activity.
- `app/src/main/java/com/layos/unrealmobile/VulkanView.kt` — surface lifecycle and native calls.
- `app/src/main/cpp/NativeEngineBridge.cpp` — JNI and native-window ownership.
- `app/src/main/cpp/engine/Engine.h/.cpp` — engine façade.
- `app/src/main/cpp/engine/vulkan/VulkanRenderer.h/.cpp` — Vulkan presentation foundation.
- `app/src/main/cpp/CMakeLists.txt` — native build definition.
- `CLAUDE.md` — mandatory continuation/handoff instructions for Claude and other coding agents.
- `.github/workflows/android-ci.yml` — debug build workflow on push/PR/manual dispatch.
- `.github/workflows/android-release.yml` — manually triggered release build workflow.

## Current handoff — 2026-10-04

- Latest known implementation commit: `ffd80d686e2342832e0a4ef7cd7b62fdd81155a2` (swapchain recreation).
- Additional header declaration commit: `3fe75569f677324c33785b3b995a5dd63adbc75b`.
- Earlier native renderer bridge and Actions commits are present in repository history.
- **Verification:** no successful Android CI result has been confirmed in this handoff. Treat compilation and runtime as unverified until an actual workflow/device result is inspected.
- **Immediate next task:** run/inspect debug CI, then implement the smallest real graphics pipeline and draw a triangle. Do not jump to cube/camera until triangle rendering builds and is verified.
- **Agent handoff:** `CLAUDE.md` now makes README updates, verification honesty, SHA inspection and concrete next-task documentation mandatory for every agent.

## Change log

### 2026-10-04 — Vulkan fence recovery
- Moved fence reset until command recording succeeds and added recovery that recreates the fence in a signaled state when fence reset/submission fails, preventing a future frame from waiting forever.
- Files: `app/src/main/cpp/engine/vulkan/VulkanRenderer.h`, `app/src/main/cpp/engine/vulkan/VulkanRenderer.cpp`.
- Commits: `6f24b0f07464d709433fdd82a86695d2a347c494`, `553928fd7de044358db366bfb9c1bdc9d5f5ff95`.
- Verification: no Android build/runtime test executed in this environment; pending CI/device verification.

### 2026-10-04 — Persistent handoff and collaboration rules
- Added `CLAUDE.md` with mandatory instructions for Claude/other agents to read the README, inspect current SHAs, document every meaningful change, and never claim unverified builds/tests.
- Files: `CLAUDE.md`, `README.md`.
- Verification: documentation-only change; no build/test run performed.

### 2026-10-04 — Persistent handoff and collaboration rules
- Documented actual implementation state, limitations, ordered roadmap, verification policy and collaboration protocol for Cloud/Claude and future agents.
- Files: `README.md`.
- Verification: documentation-only change; no build/test run performed.
