#include "application/application.hpp"
#include "scene/splash_scene.hpp"
#include "scene/arena_scene.hpp"

int main()
{
    using namespace amo;

    Application app("Amora v1.0", 120, 30);
    app.add_scene(std::make_unique<SplashScene>());
    app.add_scene(std::make_unique<ArenaScene>());
    
    app.set_scene(0);
    app.run();
}