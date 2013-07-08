#ifndef RENDERER_CAMERA_HPP
#define RENDERER_CAMERA_HPP

#include <glm/glm.hpp>

namespace Antumbra
{
	class Camera
	{
	public:
		Camera();

		void SetAspectRatio(float aspectRatio);
		void SetFieldOfView(float fieldOfView);

		void SetRotation(glm::vec2 rotation);
		void SetPosition(glm::vec3 position);

		void OffsetRotation(glm::vec2 rotation);
		void OffsetPosition(glm::vec3 position);

		glm::vec3 GetPosition() const;
		glm::vec3 GetUpVector() const;
		glm::vec3 GetRightVector() const;
		glm::vec3 GetForwardVector() const;

		glm::mat4 GetProjMatrix() const;
		glm::mat4 GetViewMatrix() const;
		glm::mat4 GetOrientationMatrix() const;
	private:
		float m_aspectRatio;
		float m_fieldOfView;
		glm::vec2 m_rotation;
		glm::vec3 m_position;
	};
}

#endif