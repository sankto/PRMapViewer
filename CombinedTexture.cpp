#include "CombinedTexture.hpp"

namespace pr {
	CombinedTexture::CombinedTexture()
		: m_maxFullSize(PREFERED_TEXTURE_SIZE), m_texture(nullptr) {
		
		if (m_maxFullSize > static_cast<int>(sf::Texture::getMaximumSize()))
			m_maxFullSize = static_cast<int>(sf::Texture::getMaximumSize());
	}
	CombinedTexture::~CombinedTexture() {
		delete m_texture;
		m_texture = nullptr;
	}

	void CombinedTexture::processImages(const ImagesHolder& images, ProcessingResources* res) {
		bool isRoot = false;
		if (res == nullptr) {
			isRoot = true;
			res = new ProcessingResources;
			// first get all images sorted by size, taller to shorter
			res->m_sorted = images.getSortedBySizeDesc();
			res->m_root = this;
		}

		sf::Image fullImage;
		fullImage.create(m_maxFullSize, m_maxFullSize);
		sf::IntRect availableRect = { 0, 0, m_maxFullSize, m_maxFullSize };

		// Now we create a first shelf, that will hold the tallest first
		std::vector<Shelf> shelves;
		shelves.push_back(Shelf());
		int totalShelvesHeight = 0; // we keep track of the total height to properly know the next shelf's Y position

		for (auto i = res->m_startingAtIndex; i < res->m_sorted->size(); i++) {
			// We try to insert the image into the shelf. if it work, we go to the next image.
			// If it doesn't, we create a new shelf, reset the availableRect with the new shelf's position in mind,
			// and we try again with the new shelf. If it fail, we keep track of the current image's index, to be returned.
			if (!shelves.back().insert((*res->m_sorted)[i], availableRect)) {
				totalShelvesHeight += shelves.back().height();
				availableRect = {
					0,
					totalShelvesHeight,
					m_maxFullSize,
					m_maxFullSize - totalShelvesHeight
				};
				shelves.push_back(Shelf());
				if (!shelves.back().insert((*res->m_sorted)[i], availableRect)) {
					res->m_startingAtIndex = i;
					res->m_root->m_allTextures.push_back(CombinedTexture());
					res->m_root->m_allTextures.back().processImages(images, res);
					break;
				}
			}
		}

		// Once we have calculated the images placement, we actually copy the images into the large texture.
		// We also link the Rect to the image's ID for the class's user.
		for (auto& shelf : shelves) {
			for (size_t i = 0; i < shelf.getPairs().size(); i++) {
				auto& rect = shelf.getRects()[i];
				auto& pair = shelf.getPairs()[i];
				res->m_root->m_mappedTextures[pair.first] = this;
				res->m_root->m_mappedRects[pair.first] = rect;
				fullImage.copy(*pair.second, rect.left, rect.top);
			}
		}

		// We finally create a texture out of it.
		m_texture = new sf::Texture;
		m_texture->loadFromImage(fullImage);
		
		if (isRoot) {
			delete res;

			// uncomment if you want a tangible result.
			//fullImage.saveToFile("c:/test/combined.png");
		}
	}

	sf::Texture* CombinedTexture::getTexture(const std::string& index) {
		return m_mappedTextures[index]->m_texture;
	}

	sf::Texture* CombinedTexture::getTexture() {
		return m_texture;
	}

	sf::IntRect* CombinedTexture::getRect(const std::string& index) {
		return &m_mappedRects[index];
	}
}