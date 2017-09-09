#ifndef PROJR_TILEDMAP_HPP
#define PROJR_TILEDMAP_HPP

#include "SFML\Graphics.hpp"
#include "SpriteSheets.hpp"
#include "Animation.hpp"
#include "Time.hpp"
#include "GameObject.hpp"
#include "Utils.hpp"

#include <vector>
#include <iostream>
#include <fstream>

namespace pr {
	class TiledMap : private GameObject {
		private:
			int m_width, m_height, m_depth;
			int m_tileSize;
			std::vector<sf::Sprite> m_tiles1;
			std::vector<sf::Sprite> m_tiles2;
			std::vector<sf::Sprite>* m_drawnTiles;
			std::vector<std::vector<std::shared_ptr<sf::RectangleShape>>> m_collisionSides;
			sf::RenderTexture m_renderTexture;
			sf::Sprite m_renderSprite;
			Timer m_switchTimer;

			void switchCallback(const Timer& timer);
			void initializeRender();
		public:
			TiledMap(Game* g, int tileSize, const std::string& mapFilePath);
			TiledMap(Game* g, int tileSize, int width, int height, int depth);

			sf::Sprite& getTile(int x, int y, int z, bool isSecond = false);
			sf::Sprite& getRenderSprite();
			int getTileSize();
			int getPixelWidth();
			int getPixelHeight();
			int getWidth();
			int getHeight();
			std::vector<std::vector<std::shared_ptr<sf::RectangleShape>>>& getCollisions();

			void updateRender();
			void update(const sf::Time& elapsed);
			
			void resetTilesPosition();
			void setTile(const std::string& sheetName, int sheetx, int sheety, int mapx, int mapy, int mapz, bool flipped);
			void loadFromJson(const nlohmann::json& jsonNode);
	};
}

#endif