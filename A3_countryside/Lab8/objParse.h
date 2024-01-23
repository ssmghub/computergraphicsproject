#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct VertexOBJ {
    float x, y, z;
};

struct Normal {
    float nx, ny, nz;
};

struct Face {
    int vertexIndices[3];
};


// this is only a file for parse, when using it, need to create a new project for it
int main_forParse();
