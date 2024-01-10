#pragma once
#include <numeric>
#include <string>

#include "utils/direction.hpp"
#include "utils/random.hpp"
#include "weapon.hpp"

namespace amo
{
	struct User
	{
	public:
		explicit User()
		{
			maxArmor = amo::Random<uint32_t>::get(MaxArmorLower, MaxArmorUpper);
			maxLife = amo::Random<uint32_t>::get(MaxLifeLower, MaxLifeUpper);

			currentArmor = maxArmor;
			currentLife = maxLife;
		}

	public:
		void render(NON_OWNING AmoraConsole* console)
		{
			render_player(console);

			render_health_overlay(console);
		}

		void update(double dt)
		{
			direction = Direction::NONE;

			/*
			if (GetAsyncKeyState(0x53) < 0)
			{
				rigidbody.velocity.y += rigidbody.speed * (float)dt;
				direction = Direction::BOTTOM;
			}

			if (GetAsyncKeyState(0x57) < 0)
			{
				rigidbody.velocity.y -= rigidbody.speed * (float)dt;
				direction = Direction::TOP;
			}

			if (GetAsyncKeyState(0x44) < 0)
			{
				rigidbody.velocity.x += rigidbody.speed * (float)dt;
				direction = Direction::RIGHT;
			}

			if (GetAsyncKeyState(0x41) < 0)
			{
				rigidbody.velocity.x -= rigidbody.speed * (float)dt;
				direction = Direction::LEFT;
			}

			update_sprite();

			rigidbody.position.x += rigidbody.velocity.x;
			rigidbody.position.y += rigidbody.velocity.y;
			*/
		}

		void stop()
		{
			//rigidbody.velocity.x = 0;
			//rigidbody.velocity.y = 0;
		}
	
	private:
		void render_player(NON_OWNING AmoraConsole* console)
		{
			CHAR_INFO info;
			info.Char.AsciiChar = m_UserSprite;
			info.Attributes = UserAttribute;

			/*console->write(
				(uint32_t)rigidbody.position.x,
				(uint32_t)rigidbody.position.y,
				info
			);*/
		}

		void render_health_overlay(NON_OWNING AmoraConsole* console)
		{
			/*
			console->write_text(
				"HP: " + std::to_string(currentLife) + "/" + std::to_string(maxLife),
				{ (uint32_t)rigidbody.position.x - 4, (uint32_t)rigidbody.position.y - 1 },
				FOREGROUND_BLUE
			);
			*/
		}

	private:
		void update_sprite()
		{
			switch (direction)
			{
				case Direction::LEFT:
					m_UserSprite = '<';
					break;

				case Direction::RIGHT:
					m_UserSprite = '>';
					break;

				case Direction::BOTTOM:
					m_UserSprite = 'v';
					break;

				case Direction::TOP:
					m_UserSprite = '^';
					break;

				default:
					m_UserSprite = 'x';
					break;
			}
		}

	public:
		std::string name = "Guts";
		uint32_t maxLife = 0, currentLife = 0;
		uint32_t maxArmor = 0, currentArmor = 0;

	public:
		Weapon weapon;
		Direction direction;

	private:
		char m_UserSprite = 'x';

	public:
		constexpr static inline uint32_t MaxLifeLower = 10;
		constexpr static inline uint32_t MaxLifeUpper = 20;

		constexpr static inline uint32_t MaxArmorLower = 10;
		constexpr static inline uint32_t MaxArmorUpper = 20;

	private:
		constexpr static inline uint32_t UserAttribute = FOREGROUND_INTENSITY | FOREGROUND_RED;
	};
}