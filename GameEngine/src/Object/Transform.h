#pragma once
#include "Component.h"
#include <vector>
#include "../Types/Vector.h"
#include "../GLM/glm/glm.hpp"
#include <functional>
#include <list>

namespace vge {

	class Transform : public Component
	{

	private:

		Vector3F l_position;
		Vector3F l_rotation;
		Vector3F l_lookingTo;
		Vector3F l_scale;

		std::list <std::function<void(Vector3F)>* > callback_TRANSFORM_POSITION_MODIFIED;
		std::list < std::function<void(float, Vector3F)>* > callback_TRANSFORM_ROTATION_MODIFIED;
		std::list < std::function<void(Vector3F)>* > callback_TRANSFORM_SCALE_MODIFIED;
		std::list < std::function<void(Vector3F)>* > callback_TRANSFORM_LOOKINGTO_MODIFIED;

	public:

		Transform();
		~Transform();

		void Behaviour() override;

		void move(const Vector3F& direction);
		void rotate(float angles, Vector3F axis);
		void scale(const Vector3F& scalar);

		Vector3F position() { return this->l_position; }
		std::vector<float> positionArr() { return {l_position[0], l_position[1], l_position[2]}; }
		glm::vec3 positionGLM() { return glm::vec3(l_position[0], l_position[1], l_position[2]); }
		Vector3F rotation() { return this->l_rotation; }
		std::vector<float> rotationArr() { return { l_rotation[0], l_rotation[1], l_rotation[2] }; }
		glm::vec3 rotationGLM() { return glm::vec3(l_rotation[0], l_rotation[1], l_rotation[2]); }
		Vector3F lookingTo() { return this->l_lookingTo; }
		std::vector<float> lookingToArr() { return { l_lookingTo[0], l_lookingTo[1], l_lookingTo[2] }; }
		glm::vec3 lookingToGLM() { return glm::vec3(l_lookingTo[0], l_lookingTo[1], l_lookingTo[2]); }
		Vector3F scale() { return this->l_scale; }
		std::vector<float> scaleArr() { return { l_scale[0], l_scale[1], l_scale[2] }; }
		glm::vec3 scaleGLM() { return glm::vec3(l_scale[0], l_scale[1], l_scale[2]); }

		glm::mat4 getModelMatrixTransform();

		void setCallbacks(
			std::list < std::function<void(Vector3F)>*> callback_TRANSFORM_POSITION_MODIFIED,
			std::list < std::function<void(float, Vector3F)>*> callback_TRANSFORM_ROTATION_MODIFIED,
			std::list < std::function<void(Vector3F)>*> callback_TRANSFORM_SCALE_MODIFIED,
			std::list < std::function<void(Vector3F)>*> callback_TRANSFORM_LOOKINGTO_MODIFIED
		);

		void addCallback(
			std::function<void(Vector3F)>* callback_TRANSFORM_POSITION_MODIFIED,
			std::function<void(float, Vector3F)>* callback_TRANSFORM_ROTATION_MODIFIED,
			std::function<void(Vector3F)>* callback_TRANSFORM_SCALE_MODIFIED,
			std::function<void(Vector3F)>* callback_TRANSFORM_LOOKINGTO_MODIFIED
		);

		void removeCallback(
			std::function<void(Vector3F)>* callback_TRANSFORM_POSITION_MODIFIED,
			std::function<void(float, Vector3F)>* callback_TRANSFORM_ROTATION_MODIFIED,
			std::function<void(Vector3F)>* callback_TRANSFORM_SCALE_MODIFIED,
			std::function<void(Vector3F)>* callback_TRANSFORM_LOOKINGTO_MODIFIED
		);
	};


}