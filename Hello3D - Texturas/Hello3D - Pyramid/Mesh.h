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
	void initialize(GLuint VAO, int nVertices, Shader *shader, GLuint texID, float ka, float ks, float kd); 
	void update();
	void draw();

protected:
	GLuint VAO; //Identificador do buffer Vertex Array Object
	int nVertices;
	Shader* shader;
	GLuint texID;
	float ka, ks, kd;
};

