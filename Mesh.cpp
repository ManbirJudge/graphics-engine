#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures)
{
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	// bind vertex array object to modify it
	Mesh::VAO.Bind();

	// vertex buffer object and element buffer object
	VBO VBO(vertices);
	EBO EBO(indices);

	// linking VAO to VBO
	VAO.LinkAtrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)(0 * sizeof(float)));  // layout 0 -> position
	VAO.LinkAtrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));  // layout 1 -> normal
	VAO.LinkAtrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));  // layout 2 -> color
	VAO.LinkAtrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));  // layout 3 -> texture coordinates

	// unbinding all to prevent modifying them
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}

void Mesh::Move(glm::vec3 translation) {
	Mesh::position = Mesh::position + translation;
}

void Mesh::Render(
	Shader& shader,
	Camera& camera

	// glm::mat4 matrix,
	// glm::vec3 translation,
	// glm::quat rotation,
	// glm::vec3 scale
)
{
	shader.Activate();
	VAO.Bind();

	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;
	unsigned int numNormal = 0;
	
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
		else if(type == "normal")
		{
			num = std::to_string(numNormal++);
		}

		textures[i].texSlot(shader, (type + num).c_str());
		textures[i].Bind();
	}

	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMat");

	glm::mat4 translationMat = glm::translate(glm::mat4(1.0f), Mesh::position);
	glm::mat4 rotationMat = glm::rotate(glm::mat4(1.f), Mesh::rotation.x, glm::vec3(1.f, 0.f, 0.f));
	rotationMat = glm::rotate(rotationMat, Mesh::rotation.y, glm::vec3(0.f, 1.f, 0.f));
	rotationMat = glm::rotate(rotationMat, Mesh::rotation.z, glm::vec3(0.f, 0.f, 1.f));
	glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), Mesh::scale);

	// translationMat = glm::translate(translationMat, Mesh::position);
	// rotationMat = glm::mat4_cast(rotation);
	// scaleMat = glm::scale(scaleMat, scale);

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "modelTranslationMat"), 1, GL_FALSE, glm::value_ptr(translationMat));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "modelRotationMat"), 1, GL_FALSE, glm::value_ptr(rotationMat));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "modelScaleMat"), 1, GL_FALSE, glm::value_ptr(scaleMat));

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}