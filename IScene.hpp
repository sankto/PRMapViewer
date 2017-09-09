#ifndef PROJR_ISCENE_HPP
#define PROJR_ISCENE_HPP

#include <SFML\Graphics.hpp>
//#include <SFGUI\Widgets.hpp>
#include <memory>
#include <string>

namespace pr {
	class IScene {
		private:
			std::string m_name;
			//sfg::Desktop m_desktop;
		public:
			IScene(const std::string& name) : m_name(name) { }
			virtual const std::unique_ptr<std::string> handleInputs(const sf::Event& event) = 0;
			virtual const std::unique_ptr<std::string> update(const sf::Time& elapsed) = 0;
			virtual void display() = 0;

			const std::string& getName() { return m_name; }
			//sfg::Desktop& getDesktop() { return m_desktop; }
	};

	class EmptyScene : public IScene {
		public :
			EmptyScene() : IScene("") {}
			const std::unique_ptr<std::string> handleInputs(const sf::Event&) { return nullptr; }
			const std::unique_ptr<std::string> update(const sf::Time&) { return nullptr; }
			void display() {}
	};
}

#endif