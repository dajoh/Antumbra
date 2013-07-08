#include <glm/gtc/matrix_transform.hpp>
#include "Camera.hpp"

namespace Antumbra
{
	Camera::Camera()
	{
		m_aspectRatio = 4.0f / 3.0f;
		m_fieldOfView = 70.0f;
	}

	void Camera::SetAspectRatio(float aspectRatio)
	{
		m_aspectRatio = aspectRatio;
	}

	void Camera::SetFieldOfView(float fieldOfView)
	{
		m_fieldOfView = fieldOfView;
	}

	void Camera::SetRotation(glm::vec2 rotation)
	{
		m_rotation = rotation;
	}

	void Camera::SetPosition(glm::vec3 position)
	{
		m_position = position;
	}

	void Camera::OffsetRotation(glm::vec2 rotation)
	{
		m_rotation.x += rotation.x;
		while(m_rotation.x > 360.0f) m_rotation.x -= 360.0;
		while(m_rotation.x < 0.0f) m_rotation.x += 360.0;

		m_rotation.y += rotation.y;
		if(m_rotation.y > 89.9f) m_rotation.y = 89.9f;
		if(m_rotation.y < -89.9f) m_rotation.y = -89.9f;
	}

	void Camera::OffsetPosition(glm::vec3 position)
	{
		m_position += position;
	}

	glm::vec3 Camera::GetPosition() const
	{
		return m_position;
	}

	glm::vec3 Camera::GetUpVector() const
	{
		glm::vec4 vec = glm::inverse(GetOrientationMatrix()) * glm::vec4(0, 1, 0, 1);
		return glm::vec3(vec);
	}

	glm::vec3 Camera::GetRightVector() const
	{
		glm::vec4 vec = glm::inverse(GetOrientationMatrix()) * glm::vec4(1, 0, 0, 1);
		return glm::vec3(vec);
	}

	glm::vec3 Camera::GetForwardVector() const
	{
		glm::vec4 vec = glm::inverse(GetOrientationMatrix()) * glm::vec4(0, 0, -1, 1);
		return glm::vec3(vec);
	}

	glm::mat4 Camera::GetProjMatrix() const
	{
		return glm::perspective(m_fieldOfView, m_aspectRatio, 0.01f, 1000.0f);
	}

	glm::mat4 Camera::GetViewMatrix() const
	{
		return glm::translate(GetOrientationMatrix(), -m_position);
	}

	glm::mat4 Camera::GetOrientationMatrix() const
	{
		glm::mat4 orientation;
		orientation = glm::rotate(orientation, m_rotation.y, glm::vec3(1, 0, 0));
		orientation = glm::rotate(orientation, m_rotation.x, glm::vec3(0, 1, 0));
		return orientation;
	}
}