#pragma once
#include <core/scene.hpp>
#include <numeric>

namespace amo
{
    class ArenaScene : public amo::IScene
    {
    public:
        void update(double dt) override;

        void render(amo::AmoraConsole* console) override;

    private:
        uint32_t m_MapWidth = 80, m_MapHeight = 30;
        float x = 5.f, y = 5.f;
    };
}