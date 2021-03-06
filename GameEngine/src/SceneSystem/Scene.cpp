#include "Scene.h"

namespace vge {

	Scene::Scene()
	{
		objects = {};
		sceneCamera = new Camera();
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
			object->UpdateComponents();
			object->Update();
		}
	}

}