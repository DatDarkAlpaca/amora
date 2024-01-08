#pragma once
#include <string>
#include <numeric>

#include "utils/direction.hpp"
#include "utils/random.hpp"
#include "constants.hpp"

namespace amo
{
	struct User
	{
	public:
		explicit User()
		{
			maxArmor = amo::Random::get(MaxArmorLower, MaxArmorUpper);
			maxLife = amo::Random::get(MaxLifeLower, MaxLifeUpper);

			currentArmor = maxArmor;
			currentLife = maxLife;
		}
	
	public:
		std::string name = "Guts";

		Direction direction = Direction::DOWN;
		uint32_t maxLife = 0, currentLife = 0;
		uint32_t maxArmor = 0, currentArmor = 0;
	};

}