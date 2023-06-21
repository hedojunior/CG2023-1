#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "MaterialConfig.h"

using namespace std;

Material MaterialConfig::getMaterial(string materialId)
{
    for (Material m : materials)
    {
        if (m.mtlId == materialId)
        {
            return m;
        }
    }

    return Material();
}

void MaterialConfig::parseMTLFile(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Failed to open file: " << filename << endl;
    }

    string line;
    Material currentMaterial;

    while (getline(file, line)) {
        istringstream iss(line);
        string keyword;

        if (!(iss >> keyword))
            continue;

        if (keyword == "newmtl") {
            if (!currentMaterial.mtlId.empty()) {
                materials.push_back(currentMaterial);
            }
            iss >> currentMaterial.mtlId;
        }
        else if (keyword == "Ns") {
            string valueStr;
            iss >> valueStr;
            currentMaterial.ns = stof(valueStr);
        }
        else if (keyword == "Ni") {
            string valueStr;
            iss >> valueStr;
            currentMaterial.ni = stof(valueStr);
        }
        else if (keyword == "d") {
            string valueStr;
            iss >> valueStr;
            currentMaterial.d = stof(valueStr);
        }
        else if (keyword == "Tf") {
            string valueStr;
            iss >> valueStr;
            currentMaterial.tf = stof(valueStr);
        }
        else if (keyword == "illum") {
            string valueStr;
            iss >> valueStr;
            currentMaterial.illum = stoi(valueStr);
        }
        else if (keyword == "Ka") {
            string valueStr;
            iss >> valueStr;
            currentMaterial.ka = stof(valueStr);
        }
        else if (keyword == "Kd") {
            string valueStr;
            iss >> valueStr;
            currentMaterial.kd = stof(valueStr);
        }
        else if (keyword == "Ks") {
            string valueStr;
            iss >> valueStr;
            currentMaterial.ks = stof(valueStr);
        }
        else if (keyword == "map_Kd") {
            iss >> currentMaterial.map_Kd;
        }
    }

    if (!currentMaterial.mtlId.empty()) {
        materials.push_back(currentMaterial);
    }

    file.close();
}
