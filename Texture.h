#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "Shader.h"

class Texture
{
public:
	GLuint ID;
	const char* type;
	GLuint slot;

	Texture(const char* imgPath, const char* texType, GLuint slot);

	void texSlot(Shader& shader, const char* uniform);

	void Bind();
	void Unbind();
	void Delete();
};

#endif