#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
 
#include "Shader.h"

class Camera
{
public:
	glm::vec3 Position = glm::vec3(0.f, 0.f, 0.f);

	float yaw = -90.f;
	float pitch = 0.f;

	glm::vec3 up = glm::vec3(0.f, 0.1f, 0.f);
	glm::vec3 forward = glm::vec3(0.f, 0.f, -1.f);
	glm::vec3 right = glm::vec3(1.f, 0.f, 0.f);

	glm::mat4 cameraMatrix = glm::mat4(1.f);

	int width;
	int height;

	const float SPEED = 4.f;
	float SENSTIVITY = 70.f;

	double lastTime = glfwGetTime();
	bool firstClick = true;
	bool stationary = true;

	Camera(int width, int height);
	Camera(int width, int height, glm::vec3 position, float yaw = -90.f, float pitch = 0.f);

	void Matrix(Shader& shader, const char* uniform);
	void updateMatrix(float FOVMag, float nearPlane, float farPlane);

	void Inputs(GLFWwindow* window);
};

#endif