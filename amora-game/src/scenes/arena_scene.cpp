#pragma once
#include <core/console.hpp>
#include <physics/collision.hpp>

#include "arena_scene.hpp"
#include "windows_header.hpp"

namespace amo
{
    void ArenaScene::initialize()
    {
        initialize_weapon();

        m_User.rigidbody.position.x = 5;
        m_User.rigidbody.position.y = 5;
        m_User.weapon = choose_weapon();

        m_Map.resize(80, 30);

        CHAR_INFO wall;
        wall.Char.AsciiChar = ' ';
        wall.Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;

        for (uint32_t x = 0; x < m_Map.width(); ++x)
            m_Map.write(x, 0, wall);

        for (uint32_t x = 0; x < m_Map.width(); ++x)
            m_Map.write(x, m_Map.height() - 1, wall);

        for (uint32_t y = 0; y < m_Map.height(); ++y)
            m_Map.write(0, y, wall);

        for (uint32_t y = 0; y < m_Map.height(); ++y)
            m_Map.write(m_Map.width() - 1, y, wall);

        for (uint32_t y = 10; y < 20; ++y)
            m_Map.write(5, y, wall);

        for (uint32_t y = 10; y < 20; ++y)
            m_Map.write(18, y, wall);

        // GUI:
        m_GUIUser.set_map(m_Map);
        m_GUIUser.set_user(m_User);
    }

    void ArenaScene::update(double dt)
    {
        m_User.update(dt);

        // Physics:
        for (uint32_t i = 0; i < m_Map.map().size(); ++i)
        {
            auto x = i % m_Map.width();
            auto y = (i - x) / m_Map.width();

            if (!m_Map.map()[x + m_Map.width() * y].visible)
                continue;

            if (aabb_detection(m_User.rigidbody, vec2u(x, y)))
            {
                Rigidbody wallBody;
                wallBody.position = { (float)x, (float)y };
                wallBody.isStatic = true;

                collision_resolution(m_User.rigidbody, wallBody);
            }
        }

        m_User.stop();
    }

    void ArenaScene::render(amo::AmoraConsole* console)
    {
        // Player:
        m_User.render(console);

        // Map:
        m_Map.render(console);

        // GUI:
        m_GUIUser.render(console);
    }

    void ArenaScene::initialize_weapon()
    {
        weapons.push_back({ "Longsword", 10 });
        weapons.push_back({ "Katana", 10 });
        weapons.push_back({ "Scimitar", 10 });
    }

    Weapon ArenaScene::choose_weapon()
    {
        return weapons[Random::get(0, weapons.size() - 1)];
    }
}