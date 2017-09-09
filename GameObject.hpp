#ifndef PROJR_GAMEOBJECT_HPP
#define PROJR_GAMEOBJECT_HPP

namespace pr {
	class Game;
	class GameObject {
		public:
			Game* m_game;
			GameObject(Game& g) : m_game(&g) { }
	};
}

#endif