#pragma once
#include <numeric>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace amo
{
	struct Frame
	{
		std::string frameData;
		uint32_t duration;
	};

	inline std::vector<Frame> read_animation_file(const std::string& filepath)
	{
		std::vector<Frame> frames;
		std::fstream file(filepath);

		std::string line;
		while (std::getline(file, line))
		{
			if (line.starts_with("#"))
				continue;

			std::istringstream ss(line);

			std::string frameFilepath;
			uint32_t frameDuration = 0;

			std::string part;
			size_t i = 0;
			while (std::getline(ss, part, ','))
			{
				if (i == 0)
				{
					std::erase(part, '"');
					frameFilepath = part;
				}
				if (i == 1)
					frameDuration = std::stoul(part);
				++i;
			}

			std::fstream frameFile(frameFilepath);

			std::stringstream frameStringStream;
			frameStringStream << frameFile.rdbuf();

			frames.push_back({ frameStringStream.str(), frameDuration});
		}

		return frames;
	}
}