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

#define PI 3.141592f

namespace vge {

    MyGameObject::MyGameObject()
    {
 
        Model* cube = ObjLoader::loadObj("./src/knight.obj");

        this->model = this->addComponent<Model>();
        this->model->load(cube);
        this->model->assignTexture("./imgs/knight.png");

        this->ShaderProgramLinked = GraphicsEngineVGE.CreateProgram({
            "./src/Object/Components/SpriteRendererVS.vert",
            "./src/Object/Components/SpriteRendererFS.frag"
        });

        unsigned int VAOassigned = GraphicsEngineVGE.pushModel(model, this->ShaderProgramLinked);
        GraphicsEngineVGE.LinkShader(VAOassigned, this->ShaderProgramLinked);

	}

	MyGameObject::~MyGameObject()
	{
	}

	void MyGameObject::Update()
	{

        if (InputSystemVGE.isKeyPressed(int('1'))) {
            SceneManagementVGE.setCurrentScene(0);
        }
        if (InputSystemVGE.isKeyPressed(int('2'))) {
            SceneManagementVGE.setCurrentScene(1);
        }

        if (InputSystemVGE.isKeyDown(int('D'))) this->transform->move({ 1.0f * 0.001f, 0.0f, 0.0f});
        if (InputSystemVGE.isKeyDown(int('A'))) this->transform->move({-1.0f * 0.001f, 0.0f, 0.0f });
        if (InputSystemVGE.isKeyDown(int('W'))) this->transform->move({ 0.0f, 1.0f * 0.001f, 0.0f });
        if (InputSystemVGE.isKeyDown(int('S'))) this->transform->move({ 0.0f, -1.0f * 0.001f, 0.0f });
        if (InputSystemVGE.isKeyDown(int('Q'))) this->transform->move({ 0.0f, 0.0f, 1.0f * 0.001f});
        if (InputSystemVGE.isKeyDown(int('E'))) this->transform->move({ 0.0f, 0.0f, -1.0f * 0.001f});

	}	

}


