#include "SceneSystem.h"
#include <iostream>
#define DEBUG(x) std::cout << x << std::endl;

SceneSystem* SceneSystem::get()
{
	static SceneSystem sceneSystem;
	return &sceneSystem;
}

SceneSystem::SceneSystem()
{
	SceneSystem::currentScene = nullptr;
}

SceneSystem::~SceneSystem()
{
}

void SceneSystem::addScene()
{
	Scene newScene = Scene();
	scenes.push_back(&newScene);
}

void SceneSystem::removeScene(Scene* scene)
{
	std::vector<Scene*>::iterator it = scenes.begin();
	while (it != scenes.end()) {
		if (*it == scene) {
			scenes.erase(it);
			return;
		}
	}
}

void SceneSystem::setCurrentScene(int index)
{
	this->currentScene = scenes[index];
}
