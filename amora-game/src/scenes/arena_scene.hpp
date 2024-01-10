#pragma once
#include <core/scene.hpp>
#include <numeric>

#include "assets/gui_user.hpp"
#include "assets/user.hpp"
#include "assets/map.hpp"

#include <utils/frame.hpp>
#include <core/animation.hpp>

namespace amo
{
    class ArenaScene : public amo::IScene
    {
    public:
        void initialize() override;

        void update(double dt) override;

        void render(amo::AmoraConsole* console) override;

    private:
        void initialize_weapon();

        Weapon choose_weapon();

    private:
        GUIPlayer m_GUIUser;
        Map m_Map;
        User m_User;

    private:
        Animation m_SlashAnimation;

    private:
        std::vector<Weapon> weapons;
    };
}