#ifdef _WIN32
#include <Windows.h>	// avoid compilation redefinition of APIENTRY
#endif
#include "SceneManagement.h"

namespace vge {


	SceneManagement* SceneManagement::get()
	{
		static SceneManagement sceneSystem;
		return &sceneSystem;
	}

	SceneManagement::SceneManagement()
	{
		currentScene = nullptr;
		scenes = {};
	}

	SceneManagement::~SceneManagement()
	{
	}

	void SceneManagement::addScene()
	{
		scenes.push_back(new Scene());
		if (currentScene == nullptr) setCurrentScene(0);
	}

	void SceneManagement::removeScene(Scene* scene)
	{
		std::vector<Scene*>::iterator it = scenes.begin();
		while (it != scenes.end()) {
			if (*it == scene) {
				scenes.erase(it);
				return;
			}
		}
	}

	void SceneManagement::setCurrentScene(int index)
	{
		currentScene = scenes[index];
	}

	Scene* SceneManagement::getCurrentScene()
	{
		return currentScene;
	}


}
