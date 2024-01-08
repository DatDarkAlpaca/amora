#pragma once
#include <core/scene.hpp>
#include <numeric>

#include "assets/user.hpp"
#include "assets/map.hpp"

namespace amo
{
    class ArenaScene : public amo::IScene
    {
    public:
        void initialize() override;

        void update(double dt) override;

        void render(amo::AmoraConsole* console) override;

    private:
        Map m_Map;
        User m_User;
    };
}