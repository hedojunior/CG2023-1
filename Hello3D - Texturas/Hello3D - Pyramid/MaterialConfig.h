#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct Material {
public:
    string mtlId;
    float ns;
    float ni;
    float d;
    int tf;
    int illum;
    float ka;
    float kd;
    float ks;
    string map_Kd;
};

struct MaterialConfig {
public:
    vector<Material> materials;
    
    void parseMTLFile(const string& filename);
    Material getMaterial(string materialId);
};




