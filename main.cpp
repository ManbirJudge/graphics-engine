#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Mesh.h"
#include "Log.h"

const unsigned int WIDTH = 900;
const unsigned int HEIGHT = 900; 

const float IDK = 2;

// --------
const Vertex planeVertices[] = {
	Vertex {
		glm::vec3(1.f, 0.f, 1.f),
		glm::vec3(0.f, -1.f, 0.f),
		glm::vec3(1.f, 0.f, 0.f),
		glm::vec2(1.f * IDK, 0.f),
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
		glm::vec2(0.f, 1.f * IDK),
	},
	Vertex {
		glm::vec3(1.f, 0.f, -1.f),
		glm::vec3(0.f, -1.f, 0.f),
		glm::vec3(0.f, 1.f, 0.f),
		glm::vec2(1.f * IDK, 1.f * IDK),
	}
};
const GLuint planeIndices[] = {
	3, 1, 0,
	2, 3, 1
};

const Vertex pyramidVertices[5] = {
	// Base
	{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
	{glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
	{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	{glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},

	// Apex
	{glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 1.0f)},
};
const GLuint pyramidIndices[18] = {
	// Base
	0, 1, 2,
	0, 2, 3,

	// Side Faces
	0, 4, 1,
	1, 4, 2,
	2, 4, 3,
	3, 4, 0
};
// --------

int main() {
	// initialising GLFW
	glfwInit();

	// telling GLFW the version of OpenGL we are using, for us -> 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// creating the window
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Graphics Engine", NULL, NULL);

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
	glViewport(0, 0, WIDTH, HEIGHT);
	std::cout << "[DEBUG] Viewport size configured." << std::endl;

	// meshes
	Texture textures[]
	{
		Texture("D:/Manbir/Programming/C++ Projects/(1) Graphics Engine/Ground_Dirt_009_BaseColor.jpg", "color", 0),
		Texture("D:/Manbir/Programming/C++ Projects/(1) Graphics Engine/Ground_Dirt_009_Roughness.jpg", "specular", 1),
		Texture("D:/Manbir/Programming/C++ Projects/(1) Graphics Engine/Ground_Dirt_009_Normal.jpg", "normal", 2)
	};

	std::vector<Vertex> meshVertices(planeVertices, planeVertices + sizeof(planeVertices) / sizeof(Vertex));
	std::vector<GLuint> meshIndices(planeIndices, planeIndices + sizeof(planeIndices) / sizeof(GLuint));
	std::vector<Texture> meshTextures(textures, textures + sizeof(textures) / sizeof(Texture));

	Mesh mesh(meshVertices, meshIndices, meshTextures);

	glm::vec3 meshPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 meshModelMat = glm::translate(glm::mat4(1.0f), meshPos);

	std::cout << "[DEBUG] Meshes configured." << std::endl;

	// setting up shader program
	Shader shaderProgram(
		"D:\\Manbir\\Programming\\C++ Projects\\(1) Graphics Engine\\default.vert", 
		"D:\\Manbir\\Programming\\C++ Projects\\(1) Graphics Engine\\phong.frag"
	);

	shaderProgram.Activate();

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "globalMat"), 1, GL_FALSE, glm::value_ptr(meshModelMat));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), 1, 1, 1, 1);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), 0.5, 1., 0.5);

	std::cout << "[DEBUG] Shader program configured." << std::endl;

	// enabling depth
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DOUBLEBUFFER);
	std::cout << "[DEBUG] Depth enabled." << std::endl;

	// setting up camera
	Camera camera(WIDTH, HEIGHT, glm::vec3(0.f, 2.f, 2.f), -90.f, -45.f);

	std::cout << "[DEBUG] Camera configured." << std::endl;

	// main while loop
	float pTime = glfwGetTime();
	float cTime = .0f;

	std::cout << "[DEBUG] Starting the mainloop." << std::endl;

	while (!glfwWindowShouldClose(window)) {
		cTime = glfwGetTime();
		float fps = 1 / (cTime - pTime);
		pTime = cTime;

		std::cout << fps << std::endl;

		// background color
		glClearColor(.07f, .13f, .17f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// updating camera
		camera.Inputs(window);
		camera.updateMatrix(45.f, .1f, 100.f);

		// inputs
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) mesh.Move(glm::vec3(.0f, .0f, -0.1f));
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) mesh.Move(glm::vec3(.0f, .0f, 0.1f));
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) mesh.Move(glm::vec3(-0.1f, .0f, .0f));
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) mesh.Move(glm::vec3(0.1f, .0f, .0f));

		// rendering meshes
		mesh.Render(shaderProgram, camera);

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

	// successful execution
	return 0;
}