#include "MyGameObject.h"
#include "../Log/Console.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../InputSystem/InputSystem.h"

#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "../GLM/glm/glm.hpp"
#include "../GLM/glm/gtc/matrix_transform.hpp"
#include "../GLM/glm/gtc/type_ptr.hpp"


namespace vge {

    MyGameObject::MyGameObject()
    {
        this->model = this->addComponent<Model>();

        std::vector<float> v = {
            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f
        };

        for (int i = 0; i < 36; i++) {
            v[(i * 3)] /= 2.0f;
            v[(i * 3) + 1] /= 2.0f;
  
            v[(i * 3) + 2] = 0.0f;
        }

        std::vector<float> subV;
        for (int i = 0; i < 12; i++) {
            subV.push_back(v[(i * 3) + 0]);
            subV.push_back(v[(i * 3) + 1]);
            subV.push_back(v[(i * 3) + 2]);
        }

        this->model->assignVertexs(
            subV
        );
        
        this->ShaderProgramLinked = GraphicsEngine::get()->CreateProgram({
            "./src/Object/Components/SpriteRendererVS.vert",
            "./src/Object/Components/SpriteRendererFS.frag"
        });
        unsigned int VAOassigned = GraphicsEngine::get()->pushModel(model, this->ShaderProgramLinked);
        GraphicsEngine::get()->LinkShader(VAOassigned, this->ShaderProgramLinked);
	}

	MyGameObject::~MyGameObject()
	{
	}

	void MyGameObject::Update()
	{
		//float reductor = 1.0f / 50.0f;
		//if (this->transform->getValues()[1] > -0.5f) this->transform->move(DOWN * reductor);
		//else if (InputSystem::get()->isKeyPressed(int('W'))) {
		//	Console::debug("JUMP!", Console::COLOR::CYAN, Console::SENDER::APPLICATION);
		//	this->transform->move(UP);
		//}
		//GraphicsEngine::get()->passUniform(this->sprite->getShaderProgramLinked(), {0.0f, 0.0f, 0.0f}/*this->transform->getValues()*/, "transform");

		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

		glm::mat4 view;
		view = glm::lookAt(cameraPos, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

		GraphicsEngine::get()->passUniform(this->ShaderProgramLinked, view[0], "modelViewMat0");
		GraphicsEngine::get()->passUniform(this->ShaderProgramLinked, view[1], "modelViewMat1");
		GraphicsEngine::get()->passUniform(this->ShaderProgramLinked, view[2], "modelViewMat2");
		GraphicsEngine::get()->passUniform(this->ShaderProgramLinked, view[3], "modelViewMat3");
		GraphicsEngine::get()->passUniform(this->ShaderProgramLinked, {1.0f, 0.0f, 0.0f}, "cameraPosition");

        GraphicsEngine::get()->passUniform(this->ShaderProgramLinked, { 0.0f, 0.0f, 0.0f }, "transform");


	}	

}


