#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
enum movementDirections {
	CAM_FORWARD,
	CAM_LEFT,
	CAM_RIGHT, 
	CAM_UP,
	CAM_DOWN, 
	CAM_BACKWARD
};
class Camera{
private:
	float movementSpeed;
	glm::vec3 worldUp;

	//cam vectors
	//-------------------
	glm::vec3 camFront;
	glm::vec3 camUp;
	glm::vec3 camRight;
	
	float sens;
	float yaw, pitch, roll;
	void processCamVectors();

public:
	Camera(glm::vec3 _worldUp = glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3 _camPos = glm::vec3(0.0f, 0.0f, 3.0f), float _movementSpeed = 5.0f, float _yaw = -90.0f, float _pitch = 0.0f, float _roll = 0.0f, float _sens = 0.1f);
	inline glm::mat4 getViewMatrix() {
		return glm::lookAt(camPos, camPos + camFront, worldUp);
	}
	void processKeyboard(movementDirections dir, float deltaTime);
	void processMouse(double xpos, double ypos);
	glm::vec3 camPos;
};