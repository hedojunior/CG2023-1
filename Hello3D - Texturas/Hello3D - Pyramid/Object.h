#pragma once
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <stb_image.h>

#include <vector>

#include "Mesh.h"

#include <GLFW/glfw3.h>

using namespace std;
using namespace glm;

class Object
{
public:
	Object() {}
	~Object(){}
	void initialize(
		string filePath,
		Shader* shader,
		vec3 position = vec3(0.0f),
		vec3 scale = vec3(1),
		vec3 rotation = vec3(0.0, 0.0, 1.0),
		float angle = radians(90.0f)
	);

	void select();
	void deselect();
	
	void setModel(mat4 model);
	void setView(mat4 view);
	void setProjection(mat4 projection);
	void updatePosition(vec3 pos);

	void setRotating(vec3 axis, float angle);

	void setScale(float value);

	void translate(float left, float top, float right, float down);

	void update();
	void draw();
protected:
	void loadObj(string filePath);
	int generateTexture(string filePath);
	GLuint generateVAO(vector <GLfloat> vertbuffer, int& nVertices);
	vector <Mesh*> grupos;
	//Atributos que armazenam informações para aplicar as transforms no objeto
	vec3 position;
	float angle;
	vec3 rotation;
	vec3 scale;
	bool isRotating;
	mat4 model, view, projection;
	Shader* shader;

};

