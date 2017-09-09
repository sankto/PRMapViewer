#ifndef PROJR_GAME_HPP
#define PROJR_GAME_HPP

#include "SpriteSheets.hpp"
#include "SceneManager.hpp"

#include <json.hpp>
#include <SFML\Graphics.hpp>
//#include <SFGUI\SFGUI.hpp>
//#include <SFGUI\Renderers.hpp>

#include <memory>
#include <iomanip> // setprecision
#include <sstream> // stringstream

#define _game pr::Game::instance()

namespace pr {
	class Game {
		private:
			const float DEFAULT_ZOOM = 0.5f;

			std::unique_ptr<SpriteSheets> m_sheets;
			std::unique_ptr<SceneManager> m_scenes;
			std::unique_ptr<sf::RenderWindow> m_window;
			std::unique_ptr<sf::View> m_view;

			//sfg::SFGUI m_sfgui;
			sf::Vector2f m_screenSize;

			Game();
		public:
			static Game& instance();

			//sfg::SFGUI& getGUI();

			std::unique_ptr<SpriteSheets>& getSheets();
			void initSheets(const std::string& filepath);

			const sf::Vector2f& getScreenSize();
			void setScreenSize(const sf::Vector2f& size);

			std::unique_ptr<SceneManager>& getSceneManager();
			void initSceneManager();

			std::unique_ptr<sf::RenderWindow>& getWindow();
			void initWindow();

			float getZoom();
			std::string getZoomString();
			void zoom(float zoom);
			void resetZoom();

			std::unique_ptr<sf::View>& getView();
			void moveView(const sf::Vector2f& rel);

			std::shared_ptr<sf::Image> loadImage(const std::string& path, const sf::Vector2u& size = { 0, 0 }, const sf::Color& color = sf::Color::White);
	};
}

#endif