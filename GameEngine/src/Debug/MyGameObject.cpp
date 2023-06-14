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
 
        Model* cube = ObjLoader::loadObj("./src/cube.obj");

        this->model = this->addComponent<Model>();
        this->model->load(cube);
        this->model->assignTexture("./imgs/knight.png");

        this->ShaderProgramLinked = GraphicsEngineVGE.CreateProgram(
            "spriteRendererProgram", 
            {
                "./src/GraphicsEngine/Shaders/SpriteRendererVS.vert",
                "./src/GraphicsEngine/Shaders/SpriteRendererFS.frag"
            }
        );

        unsigned int VAOassigned = GraphicsEngineVGE.pushModel(model, this->ShaderProgramLinked);
        GraphicsEngineVGE.LinkShader(VAOassigned, "spriteRendererProgram");

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

        if (InputSystemVGE.isKeyDown(int('I'))) this->transform->rotate( 1.0f * 0.001f, { 0.0f, 1.0f, 0.0f});
        if (InputSystemVGE.isKeyDown(int('J'))) this->transform->rotate( 1.0f * 0.001f, { 0.0f, 0.0f, 1.0f });
        if (InputSystemVGE.isKeyDown(int('K'))) this->transform->rotate(-1.0f * 0.001f, { 0.0f, 1.0f, 0.0f });
        if (InputSystemVGE.isKeyDown(int('L'))) this->transform->rotate(-1.0f * 0.001f, { 0.0f, 0.0f, 1.0f });

	}	

}


