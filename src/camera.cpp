#include "camera.h"
#include <iostream>

camera::camera(int width, int height, glm::vec3 pos)
{
	camera::width = width;
	camera::height = height;
	position = pos;
}

void camera::matrix(float FOVdeg, float nearPlane, float farPlane, shader& viewShader, const char* uniform)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(position, position + orientation, up);
	projection = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);

	viewShader.setMatrixUniform(uniform, projection * view);
}

void camera::inputs(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position += speed * orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position += speed * -glm::normalize(glm::cross(orientation, up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position += speed * -orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position += speed * glm::normalize(glm::cross(orientation, up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		position += speed * up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		position += speed * -up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 0.4f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 0.1f;
	}

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	float rotationX = sens * (float)(mouseY - (height / 2)) / height;
	float rotationY = sens * (float)(mouseX - (width / 2)) / width;

	glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotationX), glm::normalize(glm::cross(orientation, up)));

	if (!((glm::angle(newOrientation, up) <= glm::radians(5.0f)) or (glm::angle(newOrientation, -up) <= glm::radians(5.0f))))
	{
		orientation = newOrientation;
	}

	orientation = glm::rotate(orientation, glm::radians(-rotationY), up);

	glfwSetCursorPos(window, width / 2, height / 2);
}