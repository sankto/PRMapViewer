#ifndef PROJR_IMAGESHOLDER_HPP
#define PROJR_IMAGESHOLDER_HPP

#include <SFML\Graphics.hpp>
#include <string>
#include <map>

namespace pr {
	using pair_t = std::pair<std::string, sf::Image*>;

	class ImagesHolder {
		private:
			std::map<std::string, sf::Image*> m_images;
		public:
			ImagesHolder();
			~ImagesHolder();

			sf::Image* operator[](const std::string& index);

			void loadAndAdd(const std::string& id, const std::string& filepath);
			std::vector<pair_t>* getSortedBySizeDesc() const;
	};
}

#endif