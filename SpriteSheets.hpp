#ifndef PROJR_SPRITESHEETS_HPP
#define PROJR_SPRITESHEETS_HPP

#include "json.hpp"
#include "SpriteSheet.hpp"
#include <iostream>
#include <fstream>

namespace pr {
	class SpriteSheets {
		private:
			CombinedTexture m_textures;
			std::map<std::string, SpriteSheet> m_sheets;
		public:
			SpriteSheets(const std::string& filepath);
			SpriteSheet& get(const std::string& index);
			SpriteSheet& operator[](const std::string& index);
	};
}

#endif