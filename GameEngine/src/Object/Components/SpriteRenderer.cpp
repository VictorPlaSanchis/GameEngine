#include "SpriteRenderer.h"

#include "../../GraphicsEngine/GraphicsEngine.h"
#include "../../GraphicsEngine/ObjLoader.h"



namespace vge {

    SpriteRenderer::SpriteRenderer()
    {
		this->spriteModel = new Model();
    }

    SpriteRenderer::SpriteRenderer(const char* filename)
	{
		Model* plane = ObjLoader::loadObj("./src/plane.obj");
		this->spriteModel = new Model();
		this->spriteModel->load(plane);
		this->spriteModel->assignTexture(filename);
		unsigned int shaderIDassigned = GraphicsEngine::get()->CreateProgram({
			"./src/Object/Components/SpriteRendererVS.vert",
			"./src/Object/Components/SpriteRendererFS.frag"
		});
		this->spriteModel->setVAOassigned(GraphicsEngine::get()->pushModel(this->spriteModel, shaderIDassigned));
		GraphicsEngine::get()->LinkShader(this->spriteModel->VAOassigned, shaderIDassigned);
	
	}

	void SpriteRenderer::setSprite(const char* filename)
	{
		Model* plane = ObjLoader::loadObj("./src/plane.obj");
		this->spriteModel->load(plane);
		this->spriteModel->assignVertexsTexCoord({
			0.0f, 0.0f,
			0.0f, -1.0f,
			1.0f, 0.0f,
			0.0f, -1.0f,
			1.0f, -1.0f,
			1.0f, 0.0f
			});
		this->spriteModel->assignTexture(filename);
		unsigned int shaderIDassigned = GraphicsEngine::get()->CreateProgram({
			"./src/Object/Components/SpriteRendererVS.vert",
			"./src/Object/Components/SpriteRendererFS.frag"
			});
		this->spriteModel->setVAOassigned(GraphicsEngine::get()->pushModel(this->spriteModel, shaderIDassigned));
		GraphicsEngine::get()->LinkShader(this->spriteModel->VAOassigned, shaderIDassigned);
	}

	void SpriteRenderer::Behaviour()
	{
		this->spriteModel->Behaviour();
	}

}
