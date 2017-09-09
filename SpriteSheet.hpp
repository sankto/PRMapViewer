#ifndef PROJR_SPRITESHEET_HPP
#define PROJR_SPRITESHEET_HPP

#include "json.hpp"
#include "CombinedTexture.hpp"

namespace pr {
	class SpriteSheet {
		private:
			const sf::IntRect EmptyRect;

			std::string m_name;
			std::string m_file;
			int m_width;
			int m_height;
			std::string m_style;
			bool m_mixWithOwnStyle;
			std::string m_linkedSheetId;
			sf::Texture* m_texture;
			sf::IntRect* m_rect;
			SpriteSheet* m_linkedSheet;
			std::vector<sf::IntRect> m_tiles;
		public:
			SpriteSheet();
			SpriteSheet(nlohmann::json& jsonNode);

			const bool isLinked() const;
			SpriteSheet& getLinked() const;
			const std::string& getLinkedId() const;
			const std::string& getFile() const;
			const sf::Texture& getTexture() const;
			const sf::IntRect& getRect() const;
			const sf::IntRect& getTile(int x, int y) const;

			void setLinked(SpriteSheet* sheet);
			void setTexture(CombinedTexture& texture);
	};
}

#endif