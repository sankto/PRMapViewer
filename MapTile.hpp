#ifndef PROJR_MAPTILE_HPP
#define PROJR_MAPTILE_HPP

#include "SFML\Graphics.hpp"

namespace pr {
	class MapTile {
		private:
			sf::Sprite m_sprite;
		public:
			MapTile();
			~MapTile();

			sf::Sprite& getSprite();
	};
}

#endif
