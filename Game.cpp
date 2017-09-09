#include "Game.hpp"

namespace pr {
	Game::Game() :
		m_sheets(nullptr), m_scenes(nullptr), m_view(nullptr),
		m_screenSize({ 800, 600 }) {

		//sfg::Renderer::Set(sfg::VertexArrayRenderer::Create());
	}

	Game& Game::instance() {
		static Game inst;
		return inst;
	}

	/*sfg::SFGUI& Game::getGUI() {
		return m_sfgui;
	}*/

	std::unique_ptr<SpriteSheets>& Game::getSheets() {
		return m_sheets;
	}

	void Game::initSheets(const std::string& filepath) {
		m_sheets = std::make_unique<SpriteSheets>(filepath);
	}

	const sf::Vector2f& Game::getScreenSize() {
		return m_screenSize;
	}

	void Game::setScreenSize(const sf::Vector2f& size) {
		m_screenSize = size;
	}

	std::unique_ptr<SceneManager>& Game::getSceneManager() {
		return m_scenes;
	}

	void Game::initSceneManager() {
		m_scenes = std::make_unique<SceneManager>();
	}

	std::unique_ptr<sf::RenderWindow>& Game::getWindow() {
		return m_window;
	}

	void Game::initWindow() {
		m_view = std::make_unique<sf::View>(
			sf::Vector2f { m_screenSize.x / 4, m_screenSize.y / 4 },
			sf::Vector2f { m_screenSize.x, m_screenSize.y }
		);
		m_view->zoom(DEFAULT_ZOOM);
		
		m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode{
			static_cast<unsigned int>(m_screenSize.x),
			static_cast<unsigned int>(m_screenSize.y)
		}, "Project Rogue - Map Viewer");
		m_window->setVerticalSyncEnabled(true);
		m_window->setView(*m_view);
		m_window->resetGLStates();
	}

	float Game::getZoom() {
		if (m_view == nullptr)
			return DEFAULT_ZOOM;
		else {
			return static_cast<float>(m_screenSize.x / 4) / m_view->getSize().x;
		}
	}

	std::string Game::getZoomString() {
		std::stringstream stream;
		stream << std::fixed << std::setprecision(2) << getZoom();
		return stream.str();
	}

	void Game::zoom(float zoom) {
		m_view->zoom(zoom);
		m_window->setView(*m_view);
	}

	void Game::resetZoom() {
		m_view = std::make_unique<sf::View>(
			sf::Vector2f{ m_screenSize.x / 4, m_screenSize.y / 4 },
			sf::Vector2f{ m_screenSize.x, m_screenSize.y }
		);
		m_view->zoom(DEFAULT_ZOOM);
		m_window->setView(*m_view);
	}

	std::unique_ptr<sf::View>& Game::getView() {
		return m_view;
	}

	void Game::moveView(const sf::Vector2f& rel) {
		m_view->move(rel);
		m_window->setView(*m_view);
	}

	std::shared_ptr<sf::Image> Game::loadImage(const std::string& path, const sf::Vector2u& size, const sf::Color& color) {
		auto img = std::make_shared<sf::Image>();
		if (!img->loadFromFile(path)) {
			return nullptr;
		}
		bool shouldResize = (size.x != 0 && size.y != 0) && (size.x != img->getSize().x && size.y != img->getSize().y);
		bool shouldRecolor = color != sf::Color::White;
		if (shouldResize || shouldRecolor) {
			sf::Texture imgTexture;
			imgTexture.loadFromImage(*img);
			sf::Sprite sprite;
			sprite.setTexture(imgTexture);
			sf::RenderTexture render;
			if (shouldResize) {
				sprite.setScale({
					static_cast<float>(size.x) / static_cast<float>(img->getSize().x),
					static_cast<float>(size.y) / static_cast<float>(img->getSize().y)
				});
			}
			if (!render.create(img->getSize().x * sprite.getScale().x, img->getSize().y * sprite.getScale().y)) {
				return nullptr;
			}
			render.setSmooth(true);
			if (shouldRecolor) {
				sprite.setColor(color);
			}
			render.clear(sf::Color::Transparent);
			render.draw(sprite);
			render.display();

			return std::make_shared<sf::Image>(render.getTexture().copyToImage());
		} else {
			return img;
		}
	}
}