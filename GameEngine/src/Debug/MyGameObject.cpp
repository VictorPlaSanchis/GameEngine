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
 
        Model* cube = ObjLoader::loadObj("./src/cube.obj");

        this->model = this->addComponent<Model>();
        this->model = cube;

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

        this->model->Behaviour();

        if (InputSystemVGE.isKeyPressed(int('1'))) {
            ConsoleLogS("Set scene number 1", AUXILIAR);
            SceneManagementVGE.setCurrentScene(0);
        }
        if (InputSystemVGE.isKeyPressed(int('2'))) {
            ConsoleLogS("Set scene number 2", AUXILIAR);
            SceneManagementVGE.setCurrentScene(1);
        }

		float reductor = 1.0f / 300.0f;
		if (InputSystemVGE.isKeyDown(int('W'))) {
            altura += -1.0f * reductor;
		}
        if (InputSystemVGE.isKeyDown(int('S'))) {
            altura += 1.0f * reductor;
        }
        if (InputSystemVGE.isKeyDown(int('A'))) {
            desplas += 1.0f * reductor;
        }
        if (InputSystemVGE.isKeyDown(int('D'))) {
            desplas += -1.0f * reductor;
        }

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(
            this->transform->getValues()[0],
            this->transform->getValues()[1],
            this->transform->getValues()[2]
        ));
        float actualTime = static_cast<float>(glfwGetTime());
        model = glm::rotate(model, actualTime, glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 view = glm::lookAt(glm::vec3(desplas, altura, 3.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        float FOV = visionAngle * (PI / 180.0f);
        glm::mat4 projectionMatrix = glm::perspective(FOV, (float)1280 / (float)720, 1.0f, 10.0f);

        GraphicsEngineVGE.passUniformMat4(this->ShaderProgramLinked, model, "model");
        GraphicsEngineVGE.passUniformMat4(this->ShaderProgramLinked, view, "view");
        GraphicsEngineVGE.passUniformMat4(this->ShaderProgramLinked, projectionMatrix, "projection");


	}	

}


