#include "Camera.h"

#include <glm.hpp>
#include <vec3.hpp>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

Camera::Camera(float ffov, float fnearPlane, float ffarPlane, int fframeBufferWidth, int fframeBufferHeight, glm::vec3 finitialPos, glm::vec3 finitialViewDirection)
{
	fov = ffov;
	nearPlane = fnearPlane;
	farPlane = ffarPlane;

	frameBufferWidth = fframeBufferWidth;
	frameBufferHeight = fframeBufferHeight;

	position = finitialPos;
	viewDirection = finitialViewDirection;
	worldUp = glm::vec3(0.f, 1.f, 0.f);
}

glm::mat4 Camera::getWorldToViewMatrix() const {
	return glm::lookAt(position, position + viewDirection, worldUp);
}

glm::mat4 Camera::getProjectionMatrix() const {
	return glm::perspective(glm::radians(fov), static_cast<float>(frameBufferWidth) / frameBufferHeight, nearPlane, farPlane);
}

glm::vec3 Camera::getCameraWorldPosition() const {
	return position;
}

void Camera::moveCamera() {
	position.z += 0.2f;
}