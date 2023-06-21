#pragma once

#include <stb_image.h>

#include <vector>

#include "Mesh.h"

#include <GLFW/glfw3.h>

using namespace std;

class Object
{
public:
	Object() {}
	~Object(){}
	void initialize(
		string filePath,
		vector<string> texturePaths,
		Shader* shader,
		float ka,
		glm::vec3 position = glm::vec3(0.0f),
		glm::vec3 scale = glm::vec3(1),
		glm::vec3 rotation = glm::vec3(0.0, 0.0, 1.0),
		float angle = glm::radians(90.0f)
	);

	void select();
	void deselect();
	
	void setModel(glm::mat4 model);
	void setView(glm::mat4 view);
	void setProjection(glm::mat4 projection);
	void updatePosition(glm::vec3 pos);

	void setRotating(glm::vec3 axis, float angle);

	void setScale(float value);

	void translate(float left, float top, float right, float down);

	void update();
	void draw();
protected:
	void loadObj(string filePath, vector<string> texturePaths);
	int generateTexture(string filePath);
	GLuint generateVAO(vector <GLfloat> vertbuffer, int& nVertices);
	vector <Mesh*> grupos;
	//Atributos que armazenam informações para aplicar as transforms no objeto
	glm::vec3 position;
	float angle;
	float ka;
	glm::vec3 rotation;
	glm::vec3 scale;
	bool isRotating;
	glm::mat4 model, view, projection;
	Shader* shader;

};

