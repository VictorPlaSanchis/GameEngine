#include "Scene.h"

Scene::Scene()
{
	objects = {};
}

Scene::~Scene()
{
}

void Scene::addObject(Object* object)
{
	objects.push_back(object);
}

void Scene::removeObject(Object* object)
{
	objects.remove(object);
}

void Scene::UpdateScene() 
{
	for (Object* object : objects) {
		object->Update();
	}
}
