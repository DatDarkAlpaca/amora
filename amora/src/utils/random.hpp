#pragma once
#include <numeric>
#include <random>

namespace amo
{
	template<typename T>
	class Random
	{
	public:
		static T get()
		{
			std::uniform_int_distribution<T> distribution;
			return distribution(m_Generator);
		}

		static T get(T lower, T upper)
		{
			std::uniform_int_distribution<T> distribution(lower, upper);
			return distribution(m_Generator);
		}

	private:
		static inline std::mt19937_64 m_Generator { std::random_device()() };
	};
}