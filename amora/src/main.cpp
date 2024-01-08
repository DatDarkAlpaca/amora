#include "application/application.hpp"
#include "scene/arena_scene.hpp"

int main()
{
    using namespace amo;

    Application app("Amora v1.0", 120, 30);
    app.add_scene(std::make_unique<ArenaScene>());
    app.run();
}