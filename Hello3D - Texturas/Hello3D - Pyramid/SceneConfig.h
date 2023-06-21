#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class ObjectConfig {
public:
    string objFile;
    vec3 initialRotation;
    vec3 initialTranslation;
    vec3 initialScale;
};

class SceneConfig {
public:
    vector<ObjectConfig> objects;
    
    vec3 lightPos;
    vec3 lightColor;
    vec3 cameraPos;
    vec3 cameraFront;
    vec3 cameraUp;
    float specular;
    float cameraSpeed;
    
    SceneConfig() {}
    ~SceneConfig() {}
    
    void parseXML(const string& xmlFile);
};
