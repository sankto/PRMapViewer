#ifndef PROJR_SCENEMANAGER_HPP
#define PROJR_SCENEMANAGER_HPP

#include "IScene.hpp"
#include <memory>
#include <stack>

namespace pr {
	class SceneManager {
		private:
			static std::shared_ptr<IScene> s_emptyScene;

			std::stack<std::shared_ptr<IScene>> m_scenes;
		public:
			SceneManager();

			void push(const std::shared_ptr<IScene>& scene);
			void pop();
			std::shared_ptr<IScene>& peek();
			std::stack<std::shared_ptr<IScene>>::size_type size();
			bool empty();
	};
}

#endif
