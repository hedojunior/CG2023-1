#pragma once

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

class Mesh
{
public:
	Mesh() {}
	~Mesh() {}
	void initialize(GLuint VAO, int nVertices, Shader *shader, glm::vec3 position = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1), float angle = 0.0, glm::vec3 axis = glm::vec3(0.0, 0.0, 1.0)); 
	void select();
	void deselect();
	void updatePosition(glm::vec3 pos);
	void setModel(glm::mat4 model);
	void setView(glm::mat4 view);
	void setProjection(glm::mat4 projection);

	void setRotating(glm::vec3 axis);

	void setScale(float value);

	void translate(float left, float top, float right, float down);

	void update();
	void draw();

protected:
	GLuint VAO; //Identificador do buffer Vertex Array Object
	int nVertices;
	//Atributos que armazenam informações para aplicar as transforms no objeto
	glm::vec3 position;
	glm::vec3 axis;
	bool isRotating;
	glm::vec3 scale;
	glm::mat4 model, view, projection;

	Shader* shader;

};

