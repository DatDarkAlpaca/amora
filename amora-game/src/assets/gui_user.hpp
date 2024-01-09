#pragma once
#include <amora.hpp>

#include "assets/user.hpp"
#include "assets/map.hpp"

namespace amo
{
	class GUIPlayer
	{
	public:
        void set_user(User& user) { m_User = &user; }
        
        void set_map(const Map& map) { m_Map = map; }

	public:
		void render(AmoraConsole* console)
		{
            CHAR_INFO wall;
            wall.Char.AsciiChar = ' ';
            wall.Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;

            console->write_line(
                { m_Map.width() - 1, 0 },
                { m_Map.width() - 1, m_Map.height() - 1 },
                wall
            );

            console->write_line(
                { console->get_width() - 1, 0 },
                { console->get_width() - 1, m_Map.height() - 1 },
                wall
            );

            console->write_line(
                { m_Map.width() - 1, 0 },
                { console->get_width() - 1, 0 },
                wall
            );

            console->write_line(
                { m_Map.width() - 1,  m_Map.height() - 1 },
                { console->get_width() - 1,  m_Map.height() - 1 },
                wall
            );

            uint32_t guiStartX = m_Map.width();
            uint32_t guiStartY = 1;
            uint32_t attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

            console->write_text("Player Status:", { guiStartX + 1, guiStartY + 1 }, attributes);
            console->write_text("Name: " + m_User->name, { guiStartX + 1, guiStartY + 3 }, attributes);


            console->write_text(
                "HP: " + std::to_string(m_User->currentLife) + "/" + std::to_string(m_User->maxLife) + " | ",
                { guiStartX + 1, guiStartY + 4 }, attributes);
            console->write_text(
                "AR: " + std::to_string(m_User->currentArmor) + "/" + std::to_string(m_User->maxArmor) + " | ",
                { guiStartX + 13, guiStartY + 4 }, attributes);

            console->write_text("Player Items:", { guiStartX + 1, guiStartY + 8 }, attributes);
            console->write_text(
                "Weapon: " + m_User->weapon.name,
                { guiStartX + 1, guiStartY + 9 }, attributes);
		}

    private:
        NON_OWNING User* m_User = nullptr;
        Map m_Map;
	};
}