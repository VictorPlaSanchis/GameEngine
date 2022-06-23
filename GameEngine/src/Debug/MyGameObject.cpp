#include "MyGameObject.h"
#include "../Log/Console.h"
#include "../GraphicsEngine/GraphicsEngine.h"

namespace vge {

	MyGameObject::MyGameObject()
	{
		this->components = {};
		this->childs = {};
		this->transform = new Transform();

		Model* model = new Model({
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f
		});

		model->assignVertexsTexCoord({
			0.0f, 0.0f,
			0.0f, -1.0f,
			1.0f, 0.0f,
			0.0f, -1.0f,
			1.0f, -1.0f,
			1.0f, 0.0f
		});

		unsigned int programID = GraphicsEngine::get()->CreateProgram({ "./src/GraphicsEngine/SpriteRendererVS.vert", "./src/GraphicsEngine/SpriteRendererFS.frag" });
		unsigned int VAOassigned = GraphicsEngine::get()->pushModel(model, programID);
		GraphicsEngine::get()->LinkShader(VAOassigned, programID);

		model->assignTexture("./imgs/tumblr.png");

		MyGameScript* script = new MyGameScript();
		SpriteRenderer* sprite = new SpriteRenderer("./imgs/nya.bmp");;
		this->addComponent(script);
		this->addComponent(sprite);
		this->addComponent(model);

	}

	MyGameObject::~MyGameObject()
	{
	}
}


