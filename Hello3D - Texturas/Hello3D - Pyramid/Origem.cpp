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

#include "Object.h"

#include "SceneConfig.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 v_color;
};

// Protótipo da função de callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// Dimensões da janela (pode ser alterado em tempo de execução)
const GLuint WIDTH = 1000, HEIGHT = 1000;

bool rotateX = false, rotateY = false, rotateZ = false;

glm::vec3 cameraPos, cameraFront, cameraUp;
GLint viewloc;
float cameraSpeed = 0.15;
float fov = 50.0f;

bool firstMouse = true;
float lastX = 0.0, lastY = 0.0;
float yaw = -90.0, pitch = 0.0;

int selectedObjectIndex = -1;

string configFilePath;
vector<Object*> objects;
vector<Shader*> shaders;

int main()
{
	std::string xmlFile;
	std::cout << "Insira o caminho do arquivo XML: ";
	std::cin >> xmlFile;

	SceneConfig sceneConfig = SceneConfig();
	sceneConfig.parseXML(xmlFile);

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Trabalho GB", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPos(window, WIDTH / 2, HEIGHT / 2);
	glfwSetCursorPosCallback(window, mouse_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	cameraPos = sceneConfig.cameraPos;
	cameraUp = sceneConfig.cameraUp;
	cameraFront = sceneConfig.cameraFront;

	for (ObjectConfig object : sceneConfig.objects)
	{
		Object * obj = new Object();
		Shader * shader = new Shader("vertex.vs", "fragment.fs");
		shader->use();

		shader->setFloat("ka", object.ka);
		shader->setFloat("kd", object.kd);
		shader->setFloat("ks", object.ks);
		shader->setFloat("q", object.q);

		shader->setVec3("lightPos", sceneConfig.lightPos.x, sceneConfig.lightPos.y, sceneConfig.lightPos.z);

		shader->setVec3("lightColor", sceneConfig.lightColor.x, sceneConfig.lightColor.y, sceneConfig.lightColor.z);

		obj->initialize(object.objFile, object.textureFiles, shader, object.ka, object.initialTranslation, object.initialScale, object.initialRotation);

		glm::mat4 model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		obj->setModel(model);

		glm::mat4 view = glm::lookAt(glm::vec3(0.0, 0.0, 3.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
		obj->setView(view);

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
		obj->setProjection(projection);

		objects.push_back(obj);

		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(shader->ID, "colorBuffer"), 0);
	}

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //cor de fundo
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLineWidth(10);
		glPointSize(20);

		for (Object * obj : objects)
		{
			glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
			obj->setView(view);

			obj->updatePosition(cameraPos);
			obj->update();
			obj->draw();
		}

		glfwSwapBuffers(window);
	}
	
	glfwTerminate();
	return 0;
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
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	// Rotation

	if (key == GLFW_KEY_X && selectedObjectIndex != -1)
	{
		objects[selectedObjectIndex]->setRotating(glm::vec3(1.0f, 0.0f, 0.0f), (GLfloat)glfwGetTime());
	}

	if (key == GLFW_KEY_Y && selectedObjectIndex != -1)
	{
		objects[selectedObjectIndex]->setRotating(glm::vec3(0.0f, 1.0f, 0.0f), (GLfloat)glfwGetTime());
	}

	if (key == GLFW_KEY_Z && selectedObjectIndex != -1)
	{
		objects[selectedObjectIndex]->setRotating(glm::vec3(0.0f, 0.0f, 1.0f), (GLfloat)glfwGetTime());
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
