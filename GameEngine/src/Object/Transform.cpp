#include "Transform.h"
#include "../GLM/glm/ext/matrix_transform.hpp"

namespace vge {

	Transform::Transform()
		: l_position({ 0.0f, 0.0f, 0.0f }),
		  l_rotation({ 0.0f, 0.0f, 0.0f }),
		  l_scale(   { 1.0f, 1.0f, 1.0f }),
		  l_lookingTo({ 0.0f, 0.0f, 1.0f })
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::Behaviour()
	{
		//l_lookingTo = l_rotation;
	}

	void Transform::move(const Vector3F& direction)
	{
		this->l_position += direction;

		for (std::function<void(Vector3F)>* callback : callback_TRANSFORM_POSITION_MODIFIED) {
			(*callback)(direction);
		}
	}

	void Transform::rotate(float angles, Vector3F axis)
	{
		//this->l_lookingTo = l_rotation;
		this->l_rotation.rotate(angles, axis);

		for (std::function<void(float, Vector3F)>* callback : callback_TRANSFORM_ROTATION_MODIFIED) {
			(*callback)(angles, axis);
		}
	}

	void Transform::scale(const Vector3F& scalar)
	{
		this->l_scale = scalar;

		for(std::function<void(Vector3F)>* callback : callback_TRANSFORM_SCALE_MODIFIED) {
			(*callback)(scalar);
		}
	}

	glm::mat4 Transform::getModelMatrixTransform()
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(this->positionGLM()));
		model = glm::scale(model, this->scaleGLM());

		float anglesToRotate = this->rotation().angleOnEulerDegrees(this->lookingTo());
		Vector3F axisRotation = this->rotation().cross(this->lookingTo()).normalize();
		if (anglesToRotate != 0.0f) model = glm::rotate(model, anglesToRotate, (axisRotation).ToGLM());
		return model;
	}

	void Transform::setCallbacks(
		std::list < std::function<void(Vector3F)>*> callback_TRANSFORM_POSITION_MODIFIED,
		std::list < std::function<void(float, Vector3F)>*> callback_TRANSFORM_ROTATION_MODIFIED,
		std::list < std::function<void(Vector3F)>*> callback_TRANSFORM_SCALE_MODIFIED,
		std::list < std::function<void(Vector3F)>*> callback_TRANSFORM_LOOKINGTO_MODIFIED)
	{
		this->callback_TRANSFORM_POSITION_MODIFIED = callback_TRANSFORM_POSITION_MODIFIED;
		this->callback_TRANSFORM_ROTATION_MODIFIED = callback_TRANSFORM_ROTATION_MODIFIED;
		this->callback_TRANSFORM_SCALE_MODIFIED = callback_TRANSFORM_SCALE_MODIFIED;
		this->callback_TRANSFORM_LOOKINGTO_MODIFIED = callback_TRANSFORM_LOOKINGTO_MODIFIED;
	}

	void Transform::addCallback(
		std::function<void(Vector3F)>* callback_TRANSFORM_POSITION_MODIFIED,
		std::function<void(float, Vector3F)>* callback_TRANSFORM_ROTATION_MODIFIED,
		std::function<void(Vector3F)>* callback_TRANSFORM_SCALE_MODIFIED,
		std::function<void(Vector3F)>* callback_TRANSFORM_LOOKINGTO_MODIFIED)
	{
		this->callback_TRANSFORM_POSITION_MODIFIED.push_back(callback_TRANSFORM_POSITION_MODIFIED);
		this->callback_TRANSFORM_ROTATION_MODIFIED.push_back(callback_TRANSFORM_ROTATION_MODIFIED);
		this->callback_TRANSFORM_SCALE_MODIFIED.push_back(callback_TRANSFORM_SCALE_MODIFIED);
		this->callback_TRANSFORM_LOOKINGTO_MODIFIED.push_back(callback_TRANSFORM_LOOKINGTO_MODIFIED);
	}

	void Transform::removeCallback(
		std::function<void(Vector3F)>* callback_TRANSFORM_POSITION_MODIFIED,
		std::function<void(float, Vector3F)>* callback_TRANSFORM_ROTATION_MODIFIED,
		std::function<void(Vector3F)>* callback_TRANSFORM_SCALE_MODIFIED,
		std::function<void(Vector3F)>* callback_TRANSFORM_LOOKINGTO_MODIFIED)
	{
		this->callback_TRANSFORM_POSITION_MODIFIED.remove(callback_TRANSFORM_POSITION_MODIFIED);
		this->callback_TRANSFORM_ROTATION_MODIFIED.remove(callback_TRANSFORM_ROTATION_MODIFIED);
		this->callback_TRANSFORM_SCALE_MODIFIED.remove(callback_TRANSFORM_SCALE_MODIFIED);
		this->callback_TRANSFORM_LOOKINGTO_MODIFIED.remove(callback_TRANSFORM_LOOKINGTO_MODIFIED);
	}

}