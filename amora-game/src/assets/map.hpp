#pragma once
#include <amora.hpp>
#include <vector>

namespace amo
{
	struct MapCell
	{
		CHAR_INFO info;
		bool visible;
	};

	class Map
	{
	public:
		explicit Map(uint32_t width, uint32_t height)
			: m_Width(width)
			, m_Height(height)
		{
			resize(width, height);
		}

		explicit Map() = default;

	public:
		void resize(uint32_t width, uint32_t height)
		{
			m_Width = width;
			m_Height = height;

			m_Map.resize((size_t)width * (size_t)height);

			CHAR_INFO voidCell;
			voidCell.Attributes = 0;
			voidCell.Char.AsciiChar = ' ';

			MapCell cell;
			cell.visible = false;
			cell.info = voidCell;

			std::fill(m_Map.begin(), m_Map.end(), cell);
		}

		void render(AmoraConsole* console)
		{
			for (uint32_t y = 0; y < m_Height; ++y)
			{
				for (uint32_t x = 0; x < m_Width; ++x)
				{
					auto cell = m_Map[x + m_Width * y];

					if (!cell.visible)
						continue;

					console->write(x, y, cell.info);
				}
			}
		}

	public:
		void write(uint32_t x, uint32_t y, char character, bool visible = true)
		{
			uint32_t index = x + m_Width * y;

			CHAR_INFO info;
			info.Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY |
							  BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
			info.Char.AsciiChar = character;

			if (index >= 0 && index <= m_Map.size())
				m_Map[index] = { info, visible };
		}

		void write(uint32_t x, uint32_t y, const CHAR_INFO& info, bool visible = true)
		{
			uint32_t index = x + m_Width * y;

			if (index >= 0 && index <= m_Map.size())
				m_Map[x + (size_t)m_Width * y] = { info, visible };
		}

	public:
		const std::vector<MapCell>& map() const { return m_Map; }

		std::vector<MapCell>& map() { return m_Map; }
		
		uint32_t width() const { return m_Width; }

		uint32_t height() const { return m_Height; }

	private:
		std::vector<MapCell> m_Map;
		uint32_t m_Width, m_Height;
	};
}