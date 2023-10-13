#include "Texture.h"

Texture::Texture(const char* imgPath, const char* texType, GLuint slot)
{
	type = texType;
	Texture::slot = slot;

	// variables for image width, height and number of color channels
	int widthImg, heightImg, numColorCh;

	// loading the image using stbi
	stbi_set_flip_vertically_on_load(true);
	unsigned char* pixels = stbi_load(imgPath, &widthImg, &heightImg, &numColorCh, 0);
	
	// setting the texture up
	glGenTextures(1, &ID);  // generating the texture
	glActiveTexture(GL_TEXTURE0 + Texture::slot);  // activating the texture in the intended slot
	glBindTexture(GL_TEXTURE_2D, ID);  // binding the texture to modify it

	// setting texture paramters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  // to pixelate when scalled up
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  // to pixelate when scalled up

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  // to repeat the image
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  // to repeat the image

	if (numColorCh == 4)
	{
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			widthImg,
			heightImg,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			pixels
		);
	}
	else if (numColorCh == 3)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			widthImg,
			heightImg,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			pixels
		);
	}
	else if (numColorCh == 1)
	{
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			widthImg,
			heightImg,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			pixels
		);
	}

	glGenerateMipmap(GL_TEXTURE_2D);  // creating mipmap for the texture

	stbi_image_free(pixels);  // relaesing the loaded image from memory
	glBindTexture(GL_TEXTURE_2D, 0);  // unbinding the texture to prevent modifying it
}

void Texture::texSlot(Shader& shader, const char* uniform)
{
	shader.Activate(); // activiting the shader
	glUniform1i(glGetUniformLocation(shader.ID, uniform), Texture::slot);  // setting the image to the uniform
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + Texture::slot);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}