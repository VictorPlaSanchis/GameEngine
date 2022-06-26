#include "SpriteRenderer.h"

#include "GraphicsEngine.h"

#include <GL/glew.h>

namespace vge {

    SpriteRenderer::SpriteRenderer()
    {
    }

    SpriteRenderer::SpriteRenderer(const char* filename)
	{
		this->texturePath = filename;
	}

	void SpriteRenderer::Behaviour()
	{
	}

}
