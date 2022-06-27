#include "SpriteRenderer.h"

#include "../../GraphicsEngine/GraphicsEngine.h"

#include <GL/glew.h>

namespace vge {

    SpriteRenderer::SpriteRenderer()
    {
    }

    SpriteRenderer::SpriteRenderer(const char* filename)
	{
		std::vector<float> vertexs = {
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f
		};

		spriteModel = new Model(vertexs);
		spriteModel->assignVertexsTexCoord({
			0.0f, 0.0f,
			0.0f, -1.0f,
			1.0f, 0.0f,
			0.0f, -1.0f,
			1.0f, -1.0f,
			1.0f, 0.0f
		});
		spriteModel->assignTexture(filename);
		this->ShaderProgramLinked = GraphicsEngine::get()->CreateProgram({
			"./src/Object/Components/SpriteRendererVS.vert",
			"./src/Object/Components/SpriteRendererFS.frag"
		});
		this->VAOassigned = GraphicsEngine::get()->pushModel(spriteModel, this->ShaderProgramLinked);
		GraphicsEngine::get()->LinkShader(this->VAOassigned, this->ShaderProgramLinked);
	
	}

	void SpriteRenderer::Behaviour()
	{
	}

}
