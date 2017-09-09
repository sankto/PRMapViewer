#ifndef PROJR_TIME_HPP
#define PROJR_TIME_HPP

#include <SFML/System.hpp>
#include <functional>

namespace pr {
	class Timer {
		private:
			bool m_isFinished;
			bool m_isLooping;
			bool m_isPaused;
			sf::Time m_interval;
			sf::Time m_elapsed;
			std::function<void(const Timer&)> m_callback;
		public:
			Timer(const sf::Time& interval, std::function<void(const Timer&)> callback = nullptr, bool loop = true);

			const sf::Time& getInterval();
			const sf::Time& getElapsed();
			float getPercent();
			void add(const sf::Time& time);
			bool isFinished();
			bool isLooping();
			bool isPaused();
			void setLooping(bool loop = true);
			void pause();
			void resume();
			void setPaused(bool pause = true);
			void reset();
	};
}

#endif
