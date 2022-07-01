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

	void SceneManagement::Ini()
	{
		this->scenes = std::vector<Scene*>(0);
	}

	Scene* SceneManagement::createScene()
	{
		Scene* newScene = new Scene();
		scenes.push_back(newScene);
		if (currentScene == nullptr) setCurrentScene(0);
		return newScene;
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

	void SceneManagement::setCurrentScene(Scene* sceneToSet)
	{
		for (Scene* scene : scenes) {
			if (scene == sceneToSet) {
				currentScene = scene;
				return;
			}
		}
	}

	Scene* SceneManagement::getCurrentScene()
	{
		return currentScene;
	}


}
