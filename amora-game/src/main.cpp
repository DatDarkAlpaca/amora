#include <amora.hpp>

#include "scenes/splash_scene.hpp"
#include "scenes/arena_scene.hpp"

#include "scenes/overlays/system_overlay.hpp"

int main()
{
    using namespace amo;

    Application app("Amora v1.0", 120, 30);
    app.add_overlay(std::make_unique<SystemOverlay>());

    app.add_scene(std::make_unique<SplashScene>());
    app.add_scene(std::make_unique<ArenaScene>());

    app.set_scene(0);
    app.run();
}