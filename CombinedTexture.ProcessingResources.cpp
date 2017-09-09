#include "CombinedTexture.hpp"

namespace pr {
	CombinedTexture::ProcessingResources::ProcessingResources() :
		m_startingAtIndex(0), m_sorted(nullptr), m_root(nullptr) {
	
	}

	CombinedTexture::ProcessingResources::~ProcessingResources() {
		if (m_sorted != nullptr) {
			delete m_sorted;
			m_sorted = nullptr;
		}
	}
}