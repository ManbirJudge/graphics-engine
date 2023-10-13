#include "Camera.h"

Camera::Camera(int width, int height) {
	Camera::width = width;
	Camera::height = height;
}
Camera::Camera(int width, int height, glm::vec3 position, float yaw, float pitch) {
	Camera::width = width;
	Camera::height = height;
	Camera::Position = position;
	Camera::yaw = yaw;
	Camera::pitch = pitch;
}

void Camera::Matrix(Shader& shader, const char* uniform) 
{
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));  // assignign value to the uniform
}

void Camera::updateMatrix(float FOVMag, float nearPlane, float farPlane) 
{
	glm::mat4 viewMat = glm::mat4(1.0f);  // camera coordinates
	glm::mat4 projMat = glm::mat4(1.0f);  // projection coordinates

	float yaw_ = glm::radians(Camera::yaw);
	float pitch_ = glm::radians(Camera::pitch);

	Camera::forward.x = glm::cos(yaw_) * glm::cos(pitch_);
	Camera::forward.y = glm::sin(pitch_);
	Camera::forward.z = glm::sin(yaw_) * glm::cos(pitch_);

	Camera::forward = glm::normalize(Camera::forward);
	Camera::right = glm::normalize(glm::cross(Camera::forward, glm::vec3(0.f, 1.f, 0.f)));
	Camera::up = glm::normalize(glm::cross(Camera::right, Camera::forward));

	viewMat = glm::lookAt(Position, Position + forward, up);
	projMat = glm::perspective(glm::radians(45.0f), (float)(width / height), nearPlane, farPlane);

	cameraMatrix = projMat * viewMat;
}

void Camera::Inputs(GLFWwindow* window) 
{
	double currentTime = glfwGetTime();
	double deltaTime = currentTime - lastTime;
	lastTime = currentTime;

	float velocity = SPEED * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) Position += forward * velocity;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) Position -= forward * velocity;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) Position += right * velocity;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) Position -= right * velocity;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) Position += up * velocity;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) Position -= up * velocity;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (firstClick)
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}

		double mouseX;
		double mouseY;

		glfwGetCursorPos(window, &mouseX, &mouseY);

		std::cout << mouseX << " " << mouseY << std::endl;

		mouseX = (mouseX - (width / 2)) / width;
		mouseY = (mouseY - (height / 2)) / height;

		Camera::yaw += mouseX * SENSTIVITY;
		Camera::pitch -= glm::max(-89., glm::min(89., mouseY * SENSTIVITY));

		glfwSetCursorPos(window, (width / 2), (height / 2));
	} else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}
}