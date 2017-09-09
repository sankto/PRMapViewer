#include "SpriteSheet.hpp"

namespace pr {
	SpriteSheet::SpriteSheet() {}
	SpriteSheet::SpriteSheet(nlohmann::json& jsonNode) :
		m_name(jsonNode["Id"].get<std::string>()),
		m_file(jsonNode["File"].is_null() ? "" : "..\\..\\GameContent\\SpriteSheets\\" + jsonNode["File"].get<std::string>()),
		m_width(jsonNode["Width"].get<int>()),
		m_height(jsonNode["Height"].get<int>()),
		m_style(jsonNode["Style"].is_null() ? "" : jsonNode["Style"].get<std::string>()),
		m_mixWithOwnStyle(jsonNode["MixWithOwnStyle"].get<bool>()),
		m_linkedSheetId(jsonNode["LinkedSheetId"].is_null() ? "" : jsonNode["LinkedSheetId"].get<std::string>()),
		m_linkedSheet(nullptr),
		m_texture(nullptr),
		m_rect(nullptr) {

		m_tiles.resize(m_width * m_height);
	}

	const bool SpriteSheet::isLinked() const {
		return m_linkedSheet != nullptr;
	}

	SpriteSheet& SpriteSheet::getLinked() const {
		return *m_linkedSheet;
	}

	const std::string& SpriteSheet::getLinkedId() const {
		return m_linkedSheetId;
	}

	const std::string& SpriteSheet::getFile() const {
		return m_file;
	}

	const sf::Texture& SpriteSheet::getTexture() const {
		return *m_texture;
	}

	const sf::IntRect& SpriteSheet::getRect() const {
		return *m_rect;
	}

	const sf::IntRect& SpriteSheet::getTile(int x, int y) const {
		if (m_tiles.empty())
			return EmptyRect;
		return m_tiles[x + y * m_width];
	}

	void SpriteSheet::setLinked(SpriteSheet* sheet) {
		m_linkedSheet = sheet;
	}

	void SpriteSheet::setTexture(CombinedTexture& texture) {
		m_texture = texture.getTexture(m_name);
		m_rect = texture.getRect(m_name);

		int tileWidth = m_rect->width / m_width;
		int tileHeight = m_rect->height / m_height;

		for (int y = 0; y < m_height; y++) {
			for (int x = 0; x < m_width; x++) {
				m_tiles[x + y * m_width] = {
					m_rect->left + x * tileWidth,
					m_rect->top + y * tileHeight,
					tileWidth,
					tileHeight
				};
			}
		}
	}
}