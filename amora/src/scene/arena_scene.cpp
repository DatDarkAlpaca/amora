#pragma once
#include "arena_scene.hpp"
#include "windows_header.h"
#include "console/console.hpp"

namespace amo
{
	void ArenaScene::update(double dt)
	{
        constexpr float speed = 16.5f;

        if (GetAsyncKeyState(0x53) < 0)
            y += speed * dt;

        if (GetAsyncKeyState(0x57) < 0)
            y -= speed * dt;

        if (GetAsyncKeyState(0x44) < 0)
            x += speed * dt;

        if (GetAsyncKeyState(0x41) < 0)
            x -= speed * dt;
	}

    void ArenaScene::render(amo::AmoraConsole* console)
    {
        // Pallete:
        CHAR_INFO wall;
        wall.Char.AsciiChar = ' ';
        wall.Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;

        // Map:
        console->write_line({ 0, 0 }, { m_MapWidth - 1  , 0 }, wall);
        console->write_line({ 0, m_MapHeight - 1 }, { m_MapWidth - 1  , m_MapHeight - 1 }, wall);
        console->write_line({ 0, 0 }, { 0               , m_MapHeight - 1 }, wall);
        console->write_line({ m_MapWidth - 1, 0 }, { m_MapWidth - 1  , m_MapHeight - 1 }, wall);

        // Player:
        {
            CHAR_INFO info;
            info.Char.AsciiChar = 'X';
            info.Attributes = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
            console->write_text("HP: 10/10", { (uint32_t)x - 4, (uint32_t)y - 1 }, FOREGROUND_BLUE);
            console->write(x, y, info);
        }

        // GUI:
        {
            uint32_t guiStartX = m_MapWidth;
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
    }
}