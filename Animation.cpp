#include "Animation.hpp"

namespace pr {
	Animation::Animation(const sf::Time& interval, std::function<void()> onTimerTriggered, std::initializer_list<std::reference_wrapper<sf::Sprite>> sprites) :
		m_currentIndex(0),
		m_onTimerTriggered(onTimerTriggered),
		m_timer(interval, [&](const Timer& timer) { timerCallback(timer); }) {
		
		for (const auto& sprite : sprites) {
			m_frames.push_back(sprite);
		}
	}
	Animation::Animation(const sf::Time& interval, std::initializer_list<std::reference_wrapper<sf::Sprite>> sprites) :
		Animation(interval, nullptr, sprites) {}
	Animation::Animation(std::function<void()> onTimerTriggered, std::initializer_list<std::reference_wrapper<sf::Sprite>> sprites) :
		Animation(sf::milliseconds(SWITCH_INTERVAL), onTimerTriggered, sprites) {}
	Animation::Animation(std::initializer_list<std::reference_wrapper<sf::Sprite>> sprites) :
		Animation(sf::milliseconds(SWITCH_INTERVAL), nullptr, sprites) {}

	void Animation::timerCallback(const Timer& timer) {
		m_currentIndex = ++m_currentIndex % m_frames.size();
		if (m_onTimerTriggered != nullptr) {
			m_onTimerTriggered();
		}
	}

	void Animation::update(const sf::Time& elapsed) {
		m_timer.add(elapsed);
	}

	sf::Sprite& Animation::getCurrent() {
		return m_frames[m_currentIndex];
	}

	int Animation::getCurrentIndex() {
		return m_currentIndex;
	}

	sf::Sprite& Animation::operator[](const int& index) {
		return m_frames[index];
	}
}