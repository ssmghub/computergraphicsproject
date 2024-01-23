#include "objParse.h"

int main_forParse()
{
    std::ifstream objFile("Assert/land.obj");
    if (!objFile) {
        std::cerr << "Failed to open OBJ file." << std::endl;
        return 1;
    }

    std::vector<VertexOBJ> positions;
    std::vector<Normal> normals;
    std::vector<Face> faces;

    std::string line;
    while (std::getline(objFile, line)) {
        std::istringstream iss(line);
        std::string token;
        iss >> token;

        if (token == "vn") { // Vertex normal
            Normal normal;
            iss >> normal.nx >> normal.ny >> normal.nz;
            normals.push_back(normal);
        }
        else if (token == "v") { // Vertex position
            VertexOBJ vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            positions.push_back(vertex);
        }
        else if (token == "f") { // Face
            Face face;
            std::string vertexIndices[3];
            for (int i = 0; i < 3; ++i) {
                iss >> vertexIndices[i];
                face.vertexIndices[i] = std::stoi(vertexIndices[i]) - 1; // -1 to convert from 1-based index to 0-based index
            }
            faces.push_back(face);
        }
    }

    // Calculate face normals
    std::vector<Normal> faceNormals;
    for (const Face& face : faces) {
        const VertexOBJ& v1 = positions[face.vertexIndices[0]];
        const VertexOBJ& v2 = positions[face.vertexIndices[1]];
        const VertexOBJ& v3 = positions[face.vertexIndices[2]];

        Normal normal;
        normal.nx = (v2.y - v1.y) * (v3.z - v1.z) - (v2.z - v1.z) * (v3.y - v1.y);
        normal.ny = (v2.z - v1.z) * (v3.x - v1.x) - (v2.x - v1.x) * (v3.z - v1.z);
        normal.nz = (v2.x - v1.x) * (v3.y - v1.y) - (v2.y - v1.y) * (v3.x - v1.x);

        faceNormals.push_back(normal);
    }

    // Print vertices and face normals
    for (size_t i = 0; i < faces.size(); ++i) {
        const Face& face = faces[i];
        for (int j = 0; j < 3; ++j) {
            const VertexOBJ& vertex = positions[face.vertexIndices[j]];
            const Normal& normal = faceNormals[i];
            std::cout << vertex.x << "f, " << vertex.y << "f, " << vertex.z << "f,     "
                << "1.0f, 1.0f, 1.0f" << ",     " << normal.nx << "f, " << normal.ny << "f, " << normal.nz << "f, " << std::endl;

        }
    }

    return 0;
}

