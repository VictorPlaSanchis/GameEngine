#pragma once
#include "../Component.h"
#include "Model.h"
#include "../../GraphicsEngine/DrawableObject.h"

namespace vge {

	class SpriteRenderer : public Component
	{

	private:

		Transform* objectTransform;
		DrawableObject* drawableObject;

	public:

		SpriteRenderer();
		SpriteRenderer(const char* filename);

		void setSprite(const char* filename);
		void setTransform(Transform* objectTransform) { this->objectTransform = objectTransform; }

		virtual void Behaviour();

	};

}

