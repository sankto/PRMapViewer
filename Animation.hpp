#ifndef PROJR_ANIMATION_HPP
#define PROJR_ANIMATION_HPP

#include "SFML\Graphics.hpp"
#include <vector>
#include <functional>

#include "Time.hpp"

namespace pr {
	class Animation {
		private:
			std::vector<std::reference_wrapper<sf::Sprite>> m_frames;
			Timer m_timer;
			int m_currentIndex;
			std::function<void()> m_onTimerTriggered;

			void timerCallback(const Timer& timer);
		public:
			static const int SWITCH_INTERVAL = 235;

			Animation(const sf::Time& interval, std::function<void()> onTimerTriggered, std::initializer_list<std::reference_wrapper<sf::Sprite>> sprites);
			Animation(const sf::Time& interval, std::initializer_list<std::reference_wrapper<sf::Sprite>> sprites);
			Animation(std::function<void()> onTimerTriggered, std::initializer_list<std::reference_wrapper<sf::Sprite>> sprites);
			Animation(std::initializer_list<std::reference_wrapper<sf::Sprite>> sprites);
			

			void update(const sf::Time& elapsed);
			sf::Sprite& getCurrent();
			int getCurrentIndex();
			sf::Sprite& operator[](const int& index);
	};
}

#endif
