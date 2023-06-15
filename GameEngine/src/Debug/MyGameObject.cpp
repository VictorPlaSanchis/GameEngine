#include "MyGameObject.h"
#include <GL/glew.h>
#include "../GraphicsEngine/GraphicsEngine.h"

#include "GLFW/glfw3.h"
#include "../GLM/glm/glm.hpp"
#include "../GLM/glm/gtc/matrix_transform.hpp"
#include "../GLM/glm/gtc/type_ptr.hpp"
#include "../InputSystem/InputSystem.h"
#include "../SceneSystem/SceneManagement.h"
#include "../GraphicsEngine/ObjLoader.h"

#ifndef PI
#define PI 3.141592f
#endif

namespace vge {

    MyGameObject::MyGameObject()
    {


	}

	MyGameObject::~MyGameObject()
	{
	}

	void MyGameObject::Update()
	{

	}	

}


