#pragma once
#include "../Component.h"
#include "Model.h"

namespace vge {

	class SpriteRenderer : public Component
	{

	private:

		Model* spriteModel;
		unsigned int VAOassigned;
		unsigned int ShaderProgramLinked;

	public:

		SpriteRenderer();
		SpriteRenderer(const char* filename);

		void Behaviour() override;
		unsigned int getVAOassigned() { return this->VAOassigned; }
		unsigned int getShaderProgramLinked() { return this->ShaderProgramLinked; }

	};

}

