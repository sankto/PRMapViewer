#ifndef PROJR_COMBINEDTEXTURE_HPP
#define PROJR_COMBINEDTEXTURE_HPP

#include <SFML\Graphics.hpp>
#include "ImagesHolder.hpp"
#include <memory>

namespace pr {
	class CombinedTexture {
		private:
			class Shelf {
				private:
					std::vector<pair_t> m_items;
					std::vector<sf::IntRect> m_rects;

					bool canFit(const pair_t& pair, const sf::IntRect& rect) const;
				public:
					bool insert(pair_t& texturePair, sf::IntRect& availableRect);
					int height() const;
					const std::vector<pair_t>& getPairs() const;
					const std::vector<sf::IntRect>& getRects() const;
			};

			class ProcessingResources {
				public:
					size_t m_startingAtIndex;
					std::vector<pr::pair_t>* m_sorted;
					CombinedTexture* m_root;
				
					ProcessingResources();
					~ProcessingResources();
			};

			const int PREFERED_TEXTURE_SIZE = 4096;

			int m_maxFullSize;
			sf::Texture* m_texture;
			
			std::vector<CombinedTexture> m_allTextures;
			std::map<std::string, CombinedTexture*> m_mappedTextures;
			std::map<std::string, sf::IntRect> m_mappedRects;
		public:
			CombinedTexture();
			~CombinedTexture();
			
			void processImages(const ImagesHolder& textures, ProcessingResources* res = nullptr);
			
			sf::Texture* getTexture(const std::string& index);
			sf::Texture* getTexture();
			sf::IntRect* getRect(const std::string& index);
	};
}

#endif