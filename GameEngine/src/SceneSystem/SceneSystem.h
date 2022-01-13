#pragma once
#include <vector>
#include "Scene.h"

class SceneSystem
{

private:

	std::vector<Scene*> scenes;

public:

	Scene* currentScene;

	static SceneSystem* get();
	
	SceneSystem();
	~SceneSystem();

	void addScene();
	void removeScene(Scene* scene);
	void setCurrentScene(int index);

};

