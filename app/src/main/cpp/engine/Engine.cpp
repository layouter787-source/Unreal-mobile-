#include "Engine.h"
namespace um {
bool Engine::initialize(ANativeWindow* window) { return renderer_.initialize(window); }
void Engine::shutdown() { renderer_.shutdown(); }
}
