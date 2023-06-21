#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

// Classe ObjectConfig
class ObjectConfig {
public:
    std::string objFile;
    std::vector<std::string> textureFiles;
    glm::vec3 initialRotation;
    glm::vec3 initialTranslation;
    glm::vec3 initialScale;
    float ka, kd, ks, q;
};

// Classe SceneConfig
class SceneConfig {
public:
    std::vector<ObjectConfig> objects;
    glm::vec3 lightPos;
    glm::vec3 lightColor;
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    float cameraSpeed;
    
    SceneConfig() {}
    ~SceneConfig() {}
    
    void parseXML(const std::string& xmlFile);
};
