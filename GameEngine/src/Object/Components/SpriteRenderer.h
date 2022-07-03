#pragma once
#include "../Component.h"
#include "Model.h"

namespace vge {

	class SpriteRenderer : public Component
	{

	private:

		Model* spriteModel;

	public:

		SpriteRenderer();
		SpriteRenderer(const char* filename);

		void setSprite(const char* filename);
		Model* getSpriteModel() { return this->spriteModel; }

		virtual void Behaviour();


	};

}

