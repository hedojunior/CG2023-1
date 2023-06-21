#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "SceneConfig.h"
#include "tinyxml.h"

using namespace std;

void SceneConfig::parseXML(const string& filePath) {
    TiXmlDocument xmlDoc(filePath.c_str());
    bool loadSuccess = xmlDoc.LoadFile();

    if (!loadSuccess) {
        cout << "Erro ao carregar o arquivo XML." << endl;
        return;
    }

    TiXmlElement* rootElement = xmlDoc.RootElement();
    if (!rootElement) {
        cout << "Elemento raiz ausente." << endl;
        return;
    }

    TiXmlElement* sceneElement = rootElement->FirstChildElement("Scene");
    if (sceneElement) {
        TiXmlElement* lightPosElement = sceneElement->FirstChildElement("LightPos");
        if (lightPosElement) {
            float x, y, z;
            lightPosElement->QueryFloatAttribute("x", &x);
            lightPosElement->QueryFloatAttribute("y", &y);
            lightPosElement->QueryFloatAttribute("z", &z);
            lightPos = glm::vec3(x, y, z);
        }

        TiXmlElement* lightColorElement = sceneElement->FirstChildElement("LightColor");
        if (lightColorElement) {
            float r, g, b;
            lightColorElement->QueryFloatAttribute("r", &r);
            lightColorElement->QueryFloatAttribute("g", &g);
            lightColorElement->QueryFloatAttribute("b", &b);
            lightColor = glm::vec3(r, g, b);
        }

        TiXmlElement* cameraPosElement = sceneElement->FirstChildElement("CameraPos");
        if (cameraPosElement) {
            float x, y, z;
            cameraPosElement->QueryFloatAttribute("x", &x);
            cameraPosElement->QueryFloatAttribute("y", &y);
            cameraPosElement->QueryFloatAttribute("z", &z);
            cameraPos = glm::vec3(x, y, z);
        }

        TiXmlElement* cameraFrontElement = sceneElement->FirstChildElement("CameraFront");
        if (cameraFrontElement) {
            float x, y, z;
            cameraFrontElement->QueryFloatAttribute("x", &x);
            cameraFrontElement->QueryFloatAttribute("y", &y);
            cameraFrontElement->QueryFloatAttribute("z", &z);
            cameraFront = glm::vec3(x, y, z);
        }

        TiXmlElement* cameraUpElement = sceneElement->FirstChildElement("CameraUp");
        if (cameraUpElement) {
            float x, y, z;
            cameraUpElement->QueryFloatAttribute("x", &x);
            cameraUpElement->QueryFloatAttribute("y", &y);
            cameraUpElement->QueryFloatAttribute("z", &z);
            cameraUp = glm::vec3(x, y, z);
        }

        TiXmlElement* cameraSpeedElement = sceneElement->FirstChildElement("CameraSpeed");
        if (cameraSpeedElement) {
            cameraSpeed = stof(cameraSpeedElement->GetText());
        }

        TiXmlElement* specularElement = sceneElement->FirstChildElement("Specular");
        if (specularElement) {
            specular = stof(specularElement->GetText());
        }
    }

    TiXmlElement* objectsElement = rootElement->FirstChildElement("Objects");
    if (objectsElement) {
        for (TiXmlElement* objectElement = objectsElement->FirstChildElement("Object"); objectElement; objectElement = objectElement->NextSiblingElement("Object")) {
            ObjectConfig objectConfig;

            TiXmlElement* objFileElement = objectElement->FirstChildElement("ObjFile");
            if (objFileElement) {
                objectConfig.objFile = objFileElement->GetText();
            }

            TiXmlElement* initialRotationElement = objectElement->FirstChildElement("InitialRotation");
            if (initialRotationElement) {
                float x, y, z;
                initialRotationElement->QueryFloatAttribute("x", &x);
                initialRotationElement->QueryFloatAttribute("y", &y);
                initialRotationElement->QueryFloatAttribute("z", &z);
                objectConfig.initialRotation = glm::vec3(x, y, z);
            }

            TiXmlElement* initialTranslationElement = objectElement->FirstChildElement("InitialTranslation");
            if (initialTranslationElement) {
                float x, y, z;
                initialTranslationElement->QueryFloatAttribute("x", &x);
                initialTranslationElement->QueryFloatAttribute("y", &y);
                initialTranslationElement->QueryFloatAttribute("z", &z);
                objectConfig.initialTranslation = glm::vec3(x, y, z);
            }

            TiXmlElement* initialScaleElement = objectElement->FirstChildElement("InitialScale");
            if (initialScaleElement) {
                float x, y, z;
                initialScaleElement->QueryFloatAttribute("x", &x);
                initialScaleElement->QueryFloatAttribute("y", &y);
                initialScaleElement->QueryFloatAttribute("z", &z);
                objectConfig.initialScale = glm::vec3(x, y, z);
            }

            objects.push_back(objectConfig);
        }
    }
}