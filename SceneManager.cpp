#include "SceneManager.hpp"

namespace pr {
	std::shared_ptr<IScene> SceneManager::s_emptyScene = std::make_shared<EmptyScene>();

	SceneManager::SceneManager() {

	}

	void SceneManager::push(const std::shared_ptr<IScene>& scene) {
		if (scene != nullptr) {
			m_scenes.push(scene);
		}
	}

	void SceneManager::pop() {
		if (!m_scenes.empty()) {
			m_scenes.pop();
		}
	}

	std::shared_ptr<IScene>& SceneManager::peek() {
		if (m_scenes.empty()) {
			return s_emptyScene;
		} else {
			return m_scenes.top();
		}
	}

	std::stack<std::shared_ptr<IScene>>::size_type SceneManager::size() {
		return m_scenes.size();
	}

	bool SceneManager::empty() {
		return m_scenes.empty();
	}
}