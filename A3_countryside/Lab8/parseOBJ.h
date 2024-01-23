#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct Vertex {
    float x, y, z;
    float u, v;
    float nx, ny, nz;
};

std::vector<std::string> splitString(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void parseObjFile(const std::string& filename, std::vector<Vertex>& vertices) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::vector<float> positions, texCoords, normals;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        iss >> token;

        if (token == "v ") {
            std::istringstream s(line.substr(2));
            float x, y, z;
            s >> x >> y >> z;
            positions.push_back(x);
            positions.push_back(y);
            positions.push_back(z);
        }
        else if (token == "vt ") {
            std::istringstream s(line.substr(3));
            float u, v;
            s >> u >> v;
            texCoords.push_back(u);
            texCoords.push_back(v);
        }
        else if (token == "vn ") {
            std::istringstream s(line.substr(3));
            float nx, ny, nz;
            s >> nx >> ny >> nz;
            normals.push_back(nx);
            normals.push_back(ny);
            normals.push_back(nz);
        }
        else if (token == "f ") {
            std::istringstream s(line.substr(2));
            std::string faceToken;
            std::vector<std::string> faceTokens;
            while (s >> faceToken) {
                faceTokens.push_back(faceToken);
            }

            for (const auto& token1 : faceTokens) {
                std::vector<std::string> indices = splitString(token1, '/');
                int posIndex = std::stoi(indices[0]) - 1;
                int texCoordIndex = std::stoi(indices[1]) - 1;
                int normalIndex = std::stoi(indices[2]) - 1;

                Vertex vertex;
                vertex.x = positions[3 * posIndex];
                vertex.y = positions[3 * posIndex + 1];
                vertex.z = positions[3 * posIndex + 2];

                vertex.u = texCoords[2 * texCoordIndex];
                vertex.v = texCoords[2 * texCoordIndex + 1];

                vertex.nx = normals[3 * normalIndex];
                vertex.ny = normals[3 * normalIndex + 1];
                vertex.nz = normals[3 * normalIndex + 2];

                vertices.push_back(vertex);
            }
        }
    }

    file.close();
}

float* MakeFloatsFrom_OBJVector(std::vector<Vertex> objVer)//, int& num_verts, int& num_floats) //, float r, float g, float b)
{
    int num_verts = objVer.size();
    if (num_verts == 0)
    {
        return NULL;
    }

    // 9 float for each vertex (position, colour, normal)
    int num_floats = num_verts * 9;

    float* vertices = (float*)malloc(sizeof(float) * num_floats); //allocate memory for the vertex attributes

    for (int p = 0; p < num_verts; p++)
    {
        //specify vertex position using p
        vertices[0 + 9 * p] = objVer[p].x;
        vertices[1 + 9 * p] = objVer[p].y;
        vertices[2 + 9 * p] = objVer[p].z;
        //specify vertex colour using r, g, b
        vertices[3 + 9 * p] = 0;
        vertices[4 + 9 * p] = 0;
        vertices[5 + 9 * p] = 0;
        //specify vertex normal
        vertices[6 + 9 * p] = objVer[p].nx;
        vertices[7 + 9 * p] = objVer[p].ny;
        vertices[8 + 9 * p] = objVer[p].nz;
        //specify vertex uv 
        //vertices[9 + 11 * p] = objVer[p].u;
        //vertices[10 + 11 * p] = objVer[p].v;
    }

    return vertices;
}