#include "Shader.h"

// get text from plain text file
std::string get_file_contents(const char* filename) {
	std::ifstream in(filename, std::ios::binary);

	if (in) {
		std::string contents;

		in.seekg(0, std::ios::end);

		contents.resize(in.tellg());

		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());

		in.close();
		
		std::cout << filename << std::endl;

		return contents;
	}

	throw (errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// getting vertex and fragment shader source code
	std::string vertexStr = get_file_contents(vertexFile);
	std::string fragmentStr = get_file_contents(fragmentFile);

	// converting vertex and fragment shader to c-strings (required by libs we use)
	const char* vertexSrc = vertexStr.c_str();
	const char* fragmentSrc = fragmentStr.c_str();

	// creating vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexSrc, NULL);
	glCompileShader(vertexShader);

	checkErrors(vertexShader, "VERTEX");

	// creating fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentSrc, NULL);
	glCompileShader(fragmentShader);

	checkErrors(vertexShader, "FRAGMENT");

	// creating shader program object (rendering pipeline)
	ID = glCreateProgram();

	glAttachShader(ID, vertexShader);  			// attaching vertex shader
	glAttachShader(ID, fragmentShader);  		// attaching fragment shader
	glLinkProgram(ID);  						// link the shaders together

	// checking for errors in shader program
	checkErrors(ID, "PROGRAM");

	// deleting shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}

// TODO: Verify
void Shader::checkErrors(unsigned int shader, const char* type) 
{
	GLint hasCompiled;

	char infoLog[1024];

	// if given object is program
	if (type != "PROGRAM") 
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);

		// checking if it compiled successfully
		if (hasCompiled == GL_FALSE) 
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for: " << type << "\n" << std::endl;
		}
	}
	// if given object is a shader
	else 
	{
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);

		// checking if it compiled successfully
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for: " << type << "\n" << std::endl;
		}
	}
}
