#include "MyGameObject.h"
#include <GL/glew.h>
#include "../GraphicsEngine/GraphicsEngine.h"

#include "GLFW/glfw3.h"
#include "../GLM/glm/glm.hpp"
#include "../GLM/glm/gtc/matrix_transform.hpp"
#include "../GLM/glm/gtc/type_ptr.hpp"
#include "../InputSystem/InputSystem.h"
#include "../SceneSystem/SceneManagement.h"

#define PI 3.141592f

namespace vge {

    MyGameObject::MyGameObject()
    {
        this->model = this->addComponent<Model>();
        this->model->assignVertexs({
            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f
        });
        this->model->assignVertexsColor({
            0.583f,  0.771f,  0.014f,
            0.609f,  0.115f,  0.436f,
            0.327f,  0.483f,  0.844f,
            0.822f,  0.569f,  0.201f,
            0.435f,  0.602f,  0.223f,
            0.310f,  0.747f,  0.185f,
            0.597f,  0.770f,  0.761f,
            0.559f,  0.436f,  0.730f,
            0.359f,  0.583f,  0.152f,
            0.483f,  0.596f,  0.789f,
            0.559f,  0.861f,  0.639f,
            0.195f,  0.548f,  0.859f,
            0.014f,  0.184f,  0.576f,
            0.771f,  0.328f,  0.970f,
            0.406f,  0.615f,  0.116f,
            0.676f,  0.977f,  0.133f,
            0.971f,  0.572f,  0.833f,
            0.140f,  0.616f,  0.489f,
            0.997f,  0.513f,  0.064f,
            0.945f,  0.719f,  0.592f,
            0.543f,  0.021f,  0.978f,
            0.279f,  0.317f,  0.505f,
            0.167f,  0.620f,  0.077f,
            0.347f,  0.857f,  0.137f,
            0.055f,  0.953f,  0.042f,
            0.714f,  0.505f,  0.345f,
            0.783f,  0.290f,  0.734f,
            0.722f,  0.645f,  0.174f,
            0.302f,  0.455f,  0.848f,
            0.225f,  0.587f,  0.040f,
            0.517f,  0.713f,  0.338f,
            0.053f,  0.959f,  0.120f,
            0.393f,  0.621f,  0.362f,
            0.673f,  0.211f,  0.457f,
            0.820f,  0.883f,  0.371f,
            0.982f,  0.099f,  0.879f
        });

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
        glm::mat4 projectionMatrix = glm::perspective(FOV, (float)1280 / (float)720, 0.0f, 100.0f);

        GraphicsEngineVGE.passUniformMat4(this->ShaderProgramLinked, model, "model");
        GraphicsEngineVGE.passUniformMat4(this->ShaderProgramLinked, view, "view");
        GraphicsEngineVGE.passUniformMat4(this->ShaderProgramLinked, projectionMatrix, "projection");


	}	

}


