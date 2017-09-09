#include "Game.hpp"
#include "Scenes.hpp"

#include <exception>

int main(int argc, char* argv[]) {
	try {
		if (argc != 2)
			return -1;
		std::string mapPath = argv[1];

		_game.setScreenSize({ 800.f, 600.f });
		_game.initSheets("..\\..\\GameContent\\2d_mapping.json");
		_game.initSceneManager();
		_game.initWindow();

		_game.getSceneManager()->push(std::make_shared<pr::MainScene>(mapPath));

		sf::Clock clock;
		while (_game.getWindow()->isOpen()) {
			sf::Time elapsed = clock.restart();
			sf::Event event;
			while (_game.getWindow()->pollEvent(event)) {
				_game.getSceneManager()->peek()->handleInputs(event);
				if (event.type == sf::Event::Closed)
					_game.getWindow()->close();
			}
			_game.getSceneManager()->peek()->update(elapsed);
			_game.getWindow()->clear();
			_game.getSceneManager()->peek()->display();
			_game.getWindow()->display();
		}
	} catch (...) {
		
	}

	return 0;
}
