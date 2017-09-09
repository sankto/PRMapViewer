#include "CombinedTexture.hpp"

namespace pr {
	bool CombinedTexture::Shelf::canFit(const pair_t& pair, const sf::IntRect& rect) const {
		return (static_cast<int>(pair.second->getSize().x) <= rect.width &&
				static_cast<int>(pair.second->getSize().y) <= rect.height);
	}

	bool CombinedTexture::Shelf::insert(pair_t& texturePair, sf::IntRect& availableRect) {
		if (!canFit(texturePair, availableRect)) {
			return false;
		} else {
			if (m_items.empty()) {
				availableRect.height = texturePair.second->getSize().y;
			}
			m_items.push_back(texturePair);
			m_rects.push_back(sf::IntRect{
				availableRect.left, availableRect.top,
				static_cast<int>(texturePair.second->getSize().x),
				static_cast<int>(texturePair.second->getSize().y)
			});
			availableRect.left += static_cast<int>(texturePair.second->getSize().x);
			availableRect.width -= static_cast<int>(texturePair.second->getSize().x);
			return true;
		}
	}

	int CombinedTexture::Shelf::height() const {
		return m_rects[0].height;
	}

	const std::vector<pair_t>& CombinedTexture::Shelf::getPairs() const {
		return m_items;
	}

	const std::vector<sf::IntRect>& CombinedTexture::Shelf::getRects() const {
		return m_rects;
	}
}