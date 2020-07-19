#include "camera.hpp"

//#include <vector>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movement_speed(SPEED), mouse_sensitivity(SENSITIVITY), zoom(ZOOM) {
    position = position;
    world_up = up;
    yaw = yaw;
    pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y, float up_z, float yaw, float pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movement_speed(SPEED), mouse_sensitivity(SENSITIVITY), zoom(ZOOM) {
    position = glm::vec3(pos_x, pos_y, pos_z);
    world_up = glm::vec3(up_x, up_y, up_z);
    yaw = yaw;
    pitch = pitch;
    updateCameraVectors();
}

void Camera::processKeyboard(Camera_Movement direction, float delta_time) {
    float velocity = movement_speed * delta_time;
    if(direction == FORWARD)
        position += front * velocity;
    else if(direction == BACKWARD)
        position -= front * velocity;
    else if(direction == LEFT)
        position -= right * velocity;
    else if(direction == RIGHT)
        position += right * velocity;
    else if(direction == UP)
        position += up * velocity;
    else if(direction == DOWN)
        position -= up * velocity;
}

void Camera::processMouseMovement(float offset_x, float offset_y, GLboolean constrain_pitch) {
    offset_x *= mouse_sensitivity;
    offset_y *= mouse_sensitivity;

    yaw   += offset_x;
    pitch += offset_y;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrain_pitch) {
        if(pitch > 89.0f)
            pitch = 89.0f;
        else if(pitch < -89.0f)
            pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

void Camera::processMouseScroll(float offset_y) {
    zoom -= (float)offset_y;
    if(zoom < 1.0f)
        zoom = 1.0f;
    if(zoom > 45.0f)
        zoom = 45.0f;
}

void Camera::updateCameraVectors() {
    // calculate the new Front vector
    glm::vec3 front_;
    front_.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front_.y = sin(glm::radians(pitch));
    front_.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front_);
    // also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(front, world_up));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up = glm::normalize(glm::cross(right, front));
}
