#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Mesh.h"
#include "Log.h"

const unsigned int winWidth = 900;
const unsigned int winHeight = 900; 

const float IDK = 1.f;

// --------
const Vertex vertices[] = {
	Vertex {
		glm::vec3(1.f, 0.f, 1.f),
		glm::vec3(0.f, -1.f, 0.f),
		glm::vec3(1.f, 0.f, 0.f),
		glm::vec2(1.f, 0.f),
	},
	Vertex {
		glm::vec3(-1.f, 0.f, 1.f),
		glm::vec3(0.f, -1.f, 0.f),
		glm::vec3(0.f, 0.f, 1.f),
		glm::vec2(0.f, 0.f),
	},
	Vertex {
		glm::vec3(-1.f, 0.f, -1.f),
		glm::vec3(0.f, -1.f, 0.f),
		glm::vec3(1.f, 1.f, 1.f),
		glm::vec2(0.f, 1.f),
	},
	Vertex {
		glm::vec3(1.f, 0.f, -1.f),
		glm::vec3(0.f, -1.f, 0.f),
		glm::vec3(0.f, 1.f, 0.f),
		glm::vec2(1.f, 1.f),
	},

	Vertex {
		glm::vec3(1.f, 0.f, 1.f),
		glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(1.f, 0.f, 0.f),
		glm::vec2(0.f, 1.f),
	},
	Vertex {
		glm::vec3(1.f, 0.f, -1.f),
		glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(0.f, 1.f, 0.f),
		glm::vec2(1.f, 1.f),
	},
	Vertex {
		glm::vec3(1.f, 2.f, -1.f),
		glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(0.f, 1.f, 0.f),
		glm::vec2(1.f, 0.f),
	},
	Vertex {
		glm::vec3(1.f, 2.f, 1.f),
		glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(0.f, 1.f, 0.f),
		glm::vec2(0.f, 0.f),
	},
};

const GLuint indices[] = {
	3, 1, 0,
	2, 3, 1,

	4, 5, 6,
	4, 7, 6
};
//const GLuint indices[] = {
//	0, 1, 2, 3
//};
// --------

int main() {
	// initialising GLFW
	glfwInit();

	// telling GLFW the version of OpenGL we are using, for us -> 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// creating the window
	GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, "Graphics Engine", NULL, NULL);

	// error checking window creation
	if (window == NULL) {
		std::cout << "[ERROR] Failed to create GLFW window," << std::endl;
		glfwTerminate();
		return -1;
	} else {
		std::cout << "[DEBUG] Created GLFW window." << std::endl;
	}

	// introducing window to current context
	glfwMakeContextCurrent(window);
	std::cout << "[DEBUG] Contextualized current GLFW window." << std::endl;

	// loading GLAD
	gladLoadGL();
	std::cout << "[DEBUG] Glad loaded." << std::endl;

	// specifying viewport size of OpenGL in the window
	glViewport(0, 0, winWidth, winHeight);
	std::cout << "[DEBUG] Viewport size configured." << std::endl;

	// meshes
	Texture textures[]
	{
		Texture("D:\\Manbir\\Programming\\C++ Projects\\(3) Graphics Engine\\floor__color.jpg", "diffuse", 0),
		Texture("D:\\Manbir\\Programming\\C++ Projects\\(3) Graphics Engine\\floor__spec.jpg", "specular", 1),
		Texture("D:\\Manbir\\Programming\\C++ Projects\\(3) Graphics Engine\\floor__height.jpg", "height", 2)
	};

	std::vector <Vertex> planeVertices(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> planeIndices(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> planeTextures(textures, textures + sizeof(textures) / sizeof(Texture));

	Mesh plane(planeVertices, planeIndices, planeTextures);

	glm::vec3 planePos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 planeModelMat = glm::translate(glm::mat4(1.0f), planePos);

	std::cout << "[DEBUG] Meshes configured." << std::endl;

	// setting up shader program
	Shader shaderProgram(
		"D:\\Manbir\\Programming\\C++ Projects\\(1) Graphics Engine\\default.vert", 
		"D:\\Manbir\\Programming\\C++ Projects\\(1) Graphics Engine\\default.frag"
	);

	shaderProgram.Activate();

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "globalMat"), 1, GL_FALSE, glm::value_ptr(planeModelMat));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), 1, 1, 1, 1);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), 0, 1., 0.);

	std::cout << "[DEBUG] Shader program configured." << std::endl;

	// enabling depth
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DOUBLEBUFFER);
	std::cout << "[DEBUG] Depth enabled." << std::endl;

	// setting up camera
	Camera camera(winWidth, winHeight, glm::vec3(0.f, 2.f, 2.f), -90.f, -45.f);

	std::cout << "[DEBUG] Camera configured." << std::endl;

	// main while loop
	std::cout << "[DEBUG] Starting the mainloop." << std::endl;

	while (!glfwWindowShouldClose(window)) {
		float time = glfwGetTime();

		// background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// updating camera
		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		// inputs

		// rendering meshes
		plane.Render(shaderProgram, camera);

		// swapping buffers of the window
		glfwSwapBuffers(window);

		// checking for events, important to do or will stop responding
		glfwPollEvents();
	}

	// deleting the meshes, shader programs and others
	shaderProgram.Delete();

	// destroying the window and terminating the GLFW process
	glfwDestroyWindow(window);
	glfwTerminate();

	// succesful execution
	return 0;
}