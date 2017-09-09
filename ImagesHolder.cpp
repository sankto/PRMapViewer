#include "ImagesHolder.hpp"

namespace pr {
	ImagesHolder::ImagesHolder() {

	}

	ImagesHolder::~ImagesHolder() {
		for (auto& pair : m_images) {
			delete pair.second;
			pair.second = nullptr;
		}
	}

	sf::Image* ImagesHolder::operator[](const std::string& index) {
		return m_images[index];
	}

	void ImagesHolder::loadAndAdd(const std::string& id, const std::string& filepath) {
		auto texture = new sf::Image;
		if (texture->loadFromFile(filepath)) {
			m_images[id] = texture;
		} else {
			m_images[id] = nullptr; // error'd
		}
	}

	std::vector<pair_t>* ImagesHolder::getSortedBySizeDesc() const {
		auto sortable = new std::vector<pair_t>;
		for (auto& pair : m_images)
			sortable->push_back({ pair.first, pair.second });
		std::sort(sortable->begin(), sortable->end(), [](auto &left, auto &right) {
			return left.second->getSize().y > right.second->getSize().y;
		});
		return sortable;
	}
}