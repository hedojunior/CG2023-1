#include "Mesh.h"

void Mesh::initialize(GLuint VAO, int nVertices, Shader* shader, GLuint texID, float ka, float ks, float kd)
{
	this->VAO = VAO;
	this->nVertices = nVertices;
	this->shader = shader;
	this->texID = texID;
	this->ka = ka;
	this->ks = ks;
	this->kd = kd;
}

void Mesh::update()
{
	
}

void Mesh::draw()
{
	shader->setFloat("ka", ka);
	shader->setFloat("ks", ks);
	shader->setFloat("kd", kd);

	glBindTexture(GL_TEXTURE_2D, texID);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, nVertices);
	glBindVertexArray(0);
}
