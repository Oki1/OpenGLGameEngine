#include "Headers/camera.hpp"
#include <iostream>


Camera::Camera(glm::vec3 _worldUp, glm::vec3 _camPos, float _movementSpeed, float _yaw, float _pitch, float _roll, float _sens) : worldUp(_worldUp), camPos(_camPos), movementSpeed(_movementSpeed), yaw(_yaw), pitch(_pitch), roll(_roll), sens(_sens) {
	processCamVectors();
};
void Camera::processCamVectors() {
	// calculate the new Front vector
	glm::vec3 front_;
	front_.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front_.y = sin(glm::radians(pitch));
	front_.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	camFront = glm::normalize(front_);
	// also re-calculate the Right and Up vector
	camRight = glm::normalize(glm::cross(camFront, worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	camUp = glm::normalize(glm::cross(camRight, camFront));
}

void Camera::processKeyboard(movementDirections dir, float deltaTime) {
	float vel = deltaTime * movementSpeed;
	if (dir == CAM_LEFT) {
		camPos -= camRight * vel;
	}
	if (dir == CAM_RIGHT) {
		camPos += camRight * vel;
	}
	if (dir == CAM_FORWARD) {
		camPos += camFront * vel;
	}
	if (dir == CAM_BACKWARD) {
		camPos -= camFront * vel;
	}
	if (dir == CAM_UP) {
		camPos += camUp * vel;
	}
	if (dir == CAM_DOWN) {
		camPos -= camUp * vel;
	}
}
void Camera::processMouse(double xoffset, double yoffset) {
	xoffset *= sens;
	yoffset *= sens;
	yaw += xoffset;
	pitch += yoffset;
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
	processCamVectors();
}