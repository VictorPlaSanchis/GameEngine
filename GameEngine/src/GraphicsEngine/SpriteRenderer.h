#pragma once
#include "../Object/Component.h"

namespace vge {

	class SpriteRenderer : public Component
	{

	private:

		const char* spriteFilePath;

	public:

		SpriteRenderer(const char* spriteFilePath = "");
		~SpriteRenderer();

		void Behaviour() override;

	};

}

