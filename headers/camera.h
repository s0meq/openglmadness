#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "shaderClass.h"

class Camera
{
    public:
        // Camera Attributes
        glm::vec3 Position;
        glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::mat4 cameraMatrix = glm::mat4(1.0f);

        // Prevents the camera from jumping around when first clicking on the window
        bool firstClick = true;

        // Screen dimensions
        int width;
        int height;

        // Camera options
        float speed = 0.1f;
        float sensitivity = 100.0f;


        // Constructor with vectors
        Camera(int width, int height, glm::vec3 position);

        // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
        void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
        void Matrix(Shader& shader, const char* uniform);
        // Processes input received from any keyboard-like input system. Accepts input parameter in the form 
        // of camera defined ENUM (to abstract it from windowing systems)
        void Inputs(GLFWwindow* window);


    //     glm::vec3 Right;
    //     glm::vec3 WorldUp;

    //     // Euler Angles
    //     float Yaw;
    //     float Pitch;

    //     // Camera options
    //     float speed;
    //     float sensitivity;
    //     float Zoom;

    //     // Constructor with vectors
    //     Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);
    //     // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
    //     glm::mat4 GetViewMatrix();
    //     // Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    //     void ProcessKeyboard(int direction, float deltaTime);
    //     // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    //     void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    //     // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    //     void ProcessMouseScroll(float yoffset);
    // private:
    //     // Calculates the front vector from the Camera's (updated) Euler Angles
    //     void updateCameraVectors();
};

#endif // CAMERA_CLASS_H