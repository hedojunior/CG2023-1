/* Hello Triangle - código adaptado de https://learnopengl.com/#!Getting-started/Hello-Triangle
 *
 * Adaptado por Rossana Baptista Queiroz
 * para a disciplina de Processamento Gráfico/Computação Gráfica - Unisinos
 * Versão inicial: 7/4/2017
 * Última atualização em 20/04/2023
 *
 */

#include <iostream>
#include <string>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// GLAD
#include <glad/glad.h>

// GLFW
#include <GLFW/glfw3.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

#include "Mesh.h"


struct Vertex
{
	glm::vec3 position;
	glm::vec3 v_color;
};

void configureMesh(Mesh* mesh, int width, int height);
void updateObjectSelection();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
int loadSimpleObj(string filePath, int& nVertices, glm::vec3 color = glm::vec3(1.0,0.0,0.0));

const GLuint WIDTH = 1000, HEIGHT = 1000;

int selectedObjectIndex = -1;

glm::vec3 cameraPos = glm::vec3(0.0, 0.0, 3.0);
glm::vec3 cameraFront = glm::vec3(0.0, 0.0, -1.0);
glm::vec3 cameraUp = glm::vec3(0.0, 1.0, 0.0);
GLint viewLoc;

float cameraSpeed = 0.15;
float fov = 50.0f;

bool firstMouse = true;
float lastX = 0.0, lastY = 0.0;
float yaw = -90.0, pitch = 0.0;

vector<string> objFilePaths;
vector<Mesh*> objects;
vector<Shader*> shaders;

void main()
{
	string path = "";
	
	do
	{
		std::cout << "Provide a .obj file path or press enter to run program.\n" << std::endl;
		std::getline(std::cin, path);
		
		if (path.length() > 0)
		{
			objFilePaths.push_back(path);
		}
		
	} while (path.length() != 0);

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Trabalho GA", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	glfwSetCursorPos(window, WIDTH / 2, HEIGHT / 2);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	int nVertices;
	glm::vec3 redColor = glm::vec3(1.0, 0.0, 0.0);
	float startingX = 0.0;
	GLuint VAO;

	for (string path : objFilePaths)
	{
		Mesh * mesh = new Mesh();

		Shader * shader = new Shader("light_vertex_shader.vs", "light_fragment_shader.fs");

		shader->use();

		shader->setFloat("ka", 0.4);
		shader->setFloat("kd", 0.5);
		shader->setFloat("ks", 0.5);
		shader->setFloat("q", 10);

		shader->setVec3("lightPos", -2.0f, 10.0f, 3.0f);
		shader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);

		shader->setVec3("selectedColor", 0.0f, 0.0f, 1.0f);
		shader->setBool("isSelected", false);
	
		VAO = loadSimpleObj(path, nVertices, redColor);
		mesh->initialize(VAO, nVertices, shader, glm::vec3(startingX, 0.0, 0.0));
		configureMesh(mesh, width, height);

		objects.push_back(mesh);
		shaders.push_back(shader);

		startingX += 3.0;
	}

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLineWidth(10);
		glPointSize(20);

		for (Mesh * object : objects)
		{
			glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
			object->setView(view);

			object->updatePosition(cameraPos);
			object->update();
			object->draw();
		}

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glfwTerminate();
	return;
}

void configureMesh(Mesh* mesh, int width, int height)
{
	glm::mat4 model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	mesh->setModel(model);

	glm::mat4 view = glm::lookAt(glm::vec3(0.0, 0.0, 3.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	mesh->setView(view);

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	mesh->setProjection(projection);
}

void updateObjectSelection()
{

	if (objects.size() == 1)
	{
		objects[0]->select();
		return;
	}

	if (selectedObjectIndex + 1 == objects.size()) 
	{
		selectedObjectIndex = 0;
	}
	else
	{
		selectedObjectIndex++;
	}

	int previousIndex = selectedObjectIndex == 0 ? objects.size() - 1 : selectedObjectIndex - 1;
	objects[selectedObjectIndex]->select();
	objects[previousIndex]->deselect();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// Exit
	
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	// Rotation

	if (key == GLFW_KEY_X && action == GLFW_PRESS && selectedObjectIndex != -1)
	{
		objects[selectedObjectIndex]->setRotating(glm::vec3(1.0f, 0.0f, 0.0f));
	}

	if (key == GLFW_KEY_Y && action == GLFW_PRESS && selectedObjectIndex != -1)
	{
		objects[selectedObjectIndex]->setRotating(glm::vec3(0.0f, 1.0f, 0.0f));
	}

	if (key == GLFW_KEY_Z && action == GLFW_PRESS && selectedObjectIndex != -1)
	{
		objects[selectedObjectIndex]->setRotating(glm::vec3(0.0f, 0.0f, 1.0f));
	}

	// Camera

	if (key == GLFW_KEY_W)
	{
		cameraPos += cameraSpeed * cameraFront;
	}

	if (key == GLFW_KEY_S)
	{
		cameraPos -= cameraSpeed * cameraFront;
	}

	if (key == GLFW_KEY_A)
	{
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}

	if (key == GLFW_KEY_D)
	{
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}

	// Selection

	if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
	{
		updateObjectSelection();
	}

	// Scale

	if (key == GLFW_KEY_1 && action == GLFW_PRESS && selectedObjectIndex != -1)
	{
		objects[selectedObjectIndex]->setScale(-0.2f);
	}

	if (key == GLFW_KEY_2 && action == GLFW_PRESS && selectedObjectIndex != -1)
	{
		objects[selectedObjectIndex]->setScale(0.2f);
	}

	// Translate

	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS && selectedObjectIndex != -1)
	{
		objects[selectedObjectIndex]->translate(0.2, 0, 0, 0);
	}

	if (key == GLFW_KEY_UP && action == GLFW_PRESS && selectedObjectIndex != -1)
	{
		objects[selectedObjectIndex]->translate(0, 0.2, 0, 0);
	}

	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS && selectedObjectIndex != -1)
	{
		objects[selectedObjectIndex]->translate(0, 0, 0.2, 0);
	}

	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS && selectedObjectIndex != -1)
	{
		objects[selectedObjectIndex]->translate(0, 0, 0, 0.2);
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float offsetx = xpos - lastX;
	float offsety = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	offsetx *= cameraSpeed;
	offsety *= cameraSpeed;

	pitch += offsety;
	yaw += offsetx;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);

}

int loadSimpleObj(string filePath, int& nVertices, glm::vec3 color)
{
	ifstream inputFile;
	inputFile.open(filePath);
	vector <GLfloat> vertbuffer;

	vector <Vertex> vertices;
	vector <int> indices;
	vector <glm::vec3> normals;
	vector <glm::vec2> texCoord;

	if (inputFile.is_open())
	{
		char line[100];
		string sline;
		

		while (!inputFile.eof())
		{
			inputFile.getline(line, 100);
			sline = line;

			string word;
			istringstream ssline(sline);

			ssline >> word;

			if (word == "v")
			{
				Vertex v;
				ssline >> v.position.x >> v.position.y >> v.position.z;
				v.v_color.r = color.r; v.v_color.g = color.g; v.v_color.b = color.b;
				vertices.push_back(v);
			}
			if (word == "vt")
			{
				glm::vec2 vt;
				ssline >> vt.s >> vt.t;
				texCoord.push_back(vt);
			}
			if (word == "vn")
			{
				glm::vec3 vn;
				ssline >> vn.x >> vn.y >> vn.z;
				normals.push_back(vn);
			}
			else if (word == "f")
			{
				string tokens[3];
				for (int i = 0; i < 3; i++)
				{
					ssline >> tokens[i];
					int pos = tokens[i].find("/");
					string token = tokens[i].substr(0, pos);
					int index = atoi(token.c_str()) - 1;
					indices.push_back(index);
					vertbuffer.push_back(vertices[index].position.x);
					vertbuffer.push_back(vertices[index].position.y);
					vertbuffer.push_back(vertices[index].position.z);
					vertbuffer.push_back(vertices[index].v_color.r);
					vertbuffer.push_back(vertices[index].v_color.g);
					vertbuffer.push_back(vertices[index].v_color.b);

					tokens[i] = tokens[i].substr(pos + 1);
					pos = tokens[i].find("/");
					token = tokens[i].substr(0, pos);
					int indexT = atoi(token.c_str()) - 1;

					vertbuffer.push_back(texCoord[indexT].s);
					vertbuffer.push_back(texCoord[indexT].t);

					tokens[i] = tokens[i].substr(pos + 1);
					token = tokens[i].substr(0, pos);
					int indexN = atoi(token.c_str()) - 1;

					vertbuffer.push_back(normals[indexN].x);
					vertbuffer.push_back(normals[indexN].y);
					vertbuffer.push_back(normals[indexN].z);
					
				}
			
			}

		}

		inputFile.close();
	}
	else
	{
		cout << "Não foi possivel abrir o arquivo " << filePath << endl;
	}


	nVertices = vertbuffer.size() / 11;

	GLuint VBO, VAO;

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertbuffer.size() * sizeof(GLfloat), vertbuffer.data(), GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(8 * sizeof(GLfloat)));
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	return VAO;

}

