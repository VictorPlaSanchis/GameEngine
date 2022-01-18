#include "SceneManagement.h"
#include <iostream>
#define DEBUG(x) std::cout << x << std::endl;

SceneManagement* SceneManagement::get()
{
	static SceneManagement sceneSystem;
	return &sceneSystem;
}

SceneManagement::SceneManagement()
{
	SceneManagement::currentScene = nullptr;
}

SceneManagement::~SceneManagement()
{
}

void SceneManagement::addScene()
{
	Scene newScene = Scene();
	scenes.push_back(&newScene);
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
	this->currentScene = scenes[index];
}

Scene* SceneManagement::getCurrentScene()
{
	return currentScene;
}
