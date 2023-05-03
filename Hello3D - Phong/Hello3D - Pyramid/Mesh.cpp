#include "Mesh.h"

void Mesh::initialize(GLuint VAO, int nVertices, Shader* shader, glm::vec3 position, glm::vec3 scale, float angle, glm::vec3 axis)
{
	this->VAO = VAO;
	this->nVertices = nVertices;
	this->shader = shader;
	this->position = position;
	this->scale = scale;
	this->axis = axis;
	
}

void Mesh::select()
{
	shader->use();
	shader->setBool("isSelected", true);
}

void Mesh::deselect()
{
	shader->use();
	shader->setBool("isSelected", false);
}

void Mesh::updatePosition(glm::vec3 pos)
{
	shader->use();
	shader->setVec3("cameraPos", pos.x, pos.y, pos.z);
}

void Mesh::setModel(glm::mat4 model)
{
	shader->use();
	this->model = model;
	
	glUniformMatrix4fv(glGetUniformLocation(shader->ID, "model"), 1, FALSE, glm::value_ptr(model));
}

void Mesh::setProjection(glm::mat4 projection)
{
	shader->use();
	this->projection = projection;
	glUniformMatrix4fv(glGetUniformLocation(shader->ID, "projection"), 1, FALSE, glm::value_ptr(projection));
}

void Mesh::setView(glm::mat4 view)
{
	shader->use();
	this->view = view;
	glUniformMatrix4fv(glGetUniformLocation(shader->ID, "view"), 1, FALSE, glm::value_ptr(view));
}

void Mesh::setRotating(glm::vec3 axis)
{
	shader->use();
	this->axis = axis;
	this->isRotating = true;
}

void Mesh::setScale(float value)
{
	float nextScale = this->scale.x + value;

	if (nextScale < 0.1f) 
		return;

	glm::vec3 scale = glm::vec3(nextScale);
	this->scale = scale;
}

void Mesh::translate(float left, float top, float right, float down)
{
	if (left > 0)
	{
		position = glm::vec3(position.x - left, position.y, position.z);
	}
	else if (top > 0)
	{
		position = glm::vec3(position.x, position.y + top, position.z);
	}
	else if (right > 0)
	{
		position = glm::vec3(position.x + right, position.y, position.z);
	}
	else if (down > 0)
	{
		position = glm::vec3(position.x, position.y - down, position.z);
	}
}

void Mesh::update()
{
	shader->use();
	glm::mat4 model = glm::mat4(1); //matriz identidade
	model = glm::translate(model, position);

	if (isRotating)
	{
		float angle = (GLfloat)glfwGetTime();
		model = glm::rotate(model, angle, axis);
	}

	model = glm::scale(model, scale);
	shader->setMat4("model", glm::value_ptr(model));
}

void Mesh::draw()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, nVertices);
	glBindVertexArray(0);
}
