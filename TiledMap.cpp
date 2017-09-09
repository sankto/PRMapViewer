#include "TiledMap.hpp"
#include "Game.hpp"

namespace pr {
	TiledMap::TiledMap(Game* g, int tileSize, const std::string& mapFilePath) :
		GameObject(*g),
		m_tiles1(0), m_tiles2(0),
		m_tileSize(tileSize), m_width(0), m_height(0), m_depth(0), m_collisionSides(0),
		m_switchTimer(sf::milliseconds(Animation::SWITCH_INTERVAL), [&](const Timer& timer) { switchCallback(timer); }),
		m_drawnTiles(nullptr) {

		nlohmann::json json;
		std::ifstream i{ mapFilePath };
		i >> json;
		loadFromJson(json);
	}
	
	TiledMap::TiledMap(Game* g, int tileSize, int width, int height, int depth) :
		GameObject(*g),
		m_tiles1(width * height * depth), m_tiles2(width * height * depth),
		m_tileSize(tileSize), m_width(width), m_height(height), m_depth(depth),
		m_switchTimer(sf::milliseconds(Animation::SWITCH_INTERVAL), [&](const Timer& timer) { switchCallback(timer); }) {

		m_drawnTiles = &m_tiles1;
		initializeRender();
	}

	void TiledMap::switchCallback(const Timer& timer) {
		if (m_drawnTiles == &m_tiles1)
			m_drawnTiles = &m_tiles2;
		else m_drawnTiles = &m_tiles1;
		updateRender();
	}

	void TiledMap::initializeRender() {
		if (m_renderTexture.create(m_width * m_tileSize, m_height * m_tileSize)) {
			// error..
		}
	}
	
	sf::Sprite& TiledMap::getTile(int x, int y, int z, bool isSecond) {
		return (isSecond ? m_tiles2 : m_tiles1)[x * m_height * m_depth + y * m_depth + z];
	}

	sf::Sprite& TiledMap::getRenderSprite() {
		return m_renderSprite;
	}

	int TiledMap::getTileSize() {
		return m_tileSize;
	}

	int TiledMap::getPixelWidth() {
		return m_width * m_tileSize;
	}

	int TiledMap::getPixelHeight() {
		return m_height * m_tileSize;
	}

	int TiledMap::getWidth() {
		return m_width;
	}

	int TiledMap::getHeight() {
		return m_height;
	}

	std::vector<std::vector<std::shared_ptr<sf::RectangleShape>>>& TiledMap::getCollisions() {
		return m_collisionSides;
	}

	void TiledMap::updateRender() {
		m_renderTexture.clear();
		for (auto& tile : *m_drawnTiles) {
			m_renderTexture.draw(tile);
		}
		m_renderTexture.display();
		if (m_renderSprite.getTexture() == nullptr) {
			m_renderSprite.setTexture(m_renderTexture.getTexture());
		}
	}

	void TiledMap::update(const sf::Time& elapsed) {
		m_switchTimer.add(elapsed);
	}

	void TiledMap::resetTilesPosition() {
		for (int z = 0; z < m_depth; z++) {
			for (int y = 0; y < m_height; y++) {
				for (int x = 0; x < m_width; x++) {
					getTile(x, y, z).setPosition(
						static_cast<float>(x * m_tileSize),
						static_cast<float>(y * m_tileSize)
					);
					getTile(x, y, z, true).setPosition(
						static_cast<float>(x * m_tileSize),
						static_cast<float>(y * m_tileSize)
					);
				}
			}
		}
	}

	void TiledMap::setTile(const std::string& sheetName, int sheetx, int sheety, int mapx, int mapy, int mapz, bool flipped) {
		auto& sheet1 = m_game->getSheets()->get(sheetName);
		auto& sheet2 = sheet1.isLinked() ? sheet1.getLinked() : sheet1;
		auto& tile1 = getTile(mapx, mapy, mapz);
		auto& tile2 = getTile(mapx, mapy, mapz, true);
		
		tile1.setTexture(sheet1.getTexture());
		tile1.setTextureRect(sheet1.getTile(sheetx, sheety));
		tile2.setTexture(sheet2.getTexture());
		tile2.setTextureRect(sheet2.getTile(sheetx, sheety));
		if (flipped) {
			tile1.setTextureRect({
				tile1.getTextureRect().left + tile1.getTextureRect().width,
				tile1.getTextureRect().top, -tile1.getTextureRect().width, tile1.getTextureRect().height
			});
			tile2.setTextureRect({
				tile2.getTextureRect().left + tile2.getTextureRect().width,
				tile2.getTextureRect().top, -tile2.getTextureRect().width, tile2.getTextureRect().height
			});
		}
	}

	void TiledMap::loadFromJson(const nlohmann::json& jsonNode) {
		const int DEPTH = 3; // ground, doodads, npcs
		const int GROUND_Z = 0;
		const int DOODADS_Z = 1;
		const int NPCS_Z = 2;
		
		// We first load the size of the map, and init the tile array accordingly.
		// m_tiles1 and m_tiles2 are alternated ingame to animate the tiles.
		m_width = jsonNode["Width"].get<int>();
		m_height = jsonNode["Height"].get<int>();
		m_depth = DEPTH;
		m_tiles1.resize(m_width * m_height * DEPTH);
		m_tiles2.resize(m_width * m_height * DEPTH);
		m_collisionSides.resize(m_width * m_height);
		m_drawnTiles = &m_tiles1;

		// We init the Render Texture of which things are drawn on, and we set the position of the tiles.
		initializeRender();
		resetTilesPosition();

		// This section is for loading the 'ground' and 'doodads' layers.
		auto currentZ = GROUND_Z; // this could be any value, actually.
		for (auto& layer : jsonNode["Layers"]) {
			if (layer["Name"].get<std::string>() == "ground")
				currentZ = GROUND_Z;
			else if (layer["Name"].get<std::string>() == "doodads")
				currentZ = DOODADS_Z;
			else continue; // It's not the ground or doodads layer, we skip this one.
			auto i = 0;
			for (auto& tile : layer["Tiles"]) {
				if (!tile.is_null()) {
					auto mapx = i % m_width;
					auto mapy = i / m_width;
					auto sheetName = tile["SId"].get<std::string>();
					auto sheetx = tile["SX"].get<int>();
					auto sheety = tile["SY"].get<int>();
					setTile(sheetName, sheetx, sheety, mapx, mapy, currentZ, false);
				}
				i++;
			}
		}
		// This section is to load NPCs.
		for (auto& npc : jsonNode["NPCs"]) {
			auto id = npc["Id"].get<std::string>();
			auto mapx = npc["X"].get<int>();
			auto mapy = npc["Y"].get<int>();
			auto sheetName = npc["SheetTile"]["SheetId"].get<std::string>();
			auto sheetx = npc["SheetTile"]["X"].get<int>();
			auto sheety = npc["SheetTile"]["Y"].get<int>();
			auto flipped = npc["Flipped"].get<bool>();
			setTile(sheetName, sheetx, sheety, mapx, mapy, NPCS_Z, flipped);
		}
		// This section is to load collisions.
		auto i = 0;
		for (auto& coll : jsonNode["Collisions"]) {
			m_collisionSides[i] = { nullptr, nullptr, nullptr, nullptr };
			auto mapx = i % m_width;
			auto mapy = i / m_width;
			auto dir = Utils::directionFromString(coll.get<std::string>());

			if (hasFlag(dir, Direction::North)) {
				m_collisionSides[i][0] = std::make_shared<sf::RectangleShape>(sf::Vector2f{static_cast<float>(m_tileSize) - 3.f, 1.f});
				m_collisionSides[i][0]->setPosition({mapx * static_cast<float>(m_tileSize) + 2.f, mapy * static_cast<float>(m_tileSize) + 1.f });
				m_collisionSides[i][0]->setFillColor(sf::Color::Blue);
			}
			if (hasFlag(dir, Direction::South)) {
				m_collisionSides[i][1] = std::make_shared<sf::RectangleShape>(sf::Vector2f{static_cast<float>(m_tileSize) - 3.f, 1.f});
				m_collisionSides[i][1]->setPosition({mapx * static_cast<float>(m_tileSize) + 2.f, mapy * static_cast<float>(m_tileSize) + (static_cast<float>(m_tileSize) - 1.f) });
				m_collisionSides[i][1]->setFillColor(sf::Color::Blue);
			}
			if (hasFlag(dir, Direction::West)) {
				m_collisionSides[i][2] = std::make_shared<sf::RectangleShape>(sf::Vector2f{1.f, static_cast<float>(m_tileSize) - 3.f});
				m_collisionSides[i][2]->setPosition({mapx * static_cast<float>(m_tileSize) + 1.f, mapy * static_cast<float>(m_tileSize) + 2.f});
				m_collisionSides[i][2]->setFillColor(sf::Color::Blue);
			}
			if (hasFlag(dir, Direction::East)) {
				m_collisionSides[i][3] = std::make_shared<sf::RectangleShape>(sf::Vector2f{1.f, static_cast<float>(m_tileSize) - 3.f});
				m_collisionSides[i][3]->setPosition({mapx * static_cast<float>(m_tileSize) + (static_cast<float>(m_tileSize) - 1.f), mapy * static_cast<float>(m_tileSize) + 2.f});
				m_collisionSides[i][3]->setFillColor(sf::Color::Blue);
			}
			i++;
		}
		updateRender();
	}
}