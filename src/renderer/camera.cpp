#include "renderer/camera.h"

#include <vector>
#include <algorithm>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
{
    this->worldUp = up;
    this->position = position;
    this->yaw = yaw;
    this->pitch = pitch;
    this->fly = true;
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
{
    this->position = glm::vec3(posX, posY, posZ);
    this->worldUp = glm::vec3(upX, upY, upZ);
    this->yaw = yaw;
    this->pitch = pitch;
    this->fly = true;
    updateCameraVectors();
}


glm::mat4 Camera::GetViewMatrix()
{
    // lookAt from scratch
    //--------------------
  /*glm::vec3 cameraTarget = position + front;
    glm::vec3 cameraDirection = glm::normalize(position - cameraTarget);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

    glm::mat4 camRot = glm::mat4(1.0f);
    camRot[0][0] = cameraRight.x; // First column, first row
    camRot[1][0] = cameraRight.y;
    camRot[2][0] = cameraRight.z;
    camRot[0][1] = cameraUp.x; // First column, second row
    camRot[1][1] = cameraUp.y;
    camRot[2][1] = cameraUp.z;
    camRot[0][2] = cameraDirection.x; // First column, third row
    camRot[1][2] = cameraDirection.y;
    camRot[2][2] = cameraDirection.z; 

    glm::mat4 camTrans = glm::mat4(1.0f);
    camTrans[3][0] = -position.x;
    camTrans[3][1] = -position.y;
    camTrans[3][2] = -position.z;

    return camRot * camTrans;*/

    return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::GetTarget()
{
    return position + front;
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = movementSpeed * deltaTime;
    if (direction == FORWARD)
        position += front * velocity;
    if (direction == BACKWARD)
        position -= front * velocity;
    if (direction == LEFT)
        position -= right * velocity;
    if (direction == RIGHT)
        position += right * velocity;
    // FPS style
    if(!fly)
        position.y = 0.0f;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (constrainPitch)
    {
        pitch = std::clamp(pitch, -89.0f, 89.0f);
    }

    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    zoom -= (float)yoffset;
    zoom = std::clamp(zoom, 1.0f, 45.0f);
}

void Camera::updateCameraVectors()
{
    // calculate the new front vector
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->front = glm::normalize(front);
    // also re-calculate the right and up vector
    right = glm::normalize(glm::cross(front, worldUp)); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up = glm::normalize(glm::cross(right, front));
}

void Camera::FirstPersonShooter()
{
    position.y = 0.0f;
    fly = !fly;
}
