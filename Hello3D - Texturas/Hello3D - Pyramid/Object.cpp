#include "Object.h"

#include <GLFW/glfw3.h>

void Object::initialize(string filePath, vector<string> texturePaths, Shader* shader, float ka, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, float angle)
{
	this->position = position;
	this->scale = scale;
	this->angle = angle;
	this->ka = ka;
	this->rotation = rotation;
	this->shader = shader;
	
	loadObj(filePath, texturePaths);
}

void Object::select()
{
	shader->use();
	shader->setFloat("ka", ka * 1.5);
}

void Object::deselect()
{
	shader->use();
	shader->setFloat("ka", ka);
}

void Object::setModel(glm::mat4 pos)
{
	shader->use();
	this->model = model;

	glUniformMatrix4fv(glGetUniformLocation(shader->ID, "model"), 1, FALSE, glm::value_ptr(model));
}

void Object::setView(glm::mat4 view)
{
	shader->use();
	this->view = view;
	glUniformMatrix4fv(glGetUniformLocation(shader->ID, "view"), 1, FALSE, glm::value_ptr(view));
}

void Object::setProjection(glm::mat4 projection)
{
	shader->use();
	this->projection = projection;
	glUniformMatrix4fv(glGetUniformLocation(shader->ID, "projection"), 1, FALSE, glm::value_ptr(projection));
}

void Object::setRotating(glm::vec3 axis, float angle)
{
	if (axis.x > 0)
	{
		rotation.x = rotation.x + axis.x;
	}

	if (axis.y > 0)
	{
		rotation.y = rotation.y + axis.y;
	}

	if (axis.z = 0)
	{
		rotation.z = rotation.z + axis.z;
	}

	this->angle = angle;
}

void Object::setScale(float value)
{
	float nextScale = this->scale.x + value;

	if (nextScale < 0.1f)
		return;

	glm::vec3 scale = glm::vec3(nextScale);
	this->scale = scale;
}

void Object::translate(float left, float top, float right, float down)
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
	
void Object::updatePosition(glm::vec3 pos)
{
	shader->use();
	shader->setVec3("cameraPos", pos.x, pos.y, pos.z);
}

void Object::update()
{
	shader->use();
	glm::mat4 model = glm::mat4(1); //matriz identidade
	
	model = glm::translate(model, position);
	model = glm::rotate(model, angle, rotation);
	model = glm::scale(model, scale);

	shader->setMat4("model", glm::value_ptr(model));
}

void Object::draw()
{
	for (int i = 0; i < grupos.size(); i++)
	{
		grupos[i]->draw();
	}
}

void Object::loadObj(string filePath, vector<string> texturePaths)
{
	int iTexture = 0;

	ifstream inputFile;
	inputFile.open(filePath);
	vector <GLfloat> vertbuffer;

	vector <glm::vec3> vertices, colors;
	vector <glm::vec3> normals;
	vector <glm::vec2> texCoord;

	bool initializeGroup = true;

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

			if (initializeGroup)
			{
				
			}

			if (word == "v" || inputFile.eof())
			{
				
				if (initializeGroup)
				{
					

					if (vertbuffer.size())
					{
						initializeGroup = false;
						Mesh * m = new Mesh();
						int nVertices;
						GLuint VAO = generateVAO(vertbuffer, nVertices);
						GLuint texID = generateTexture(texturePaths[iTexture]);
						iTexture++;
						m->initialize(VAO, nVertices, shader, texID);
						grupos.push_back(m);

						//vertices.clear();
						//colors.clear();
						//normals.clear();
						//texCoord.clear();
						vertbuffer.clear();
					}

				}
				glm::vec3 v, color;
				ssline >> v.x >> v.y >> v.z;
				color.r = 1.0; color.g = 0.0; color.b = 0.0;
				vertices.push_back(v);
				colors.push_back(color);
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

			if (word == "g") //início de um novo grupo
			{
				initializeGroup = true;
			}
			if (word == "f")
			{
				string tokens[3];
				for (int i = 0; i < 3; i++)
				{
					ssline >> tokens[i];
					int pos = tokens[i].find("/");
					string token = tokens[i].substr(0, pos);
					int index = atoi(token.c_str()) - 1;
					
					vertbuffer.push_back(vertices[index].x);
					vertbuffer.push_back(vertices[index].y);
					vertbuffer.push_back(vertices[index].z);
					vertbuffer.push_back(colors[index].r);
					vertbuffer.push_back(colors[index].g);
					vertbuffer.push_back(colors[index].b);

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

}

GLuint Object::generateVAO(vector<GLfloat> vertbuffer, int &nVertices)
{
	nVertices = vertbuffer.size() / 11;

	GLuint VBO, VAO;

	//Geração do identificador do VBO
	glGenBuffers(1, &VBO);

	//Faz a conexão (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, vertbuffer.size() * sizeof(GLfloat), vertbuffer.data(), GL_STATIC_DRAW);

	//Geração do identificador do VAO (Vertex Array Object)
	glGenVertexArrays(1, &VAO);

	// Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de vértices
	// e os ponteiros para os atributos 
	glBindVertexArray(VAO);

	//Atributo posição (x, y, z)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Atributo cor (r, g, b)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Atributo coordenadas de textura (s, t)
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	//Atributo vetor normal (x, y e z)
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(8 * sizeof(GLfloat)));
	glEnableVertexAttribArray(3);

	// Observe que isso é permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de vértice 
	// atualmente vinculado - para que depois possamos desvincular com segurança
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Desvincula o VAO (é uma boa prática desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0);

	return VAO;
}

int Object::generateTexture(string filePath)
{
	GLuint texID;

	// Gera o identificador da textura na memória
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		if (nrChannels == 3) //jpg, bmp
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
				data);
		}
		else //png
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
				data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;
}
