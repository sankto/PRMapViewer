#include "SpriteSheets.hpp"

namespace pr {
	SpriteSheets::SpriteSheets(const std::string& filepath) {
		std::ifstream i{ filepath };
		nlohmann::json sheetsJson;
		i >> sheetsJson;
		
		for (auto &sheetNode : sheetsJson["SpriteSheets"]) {
			m_sheets.insert(std::make_pair(
				sheetNode["Id"].get<std::string>(),
				SpriteSheet(sheetNode)
			));
		}
		for (auto &sheet : m_sheets) {
			if (!sheet.second.getLinkedId().empty()) {
				sheet.second.setLinked(&m_sheets[sheet.second.getLinkedId()]);
			}
		}
		ImagesHolder imgs;
		for (const auto &sheet : m_sheets) {
			if (!sheet.second.getFile().empty()) {
				imgs.loadAndAdd(sheet.first, sheet.second.getFile());
			}
		}
		m_textures.processImages(imgs);
		for (auto &sheet : m_sheets) {
			if (!sheet.second.getFile().empty()) {
				sheet.second.setTexture(m_textures);
			}
		}
	}

	SpriteSheet& SpriteSheets::get(const std::string& index) {
		return m_sheets[index];
	}

	SpriteSheet& SpriteSheets::operator[](const std::string& index) {
		return m_sheets[index];
	}
}