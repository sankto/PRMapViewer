#include "AlternatingSprite.hpp"

namespace pr {
	AlternatingSprite::AlternatingSprite(sf::Sprite& first, sf::Sprite& second, sf::Time interval) :
		m_first(first), m_second(second), m_current(&first),
		m_timer(interval, [&](const Timer& t) { timerCallback(t); }) {

	}

	void AlternatingSprite::timerCallback(const Timer& timer) {
		if (m_current == &m_second)
			m_current = &m_first;
		else m_current = &m_second;
	}

	void AlternatingSprite::update(const sf::Time& elapsed) {
		m_timer.add(elapsed);
	}

	const Timer& AlternatingSprite::getInterval() {
		return m_timer.getInterval();
	}

	const sf::Sprite& AlternatingSprite::getCurrent() {
		return *m_current;
	}

	const sf::Sprite& AlternatingSprite::getFirst() {
		return m_first;
	}
	
	const sf::Sprite& AlternatingSprite::getSecond() {
		return m_second;
	}
}