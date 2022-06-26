#include "MyGameObject.h"
#include "../Log/Console.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../GraphicsEngine/SpriteRenderer.h"
#include "../GraphicsEngine/Model.h"

namespace vge {

	MyGameObject::MyGameObject()
	{
		this->components = {};
		this->childs = {};
		this->transform = new Transform();

		std::vector<float> vertexs = {
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f
		};

		Model* newModel = this->addComponent<Model>(vertexs);
		newModel->assignVertexsTexCoord({
			0.0f, 0.0f,
			0.0f, -1.0f,
			1.0f, 0.0f,
			0.0f, -1.0f,
			1.0f, -1.0f,
			1.0f, 0.0f
		});
		newModel->assignTexture("./imgs/tumblr.png");
		GraphicsEngine::get()->pushModel(newModel);

		//unsigned int programID = GraphicsEngine::get()->CreateProgram({ "./src/GraphicsEngine/SpriteRendererVS.vert", "./src/GraphicsEngine/SpriteRendererFS.frag" });
		//GraphicsEngine::get()->LinkShader(VAOassigned, programID);

	}

	MyGameObject::~MyGameObject()
	{
	}
}


