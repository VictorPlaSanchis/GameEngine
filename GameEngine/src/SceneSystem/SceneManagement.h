#pragma once
#include <vector>
#include "Scene.h"

namespace vge {


	class SceneManagement
	{

	private:

		std::vector<Scene*> scenes;
		Scene* currentScene;

	public:

		static SceneManagement* get();

		SceneManagement();
		~SceneManagement();

		void addScene();
		void removeScene(Scene* scene);
		void setCurrentScene(int index);
		Scene* getCurrentScene();

	};


}
