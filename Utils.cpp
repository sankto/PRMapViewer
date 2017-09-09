#include "Utils.hpp"

namespace pr {
	const std::map<std::string, Direction> Utils::DirectionString = {
		{ "None", Direction::None },
		{ "North", Direction::North },
		{ "South", Direction::South },
		{ "West", Direction::West },
		{ "East", Direction::East },
		{ "NorthWest", Direction::NorthWest },
		{ "NorthEast", Direction::NorthEast },
		{ "SouthWest", Direction::SouthWest },
		{ "SouthEast", Direction::SouthEast },
	};

	std::vector<std::string> Utils::splitString(const std::string& str) {
		std::stringstream ss(str);
		std::vector<std::string> result;

		while (ss.good()) {
			std::string substr;
			getline(ss, substr, ',');
			substr.erase(std::remove(substr.begin(), substr.end(), ' '), substr.end()); // this remove spaces.
			result.push_back(substr);
		}
		return result;
	}

	Direction Utils::directionFromString(const std::string& str) {
		Direction result = Direction::None;
		auto split = splitString(str);
		for (auto& dir : split) {
			result = result | DirectionString.at(dir);
		}
		return result;
	}
}