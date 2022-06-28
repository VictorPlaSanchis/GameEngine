#pragma once
#include <GLFW/glfw3.h>
#include <list>
#include "../Object/Object.h"
#include "../Object/Camera.h"

namespace vge {

	class Scene
	{

	private:

		std::list<Object*> objects;
		Camera* sceneCamera;

	public:

		Scene();
		~Scene();

		void addObject(Object* object);
		void removeObject(Object* object);
		void UpdateScene();
		Camera* getCameraScene() { return this->sceneCamera; }

	};

}
