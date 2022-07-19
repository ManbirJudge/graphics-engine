#include "Shader.h"

// general function to get contents of a plain text file
std::string get_file_contents(const char* filename) {
	std::ifstream in(filename, std::ios::binary);

	if (in) {
		std::string contents;

		in.seekg(0, std::ios::end);

		contents.resize(in.tellg());

		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());

		in.close();

		return (contents);
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

	// creating vertex shader object
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexSrc, NULL);
	glCompileShader(vertexShader);

	// checking for compile errors in vertex shader
	compileErrors(vertexShader, "VERTEX");

	// creating fagment shader object
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentSrc, NULL);
	glCompileShader(fragmentShader);

	// checking for compile errors in fragment shader
	compileErrors(vertexShader, "FRAGMENT");

	// creating shader program object (sort of rendering pipeline)
	ID = glCreateProgram();

	glAttachShader(ID, vertexShader);  // attaching vertex shader to shader program
	glAttachShader(ID, fragmentShader);  // attaching fragment shader to shader program
	glLinkProgram(ID);  // link all the shaders togther into shader program

	// checking for compile errors in shader program
	compileErrors(ID, "PROGRAM");

	// deleting vertex and fragment shaders becuase they are useless now as they are present in shader program
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
void Shader::compileErrors(unsigned int shader, const char* type) 
{
	GLint hasCompiled;

	char infoLog[1024];

	// if given object is program
	if (type != "PROGRAM") 
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);

		// checking if it compiled succesfully
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

		// checking if it compiled succesfully
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for: " << type << "\n" << std::endl;
		}
	}
}
