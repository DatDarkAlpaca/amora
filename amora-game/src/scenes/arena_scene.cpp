#pragma once
#include <core/console.hpp>
#include <physics/collision.hpp>

#include "arena_scene.hpp"
#include "windows_header.hpp"

namespace amo
{
    void ArenaScene::initialize()
    {
        m_User.rigidbody.position.x = 5;
        m_User.rigidbody.position.y = 5;

        m_Map.resize(80, 30);

        char wall = ' ';
        
        m_Map.write(5, 5, wall);
        m_Map.write(5, 6, wall);
        m_Map.write(5, 7, wall);
        m_Map.write(5, 8, wall);
        m_Map.write(5, 9, wall);
    }

    void ArenaScene::update(double dt)
    {
        constexpr float speed = 16.5f;

        if (GetAsyncKeyState(0x53) < 0)
            m_User.rigidbody.velocity.y += speed * (float)dt;

        if (GetAsyncKeyState(0x57) < 0)
            m_User.rigidbody.velocity.y -= speed * (float)dt;

        if (GetAsyncKeyState(0x44) < 0)
            m_User.rigidbody.velocity.x += speed * (float)dt;

        if (GetAsyncKeyState(0x41) < 0)
            m_User.rigidbody.velocity.x -= speed * (float)dt;

        /*Rigidbody wall;
        wall.position = { 5,5 };
        wall.isStatic = true;
        if (aabb_detection(m_User.rigidbody, wall))
        {
            collision_resolution(m_User.rigidbody, wall);
        }
        else
        {
            m_User.rigidbody.position.x += m_User.rigidbody.velocity.x;
            m_User.rigidbody.position.y += m_User.rigidbody.velocity.y;
        }*/
        m_User.rigidbody.position.x += m_User.rigidbody.velocity.x;
        m_User.rigidbody.position.y += m_User.rigidbody.velocity.y;

        m_User.rigidbody.velocity.x = 0;
        m_User.rigidbody.velocity.y = 0;
    }

    void ArenaScene::render(amo::AmoraConsole* console)
    {
        // Pallete:
        CHAR_INFO wall;
        wall.Char.AsciiChar = ' ';
        wall.Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;

        // Player:
        {
            CHAR_INFO info;
            info.Char.AsciiChar = 'X';
            info.Attributes = FOREGROUND_INTENSITY | FOREGROUND_RED;
            console->write_text("HP: 10/10", { (uint32_t)m_User.rigidbody.position.x - 4, (uint32_t)m_User.rigidbody.position.y - 1 }, FOREGROUND_BLUE);
            console->write((uint32_t)m_User.rigidbody.position.x, (uint32_t)m_User.rigidbody.position.y, info);
        }

        // GUI:
        {
            uint32_t guiStartX = m_Map.width();
            uint32_t guiStartY = 1;

            uint32_t attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

            console->write_text("Player Status:", { guiStartX + 1, guiStartY + 1 }, attributes);

            console->write_text("Name: Guts", { guiStartX + 1, guiStartY + 3 }, attributes);
            console->write_text("HP: 10/10 | ", { guiStartX + 1, guiStartY + 4 }, attributes);
            console->write_text("AR: 10/10", { guiStartX + 13, guiStartY + 4 }, attributes);


            console->write_text("Player Items:", { guiStartX + 1, guiStartY + 8 }, attributes);
            console->write_text("Weapon: Longsword", { guiStartX + 1, guiStartY + 9 }, attributes);

            console->write_line({ 0, 0 }, { console->get_width() - 1, 0 }, wall);
            console->write_line({ 0, console->get_height() - 1 }, { console->get_width() - 1, console->get_height() - 1 }, wall);
            console->write_line({ console->get_width() - 1, 0 },
                { console->get_width() - 1, console->get_height() - 1 }, wall);
        }

        // Map:
        {
            for (uint32_t y = 0; y < m_Map.height(); ++y)
            {
                for (uint32_t x = 0; x < m_Map.width(); ++x)
                {
                    auto cell = m_Map.map()[x + m_Map.width() * y];

                    if (!cell.visible)
                        continue;

                    console->write(x, y, cell.info);
                }
            }
        }

        console->write_text(std::to_string(m_User.rigidbody.position.x), { 0, 0 }, BACKGROUND_RED);
    }
}