#pragma once
#include "../Object/Component.h"

namespace vge {

	class SpriteRenderer : public Component
	{

	private:

		const char* texturePath;
		unsigned char* textureData;

		int width, height;

	public:

		SpriteRenderer();
		SpriteRenderer(const char* filename);

		void Behaviour() override;

	};

}

