#include "SpriteRenderer.h"

#include "../../GraphicsEngine/GraphicsEngine.h"
#include "../../GraphicsEngine/ObjLoader.h"



namespace vge {

    SpriteRenderer::SpriteRenderer()
    {
    }

    SpriteRenderer::SpriteRenderer(const char* texurePath)
	{
		this->drawableObject = GraphicsEngineVGE.createDrawableObject(
			"./src/plane.obj",
			texurePath,
			"spriteRendererProgram"
		);
	}

	void SpriteRenderer::setSprite(const char* filename)
	{
		this->drawableObject = GraphicsEngineVGE.createDrawableObject(
			"./src/plane.obj",
			filename,
			"spriteRendererProgram"
		);
	}

	void SpriteRenderer::Behaviour()
	{
		this->drawableObject->transformMatrix = this->objectTransform->getModelMatrixTransform();
		GraphicsEngine::get()->setDrawableObject(this->drawableObject);
	}

}
