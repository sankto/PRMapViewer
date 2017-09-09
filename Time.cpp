#include "Time.hpp"

namespace pr {
	Timer::Timer(const sf::Time& interval, std::function<void(const Timer&)> callback, bool loop)
		: m_interval(interval), m_callback(callback), m_isLooping(loop), m_isFinished(false), m_isPaused(false) {
		
	}

	const sf::Time& Timer::getInterval() {
		return m_interval;
	}

	const sf::Time& Timer::getElapsed() {
		return m_elapsed;
	}

	float Timer::getPercent() {
		return (m_elapsed / m_interval) * 100;
	}

	void Timer::add(const sf::Time& time) {
		if (m_isFinished || m_isPaused)
			return;
		m_elapsed += time;
		while (m_elapsed >= m_interval) {
			m_elapsed -= m_interval;
			if (m_callback != nullptr) {
				m_callback(*this);
			}
			if (!m_isLooping) {
				m_isFinished = true;
				m_elapsed = m_interval;
				break;
			}
		}
	}

	bool Timer::isFinished() {
		return m_isFinished;
	}

	bool Timer::isLooping() {
		return m_isLooping;
	}

	bool Timer::isPaused() {
		return m_isPaused;
	}

	void Timer::setLooping(bool loop) {
		m_isLooping = loop;
	}

	void Timer::pause() {
		m_isPaused = true;
	}

	void Timer::resume() {
		m_isPaused = false;
	}

	void Timer::setPaused(bool pause) {
		m_isPaused = pause;
	}

	void Timer::reset() {
		m_isFinished = false;
		m_elapsed = sf::Time::Zero;
	}
}