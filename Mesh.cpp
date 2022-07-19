#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures)
{
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	Mesh::VAO.Bind();

	// vertex buffer object and element buffer object (for normal objects)
	VBO VBO(vertices);
	EBO EBO(indices);

	// linking VAO to VBO (for normal objects)
	VAO.LinkAtrrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)(0 * sizeof(float)));  // layout 0 -> position
	VAO.LinkAtrrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));  // layout 1 -> normal
	VAO.LinkAtrrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));  // layout 2 -> color
	VAO.LinkAtrrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));  // layout 3 -> texture coordinates

	// unbinding all to prevent modifying them
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}

void Mesh::Move(glm::vec3 tranlsation) {
	Mesh::position = Mesh::position + tranlsation;
}

void Mesh::Render(
	Shader& shader,
	Camera& camera

	// glm::mat4 matrix,
	// glm::vec3 tranlsation,
	// glm::quat rotation,
	// glm::vec3 scale
)
{
	shader.Activate();
	VAO.Bind();

	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;
	unsigned int numHeight = 0;
	
	for (size_t i{ 0 }; i < textures.size(); i++) 
	{
		std::string num;
		std::string type = textures[i].type;

		if (type == "diffuse") 
		{
			num = std::to_string(numDiffuse++);
		}
		else if(type == "specular")
		{
			num = std::to_string(numSpecular++);
		}
		else if(type == "height")
		{
			num = std::to_string(numHeight++);
		}

		textures[i].texSlot(shader, (type + num).c_str());
		textures[i].Bind();
	}

	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMat");

	glm::mat4 translationMat = glm::mat4(1.0f);
	glm::mat4 rotationMat = glm::mat4(1.0f);
	glm::mat4 scaleMat = glm::mat4(1.0f);

	translationMat = glm::translate(translationMat, Mesh::position);
	// rotationMat = glm::mat4_cast(rotation);
	// scaleMat = glm::scale(scaleMat, scale);

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "modelTranslationMat"), 1, GL_FALSE, glm::value_ptr(translationMat));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "modelRotationMat"), 1, GL_FALSE, glm::value_ptr(rotationMat));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "modelScaleMat"), 1, GL_FALSE, glm::value_ptr(scaleMat));

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}