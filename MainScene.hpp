#ifndef PROJR_MAINSCENE_HPP
#define PROJR_MAINSCENE_HPP

#include "IScene.hpp"
#include "Game.hpp"
#include "TiledMap.hpp"

#include <string>
#include <math.h> // floor

namespace pr {
	class MainScene : public IScene {
		private:
			std::shared_ptr<TiledMap> m_map;

			bool m_dragging;
			sf::Vector2i m_dragLoc;

			sf::Font m_font;
			sf::Text m_tileLabel;

			sf::RectangleShape m_mouseTile;
			sf::Vector2i m_hoveredTile;

			std::vector<sf::RectangleShape> m_lines;
			bool m_isLinesDrawn;

			bool m_isCollisionsDrawn;

			void initLines();
			void updateMouseTile();
			void handleMovements(const sf::Event& event);
			void handleOptions(const sf::Event& event);
		public:
			MainScene(const std::string& filepath);
			const std::unique_ptr<std::string> handleInputs(const sf::Event& event);
			const std::unique_ptr<std::string> update(const sf::Time& elapsed);
			void display();
	};
}

#endif