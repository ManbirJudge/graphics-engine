#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &(VAO::ID));
}

void VAO::LinkAtrib(
	VBO& VBO, 
	GLuint layout,
	GLuint numComponents, 
	GLenum type, 
	GLsizeiptr stride, 
	void* offset
)
{
	VBO.Bind();

	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);

	VBO.Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(VAO::ID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &(VAO::ID));
}
