#pragma once
#include <amora.hpp>
#include <numeric>

#include "assets/gui_user.hpp"
#include "assets/user.hpp"
#include "assets/map.hpp"

namespace amo
{
    class ArenaScene : public amo::IView
    {
    public:
        void initialize() override;

        void update(double dt) override;

        void render(amo::AmoraConsole* console) override;

    private:
        void update_player_movement(double dt);

    private:
        void initialize_weapon();

        Weapon choose_weapon();

    private:
        Scene m_Scene;
        GUIPlayer m_GUIUser;

    private:
        std::vector<Weapon> weapons;
    };
}