#ifndef PROJR_ALTERNATINGSPRITE_HPP
#define PROJR_ALTERNATINGSPRITE_HPP

#include "SFML\Graphics.hpp"
#include "Time.hpp"
#include <functional>

namespace pr {
	class AlternatingSprite {
		private:
			Timer m_timer;
			sf::Sprite& m_first, m_second;
			sf::Sprite* m_current;

			void timerCallback(const Timer& timer);
		public:
			AlternatingSprite(sf::Sprite& first, sf::Sprite& second, sf::Time interval);

			void update(const sf::Time& elapsed);
			const Timer& getInterval();
			const sf::Sprite& getCurrent();
			const sf::Sprite& getFirst();
			const sf::Sprite& getSecond();
	};
}

#endif