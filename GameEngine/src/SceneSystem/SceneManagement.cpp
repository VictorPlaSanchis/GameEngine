#include "SceneManagement.h"
#include "../Log/Log.h"

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
	DEBUG_AUX_INFO("Current scene is now index 0.");
	currentScene = scenes[index];
}

Scene* SceneManagement::getCurrentScene()
{
	return currentScene;
}
