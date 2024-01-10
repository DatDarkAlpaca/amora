#pragma once
#include <optional>
#include <fstream>
#include <sstream>
#include <ranges>
#include <iostream>

namespace amo
{
	inline std::optional<std::string> read_file(const std::string& filepath)
	{
		std::fstream file(filepath);

		std::stringstream ss;
		ss << file.rdbuf();

		return ss.str();
	}
}