#pragma once
#include <GLFW/glfw3.h>
#include <list>
#include "../Object/Object.h"

class Scene
{

private:

	std::list<Object*> objects;

public:

	Scene();
	~Scene();

	void addObject(Object* object);
	void removeObject(Object* object);
	void UpdateScene();

};

