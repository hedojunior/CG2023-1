#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "SceneConfig.h"
#include "tinyxml.h"


void SceneConfig::parseXML(const std::string& filePath) {
    TiXmlDocument xmlDoc(filePath.c_str());
    bool loadSuccess = xmlDoc.LoadFile();

    if (!loadSuccess) {
        std::cout << "Erro ao carregar o arquivo XML." << std::endl;
        return;
    }

    TiXmlElement* rootElement = xmlDoc.RootElement();
    if (!rootElement) {
        std::cout << "Elemento raiz ausente." << std::endl;
        return;
    }

    // Parse da configuração da cena
    TiXmlElement* sceneElement = rootElement->FirstChildElement("Scene");
    if (sceneElement) {
        // Parse da posição da luz
        TiXmlElement* lightPosElement = sceneElement->FirstChildElement("LightPos");
        if (lightPosElement) {
            float x, y, z;
            lightPosElement->QueryFloatAttribute("x", &x);
            lightPosElement->QueryFloatAttribute("y", &y);
            lightPosElement->QueryFloatAttribute("z", &z);
            lightPos = glm::vec3(x, y, z);
        }

        // Parse da cor da luz
        TiXmlElement* lightColorElement = sceneElement->FirstChildElement("LightColor");
        if (lightColorElement) {
            float r, g, b;
            lightColorElement->QueryFloatAttribute("r", &r);
            lightColorElement->QueryFloatAttribute("g", &g);
            lightColorElement->QueryFloatAttribute("b", &b);
            lightColor = glm::vec3(r, g, b);
        }

        // Parse da posição da câmera
        TiXmlElement* cameraPosElement = sceneElement->FirstChildElement("CameraPos");
        if (cameraPosElement) {
            float x, y, z;
            cameraPosElement->QueryFloatAttribute("x", &x);
            cameraPosElement->QueryFloatAttribute("y", &y);
            cameraPosElement->QueryFloatAttribute("z", &z);
            cameraPos = glm::vec3(x, y, z);
        }

        // Parse da direção da câmera
        TiXmlElement* cameraFrontElement = sceneElement->FirstChildElement("CameraFront");
        if (cameraFrontElement) {
            float x, y, z;
            cameraFrontElement->QueryFloatAttribute("x", &x);
            cameraFrontElement->QueryFloatAttribute("y", &y);
            cameraFrontElement->QueryFloatAttribute("z", &z);
            cameraFront = glm::vec3(x, y, z);
        }

        // Parse do vetor 'Up' da câmera
        TiXmlElement* cameraUpElement = sceneElement->FirstChildElement("CameraUp");
        if (cameraUpElement) {
            float x, y, z;
            cameraUpElement->QueryFloatAttribute("x", &x);
            cameraUpElement->QueryFloatAttribute("y", &y);
            cameraUpElement->QueryFloatAttribute("z", &z);
            cameraUp = glm::vec3(x, y, z);
        }

        // Parse do arquivo do objeto
        TiXmlElement* cameraSpeedElement = sceneElement->FirstChildElement("CameraSpeed");
        if (cameraSpeedElement) {
            cameraSpeed = std::stof(cameraSpeedElement->GetText());
        }
    }

    // Parse dos objetos
    TiXmlElement* objectsElement = rootElement->FirstChildElement("Objects");
    if (objectsElement) {
        for (TiXmlElement* objectElement = objectsElement->FirstChildElement("Object"); objectElement; objectElement = objectElement->NextSiblingElement("Object")) {
            ObjectConfig objectConfig;

            // Parse do arquivo do objeto
            TiXmlElement* objFileElement = objectElement->FirstChildElement("ObjFile");
            if (objFileElement) {
                objectConfig.objFile = objFileElement->GetText();
            }

            // Parse dos arquivos de textura
            TiXmlElement* textureFilesElement = objectElement->FirstChildElement("TextureFiles");
            if (textureFilesElement) {
                for (TiXmlElement* textureFileElement = textureFilesElement->FirstChildElement("TextureFile"); textureFileElement; textureFileElement = textureFileElement->NextSiblingElement("TextureFile")) {
                    std::string textureFile = textureFileElement->GetText();
                    objectConfig.textureFiles.push_back(textureFile);
                }
            }

            // Parse da rotação inicial
            TiXmlElement* initialRotationElement = objectElement->FirstChildElement("InitialRotation");
            if (initialRotationElement) {
                float x, y, z;
                initialRotationElement->QueryFloatAttribute("x", &x);
                initialRotationElement->QueryFloatAttribute("y", &y);
                initialRotationElement->QueryFloatAttribute("z", &z);
                objectConfig.initialRotation = glm::vec3(x, y, z);
            }

            // Parse da translação inicial
            TiXmlElement* initialTranslationElement = objectElement->FirstChildElement("InitialTranslation");
            if (initialTranslationElement) {
                float x, y, z;
                initialTranslationElement->QueryFloatAttribute("x", &x);
                initialTranslationElement->QueryFloatAttribute("y", &y);
                initialTranslationElement->QueryFloatAttribute("z", &z);
                objectConfig.initialTranslation = glm::vec3(x, y, z);
            }

            // Parse da escala inicial
            TiXmlElement* initialScaleElement = objectElement->FirstChildElement("InitialScale");
            if (initialScaleElement) {
                float x, y, z;
                initialScaleElement->QueryFloatAttribute("x", &x);
                initialScaleElement->QueryFloatAttribute("y", &y);
                initialScaleElement->QueryFloatAttribute("z", &z);
                objectConfig.initialScale = glm::vec3(x, y, z);
            }

            // Parse dos coeficientes de reflexão
            TiXmlElement* reflectionElement = objectElement->FirstChildElement("Reflection");
            if (reflectionElement) {
                reflectionElement->QueryFloatAttribute("ka", &objectConfig.ka);
                reflectionElement->QueryFloatAttribute("kd", &objectConfig.kd);
                reflectionElement->QueryFloatAttribute("ks", &objectConfig.ks);
                reflectionElement->QueryFloatAttribute("q", &objectConfig.q);
            }

            objects.push_back(objectConfig);
        }
    }
}