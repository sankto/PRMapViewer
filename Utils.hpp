#ifndef PROJR_UTILS_HPP
#define PROJR_UTILS_HPP

#include <vector>
#include <map>
#include <sstream> // stringstream
#include <algorithm> // to remove whitespace

namespace pr {
	enum class Direction {
		None = 0,
		North = 1 << 0,
		South = 1 << 1,
		West = 1 << 2,
		East = 1 << 3,
		NorthWest = 1 << 4,
		NorthEast = 1 << 5,
		SouthWest = 1 << 6,
		SouthEast = 1 << 7
	};

	inline Direction operator|(Direction a, Direction b) {
		return static_cast<Direction>(static_cast<int>(a) | static_cast<int>(b));
	}

	inline bool hasFlag(Direction a, Direction b) {
		return ((static_cast<int>(a) & static_cast<int>(b)) == static_cast<int>(b));
	}

	class Utils {
		public:
			static const std::map<std::string, Direction> DirectionString;

			static std::vector<std::string> splitString(const std::string& str);
			static Direction directionFromString(const std::string& str);
	};
}

#endif