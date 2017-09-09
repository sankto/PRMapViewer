#include "MainScene.hpp"

namespace pr {
	MainScene::MainScene(const std::string& filepath) :
		IScene("MainScene"),
		m_map(std::make_shared<TiledMap>(&_game, 16, filepath)),
		m_dragging(false), m_hoveredTile({ -1, -1 }), m_isLinesDrawn(false), m_isCollisionsDrawn(true) {

		m_map->resetTilesPosition();

		m_font.loadFromFile("..\\..\\GameContent\\arial.ttf");

		m_tileLabel.setFont(m_font);
		m_tileLabel.setCharacterSize(18);
		m_tileLabel.setFillColor(sf::Color::White);
		m_tileLabel.setStyle(sf::Text::Bold);

		m_mouseTile.setOutlineColor(sf::Color::Red);
		m_mouseTile.setOutlineThickness(1);
		m_mouseTile.setFillColor(sf::Color::Transparent);
		m_mouseTile.setSize({
			static_cast<float>(m_map->getTileSize() - 1),
			static_cast<float>(m_map->getTileSize() - 1)
		});
		m_mouseTile.setPosition({ -1, -1 });

		initLines();
	}

	void MainScene::initLines() {
		m_lines.resize(m_map->getWidth() + m_map->getHeight() + 2);
		for (auto i = 0; i <= m_map->getWidth(); i++) {
			m_lines[i] = sf::RectangleShape{ {
					1, static_cast<float>(m_map->getHeight() * m_map->getTileSize()) + 1
				} };
			m_lines[i].setPosition({
				static_cast<float>(i * m_map->getTileSize()), 0
			});
		}
		for (std::size_t i = m_map->getWidth() + 1; i < m_lines.size(); i++) {
			m_lines[i] = sf::RectangleShape{ {
					static_cast<float>(m_map->getWidth() * m_map->getTileSize()), 1
				} };
			m_lines[i].setPosition({
				0, static_cast<float>((i - (m_map->getWidth() + 1)) * m_map->getTileSize())
			});
		}
	}

	const std::unique_ptr<std::string> MainScene::handleInputs(const sf::Event& event) {
		handleMovements(event);
		handleOptions(event);
		return nullptr;
	}

	void MainScene::updateMouseTile() {
		auto mouseCoords = _game.getWindow()->mapPixelToCoords(sf::Mouse::getPosition(*_game.getWindow()));
		if (mouseCoords.x < 0 || mouseCoords.y < 0 || mouseCoords.x >= m_map->getPixelWidth() || mouseCoords.y >= m_map->getPixelHeight()) {
			m_mouseTile.setPosition({ -1, -1 });
			m_hoveredTile = { -1, -1 };
		} else {
			m_hoveredTile = {
				static_cast<int>(std::floor(mouseCoords.x / m_map->getTileSize())),
				static_cast<int>(std::floor(mouseCoords.y / m_map->getTileSize()))
			};
			m_mouseTile.setPosition({
				static_cast<float>(m_hoveredTile.x * m_map->getTileSize()) + 1,
				static_cast<float>(m_hoveredTile.y * m_map->getTileSize()) + 1
			});

			std::stringstream ss;
			ss << "{ x: " << m_hoveredTile.x << ", y: " << m_hoveredTile.y << " }";
			m_tileLabel.setString(ss.str());
		}
	}

	void MainScene::handleMovements(const sf::Event& event) {
		switch (event.type) {
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Button::Left) {
					m_dragging = true;
					m_dragLoc = sf::Mouse::getPosition(*_game.getWindow());
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Button::Left) {
					m_dragging = false;
				}
				break;
			case sf::Event::MouseMoved:
				if (m_dragging) {
					_game.moveView(sf::Vector2f{
						static_cast<float>(-(event.mouseMove.x - m_dragLoc.x)),
						static_cast<float>(-(event.mouseMove.y - m_dragLoc.y))
					} *0.5f);
					m_dragLoc.x = event.mouseMove.x;
					m_dragLoc.y = event.mouseMove.y;
				}
				updateMouseTile();
				break;
			case sf::Event::MouseWheelScrolled:
				_game.zoom(event.mouseWheelScroll.delta > 0 ? 0.95f : 1.05f);
				updateMouseTile();
				break;
		}
	}

	void MainScene::handleOptions(const sf::Event& event) {
		switch (event.type) {
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Key::Space) {
					m_isLinesDrawn = !m_isLinesDrawn;
				}
				if (event.key.code == sf::Keyboard::Key::C) {
					m_isCollisionsDrawn = !m_isCollisionsDrawn;
				}
				if (event.key.code == sf::Keyboard::Key::R) {
					_game.resetZoom();
					updateMouseTile();
				}
				break;
		}
	}

	const std::unique_ptr<std::string> MainScene::update(const sf::Time& elapsed) {
		m_map->update(elapsed);
		return nullptr;
	}

	void MainScene::display() {
		_game.getWindow()->draw(m_map->getRenderSprite());

		if (m_isLinesDrawn) {
			for (auto& line : m_lines) {
				_game.getWindow()->draw(line);
			}
		}

		if (m_isCollisionsDrawn) {
			for (auto& coll : m_map->getCollisions()) {
				for (auto& side : coll) {
					if (side != nullptr)
						_game.getWindow()->draw(*side);
				}
			}
		}

		if (m_mouseTile.getPosition().x >= 0) {
			_game.getWindow()->draw(m_mouseTile);
		}

		_game.getWindow()->setView(_game.getWindow()->getDefaultView());
		if (m_mouseTile.getPosition().x >= 0) {
			_game.getWindow()->draw(m_tileLabel);
		}
		_game.getWindow()->setView(*_game.getView());
	}
}