#pragma once
#include <vector>
#include "./Scene.h"

namespace vge {


	class SceneManagement
	{

	private:

		std::vector<Scene*> scenes;
		Scene* currentScene;

	public:

		SceneManagement();
		~SceneManagement();

		static SceneManagement* get();

		void Ini();
		Scene* createScene();
		void removeScene(Scene* scene);
		void setCurrentScene(int index);
		void setCurrentScene(Scene* scene);
		Scene* getCurrentScene();

	};

#define SceneManagementVGE (*(vge::SceneManagement::get()))

}
