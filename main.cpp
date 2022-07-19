#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Mesh.h"
#include "Log.h"

const unsigned int winWidth = 800;
const unsigned int winHeight = 800; 

const float IDK = 1.f;
const float IDK2 = 0.5f;

Vertex vertices[] =
{
	Vertex
	{
		glm::vec3(-IDK, 0.0f, IDK),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec2(0.0f, 0.0f)
	},
	Vertex
	{
		glm::vec3(-IDK, 0.0f, -IDK),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec2(0.0f, IDK)
	},
	Vertex
	{
		glm::vec3(IDK, 0.0f, -IDK),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec2(IDK, IDK)
	},
	Vertex
	{
		glm::vec3(IDK, 0.0f,  IDK),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec2(IDK, 0.0f)
	},

	Vertex
	{
		glm::vec3(-IDK, 2 * IDK, IDK),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec2(0.0f, 0.0f)
	},
	Vertex
	{
		glm::vec3(-IDK, 2 * IDK, -IDK),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec2(0.0f, IDK)
	},
	Vertex
	{
		glm::vec3(IDK, 2 * IDK, -IDK),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec2(IDK, IDK)
	},
	Vertex
	{
		glm::vec3(IDK, 2 * IDK,  IDK),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec2(IDK, 0.0f)
	}
};


Vertex vertices2[] =
{
	Vertex
	{
		glm::vec3(-IDK2, 0.0f, IDK2),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec2(0.0f, 0.0f)
	},
	Vertex
	{
		glm::vec3(-IDK2, 0.0f, -IDK2),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec2(0.0f, IDK2)
	},
	Vertex
	{
		glm::vec3(IDK2, 0.0f, -IDK2),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec2(IDK2, IDK2)
	},
	Vertex
	{
		glm::vec3(IDK2, 0.0f,  IDK2),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec2(IDK2, 0.0f)
	},

	Vertex
	{
		glm::vec3(-IDK2, 2 * IDK2, IDK2),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec2(0.0f, 0.0f)
	},
	Vertex
	{
		glm::vec3(-IDK2, 2 * IDK2, -IDK2),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec2(0.0f, IDK2)
	},
	Vertex
	{
		glm::vec3(IDK2, 2 * IDK2, -IDK2),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec2(IDK2, IDK2)
	},
	Vertex
	{
		glm::vec3(IDK2, 2 * IDK2,  IDK2),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec2(IDK2, 0.0f)
	}
};

GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	4, 0, 1,
	4, 1, 5,
	4, 0, 3,
	4, 3, 7,
	5, 1, 2,
	5, 2, 6,
	6, 2, 3,
	6, 3, 7,
	4, 5, 6,
	4, 6, 7,

};

int main() {
	// intiazling GLFW
	glfwInit();

	// telling GLFW the version of OpenGL we are using, for us -> 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// telling GLFW the profile of OpenGL
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create non-fullscreen 800x800
	GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, "Graphics Engine", NULL, NULL);

	// error checking window creation
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// introducing window to current context, IDK why
	glfwMakeContextCurrent(window);

	// loading GLAD
	gladLoadGL();

	// specifing viewport size of OpenGL in the window
	glViewport(0, 0, winWidth, winHeight);

	// meshes
	Texture textures[]
	{
		Texture("D:\\Manbir\\Programming\\Learning\\Graphics Engine\\floor.jpg", "diffuse", 0),
		Texture("D:\\Manbir\\Programming\\Learning\\Graphics Engine\\floor__spec.jpg", "specular", 1),
		Texture("D:\\Manbir\\Programming\\Learning\\Graphics Engine\\floor__height.jpg", "height", 2)
	};

	Shader shaderProgram("default.vert", "default.frag");

	std::vector <Vertex> cubeVertices(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> cubeIndices(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> cubeTextures(textures, textures + sizeof(textures) / sizeof(Texture));

	Mesh cube(cubeVertices, cubeIndices, cubeTextures);

	glm::vec3 cubePos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 cubeModelMat = glm::mat4(1.0f);

	cubeModelMat = glm::translate(cubeModelMat, cubePos);

	// shader programm
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "globalMat"), 1, GL_FALSE, glm::value_ptr(cubeModelMat));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), 1, 1, 1, 1);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), 0.5, 0.5, 0.5);
	
	// setting up free type
	FT_Library  library;
	FT_Face face;

	FT_Error ftError;

	ftError = FT_Init_FreeType(&library);
	if (ftError)
	{
		std::cout << "[ERROR] An error occured while loading FreeType library:" << std::endl;
		std::cout << ftError << std::endl;
	}
	else {
		std::cout << "[DEBUG] FreeType library loaded succesfully." << std::endl;
	}

	ftError = FT_New_Face(
		library,
		"roboto.ttf",
		0,
		&face
	);
	if (ftError == FT_Err_Unknown_File_Format)
	{
		std::cout << "[ERROR] The file format for loading font face not supported." << std::endl;
	}
	else if (ftError)
	{
		std::cout << "[ERROR] An error occured while loading FreeType font face:" << std::endl;
		std::cout << ftError << std::endl;
	}
	else {
		std::cout << "[DEBUG] FreeType font face loaded succesfully." << std::endl;
	}

	ftError = FT_Set_Pixel_Sizes(
		face,   
		0,      
		16
	);

	FT_UInt glyph_index = FT_Get_Char_Index(face, 'a');

	ftError = FT_Load_Glyph(
		face,          
		glyph_index,   
		FT_LOAD_DEFAULT
	);
	ftError = FT_Render_Glyph(
		face->glyph,
		FT_RENDER_MODE_NORMAL
	);


	// enabling depth
	glEnable(GL_DEPTH_TEST);

	// declaring the camera
	Camera camera(winWidth, winHeight, glm::vec3(0.0f, 0.0f, 2.0f));

	// main while loop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// camera things
		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		// controls
		glm::vec3 floorTranslation(0.0f);

		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			floorTranslation.x += 0.1f;
		} if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			floorTranslation.x -= 0.1f;
		} if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			floorTranslation.z += 0.1f;
		} if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			floorTranslation.z -= 0.1f;
		}

		cube.Move(floorTranslation);

		// rendering
		cube.Render(shaderProgram, camera);
		
		// rendering text
		/*
			GLuint texName;

			glGenTextures(5, &texName);
			glBindTexture(GL_TEXTURE_2D, texName);

			glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_FALSE);
			glPixelStorei(GL_UNPACK_LSB_FIRST, GL_FALSE);
			glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);   // could also be set to image size, but this is used only
			glPixelStorei(GL_UNPACK_IMAGE_HEIGHT, 0); // if one wants to load only a subset of the image
			glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
			glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
			glPixelStorei(GL_UNPACK_SKIP_IMAGES, 0);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // that one's pretty important. For TrueColor DIBs the alignment is 4

			glTexImage2D(
				GL_TEXTURE_2D, 
				0, 
				GL_RGBA,
				face->glyph->bitmap.width, 
				face->glyph->bitmap.rows,
				0,
				GL_RGBA, 
				GL_UNSIGNED_INT_8_8_8_8, 
				face->glyph->bitmap.buffer
			);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			glBindTexture(GL_TEXTURE_2D, 0
		*/

		// swaping buffers of the window
		glfwSwapBuffers(window);

		// checking for events, important to do or will stop responding
		glfwPollEvents();
	}

	// destroying the window and terminating the GLFW process
	glfwDestroyWindow(window);
	glfwTerminate();

	// returing 0 as an indicator of succefull execution
	return 0;
}