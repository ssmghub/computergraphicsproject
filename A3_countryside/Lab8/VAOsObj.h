#include "drawObj.h"


#define NUM_BUFFERS 11
#define NUM_VAOS 11
GLuint Buffers[NUM_BUFFERS];
GLuint VAOs[NUM_VAOS];

// For OBJ
//int num_obj = sizeof(objVer);

// For Curve
int num_evals = 128;
// For 3D_Curve
int num_tri_vert = 8 * 3;
int num_tri_vert_info = num_tri_vert * 9;

/*struct vertex
{
	float x, y, z;
	float nx, ny, nz;
	float u, v;
};*/


float* makeCurve2D(float* curve_vertices)
{

	// 2D Version ---- one side
	float* cur2D_vert = (float*)malloc(sizeof(float) * num_evals * 2 * 3 * 9);
	for (int i = 0; i < num_evals; i++)
	{
		// TOP
		//right bottom
		//v1	
		cur2D_vert[(i * 54) + 0] = curve_vertices[0 + 9 * (i)]; // v1.x
		cur2D_vert[(i * 54) + 1] = curve_vertices[1 + 9 * (i)]; // v1.y
		cur2D_vert[(i * 54) + 2] = curve_vertices[2 + 9 * (i)]; // v1.z
		// rgb
		cur2D_vert[(i * 54) + 3] = curve_vertices[3 + 9 * (i)];
		cur2D_vert[(i * 54) + 4] = curve_vertices[4 + 9 * (i)];
		cur2D_vert[(i * 54) + 5] = curve_vertices[5 + 9 * (i)];
		// normal
		cur2D_vert[(i * 54) + 6] = curve_vertices[6 + 9 * (i)];
		cur2D_vert[(i * 54) + 7] = curve_vertices[7 + 9 * (i)];
		cur2D_vert[(i * 54) + 8] = curve_vertices[8 + 9 * (i)];
		//v2	
		cur2D_vert[(i * 54) + 9] = curve_vertices[0 + 9 * (i + 1)]; // v1.x
		cur2D_vert[(i * 54) + 10] = curve_vertices[1 + 9 * (i + 1)]; // v1.y
		cur2D_vert[(i * 54) + 11] = curve_vertices[2 + 9 * (i + 1)]; // v1.z
		// rgb
		cur2D_vert[(i * 54) + 12] = curve_vertices[3 + 9 * (i + 1)];
		cur2D_vert[(i * 54) + 13] = curve_vertices[4 + 9 * (i + 1)];
		cur2D_vert[(i * 54) + 14] = curve_vertices[5 + 9 * (i + 1)];
		// normal
		cur2D_vert[(i * 54) + 15] = curve_vertices[6 + 9 * (i + 1)];
		cur2D_vert[(i * 54) + 16] = curve_vertices[7 + 9 * (i + 1)];
		cur2D_vert[(i * 54) + 17] = curve_vertices[8 + 9 * (i + 1)];
		//v3
		cur2D_vert[(i * 54) + 18] = curve_vertices[0 + 9 * (i + 1)]; // v1.x
		cur2D_vert[(i * 54) + 19] = curve_vertices[1 + 9 * (0)]; // v1.y
		cur2D_vert[(i * 54) + 20] = curve_vertices[2 + 9 * (i + 1)]; // v1.z
		// rgb
		cur2D_vert[(i * 54) + 21] = curve_vertices[3 + 9 * (i + 1)];
		cur2D_vert[(i * 54) + 22] = curve_vertices[4 + 9 * (0)];
		cur2D_vert[(i * 54) + 23] = curve_vertices[5 + 9 * (i + 1)];
		// normal
		cur2D_vert[(i * 54) + 24] = curve_vertices[6 + 9 * (i + 1)];
		cur2D_vert[(i * 54) + 25] = curve_vertices[7 + 9 * (0)];
		cur2D_vert[(i * 54) + 26] = curve_vertices[8 + 9 * (i + 1)];

		// BOTTOM
		//left top
		//v1	
		cur2D_vert[(i * 54) + 27] = curve_vertices[0 + 9 * (i)]; // v1.x
		cur2D_vert[(i * 54) + 28] = curve_vertices[1 + 9 * (i)]; // v1.y
		cur2D_vert[(i * 54) + 29] = curve_vertices[2 + 9 * (i)]; // v1.z
		// rgb
		cur2D_vert[(i * 54) + 30] = curve_vertices[3 + 9 * (i)];
		cur2D_vert[(i * 54) + 31] = curve_vertices[4 + 9 * (i)];
		cur2D_vert[(i * 54) + 32] = curve_vertices[5 + 9 * (i)];
		// normal
		cur2D_vert[(i * 54) + 33] = curve_vertices[6 + 9 * (i)];
		cur2D_vert[(i * 54) + 34] = curve_vertices[7 + 9 * (i)];
		cur2D_vert[(i * 54) + 35] = curve_vertices[8 + 9 * (i)];
		//v2	
		cur2D_vert[(i * 54) + 36] = curve_vertices[0 + 9 * (i + 1)]; // v1.x
		cur2D_vert[(i * 54) + 37] = curve_vertices[1 + 9 * (0)]; // v1.y
		cur2D_vert[(i * 54) + 38] = curve_vertices[2 + 9 * (i + 1)]; // v1.z
		// rgb
		cur2D_vert[(i * 54) + 39] = curve_vertices[3 + 9 * (i + 1)];
		cur2D_vert[(i * 54) + 40] = curve_vertices[4 + 9 * (0)];
		cur2D_vert[(i * 54) + 41] = curve_vertices[5 + 9 * (i + 1)];
		// normal
		cur2D_vert[(i * 54) + 42] = curve_vertices[6 + 9 * (i + 1)];
		cur2D_vert[(i * 54) + 43] = curve_vertices[7 + 9 * (0)];
		cur2D_vert[(i * 54) + 44] = curve_vertices[8 + 9 * (i + 1)];
		//v3	
		cur2D_vert[(i * 54) + 45] = curve_vertices[0 + 9 * (i)]; // v1.x
		cur2D_vert[(i * 54) + 46] = curve_vertices[1 + 9 * (0)]; // v1.y
		cur2D_vert[(i * 54) + 47] = curve_vertices[2 + 9 * (i)]; // v1.z
		// rgb
		cur2D_vert[(i * 54) + 48] = curve_vertices[3 + 9 * (i)];
		cur2D_vert[(i * 54) + 49] = curve_vertices[4 + 9 * (0)];
		cur2D_vert[(i * 54) + 50] = curve_vertices[5 + 9 * (i)];
		// normal
		cur2D_vert[(i * 54) + 51] = curve_vertices[6 + 9 * (i)];
		cur2D_vert[(i * 54) + 52] = curve_vertices[7 + 9 * (0)];
		cur2D_vert[(i * 54) + 53] = curve_vertices[8 + 9 * (i)];
	}

	free(curve_vertices);

	return cur2D_vert;
}


float* makeCurve3DCloud(float* curve_vertices_3D)
{
	// 3D Vertion
	float* cur3D_vert = (float*)malloc(sizeof(float) * num_evals * num_tri_vert_info);
	//float* cur3D_vert = (float*)malloc(sizeof(float) * num_evals * 4 * 3 * 9);
	float thickness = 3.0f;
	for (int i = 0; i < num_evals; i++)
	{
		// Front Side TOP
		//right bottom
		//v1	
		cur3D_vert[(i * num_tri_vert_info) + 0] = curve_vertices_3D[0 + 9 * (i)]; // v1.x
		cur3D_vert[(i * num_tri_vert_info) + 1] = curve_vertices_3D[1 + 9 * (i)]; // v1.y
		cur3D_vert[(i * num_tri_vert_info) + 2] = curve_vertices_3D[2 + 9 * (i)]; // v1.z
		// rgb
		cur3D_vert[(i * num_tri_vert_info) + 3] = curve_vertices_3D[3 + 9 * (i)];
		cur3D_vert[(i * num_tri_vert_info) + 4] = curve_vertices_3D[4 + 9 * (i)];
		cur3D_vert[(i * num_tri_vert_info) + 5] = curve_vertices_3D[5 + 9 * (i)];
		//v2	
		cur3D_vert[(i * num_tri_vert_info) + 9] = curve_vertices_3D[0 + 9 * (i + 1)]; // v1.x
		cur3D_vert[(i * num_tri_vert_info) + 10] = curve_vertices_3D[1 + 9 * (i + 1)]; // v1.y
		cur3D_vert[(i * num_tri_vert_info) + 11] = curve_vertices_3D[2 + 9 * (i + 1)]; // v1.z
		// rgb
		cur3D_vert[(i * num_tri_vert_info) + 12] = curve_vertices_3D[3 + 9 * (i + 1)];
		cur3D_vert[(i * num_tri_vert_info) + 13] = curve_vertices_3D[4 + 9 * (i + 1)];
		cur3D_vert[(i * num_tri_vert_info) + 14] = curve_vertices_3D[5 + 9 * (i + 1)];
		//v3
		cur3D_vert[(i * num_tri_vert_info) + 18] = curve_vertices_3D[0 + 9 * (i + 1)]; // v1.x
		cur3D_vert[(i * num_tri_vert_info) + 19] = curve_vertices_3D[1 + 9 * (0)]; // v1.y
		cur3D_vert[(i * num_tri_vert_info) + 20] = curve_vertices_3D[2 + 9 * (i + 1)]; // v1.z
		// rgb
		cur3D_vert[(i * num_tri_vert_info) + 21] = curve_vertices_3D[3 + 9 * (i + 1)];
		cur3D_vert[(i * num_tri_vert_info) + 22] = curve_vertices_3D[4 + 9 * (0)];
		cur3D_vert[(i * num_tri_vert_info) + 23] = curve_vertices_3D[5 + 9 * (i + 1)];

		// Calculate normal for Triangle 1: 
		glm::vec3 v11 = glm::vec3(cur3D_vert[(i * num_tri_vert_info) + 9] - cur3D_vert[(i * num_tri_vert_info) + 0],
			cur3D_vert[(i * num_tri_vert_info) + 10] - cur3D_vert[(i * num_tri_vert_info) + 1],
			cur3D_vert[(i * num_tri_vert_info) + 11] - cur3D_vert[(i * num_tri_vert_info) + 2]);
		glm::vec3 v12 = glm::vec3(cur3D_vert[(i * num_tri_vert_info) + 18] - cur3D_vert[(i * num_tri_vert_info) + 0],
			cur3D_vert[(i * num_tri_vert_info) + 19] - cur3D_vert[(i * num_tri_vert_info) + 1],
			cur3D_vert[(i * num_tri_vert_info) + 20] - cur3D_vert[(i * num_tri_vert_info) + 2]);
		glm::vec3 n1 = normalize(cross(v11, v12));
		// normal
		cur3D_vert[(i * num_tri_vert_info) + 6] = -n1.x;
		cur3D_vert[(i * num_tri_vert_info) + 7] = -n1.y;
		cur3D_vert[(i * num_tri_vert_info) + 8] = -n1.z;
		// normal
		cur3D_vert[(i * num_tri_vert_info) + 15] = -n1.x;
		cur3D_vert[(i * num_tri_vert_info) + 16] = -n1.y;
		cur3D_vert[(i * num_tri_vert_info) + 17] = -n1.z;
		// normal
		cur3D_vert[(i * num_tri_vert_info) + 24] = -n1.x;
		cur3D_vert[(i * num_tri_vert_info) + 25] = -n1.y;
		cur3D_vert[(i * num_tri_vert_info) + 26] = -n1.z;

		// Front Side BOTTOM
		//left top
		//v1	
		cur3D_vert[(i * num_tri_vert_info) + 27] = curve_vertices_3D[0 + 9 * (i)]; // v1.x
		cur3D_vert[(i * num_tri_vert_info) + 28] = curve_vertices_3D[1 + 9 * (i)]; // v1.y
		cur3D_vert[(i * num_tri_vert_info) + 29] = curve_vertices_3D[2 + 9 * (i)]; // v1.z
		// rgb
		cur3D_vert[(i * num_tri_vert_info) + 30] = curve_vertices_3D[3 + 9 * (i)];
		cur3D_vert[(i * num_tri_vert_info) + 31] = curve_vertices_3D[4 + 9 * (i)];
		cur3D_vert[(i * num_tri_vert_info) + 32] = curve_vertices_3D[5 + 9 * (i)];
		//v2	
		cur3D_vert[(i * num_tri_vert_info) + 36] = curve_vertices_3D[0 + 9 * (i + 1)]; // v1.x
		cur3D_vert[(i * num_tri_vert_info) + 37] = curve_vertices_3D[1 + 9 * (0)]; // v1.y
		cur3D_vert[(i * num_tri_vert_info) + 38] = curve_vertices_3D[2 + 9 * (i + 1)]; // v1.z
		// rgb
		cur3D_vert[(i * num_tri_vert_info) + 39] = curve_vertices_3D[3 + 9 * (i + 1)];
		cur3D_vert[(i * num_tri_vert_info) + 40] = curve_vertices_3D[4 + 9 * (0)];
		cur3D_vert[(i * num_tri_vert_info) + 41] = curve_vertices_3D[5 + 9 * (i + 1)];
		//v3	
		cur3D_vert[(i * num_tri_vert_info) + 45] = curve_vertices_3D[0 + 9 * (i)]; // v1.x
		cur3D_vert[(i * num_tri_vert_info) + 46] = curve_vertices_3D[1 + 9 * (0)]; // v1.y
		cur3D_vert[(i * num_tri_vert_info) + 47] = curve_vertices_3D[2 + 9 * (i)]; // v1.z
		// rgb
		cur3D_vert[(i * num_tri_vert_info) + 48] = curve_vertices_3D[3 + 9 * (i)];
		cur3D_vert[(i * num_tri_vert_info) + 49] = curve_vertices_3D[4 + 9 * (0)];
		cur3D_vert[(i * num_tri_vert_info) + 50] = curve_vertices_3D[5 + 9 * (i)];
		// Calculate normal for Triangle 2: 
		glm::vec3 v21 = glm::vec3(cur3D_vert[(i * num_tri_vert_info) + 36] - cur3D_vert[(i * num_tri_vert_info) + 27],
			cur3D_vert[(i * num_tri_vert_info) + 37] - cur3D_vert[(i * num_tri_vert_info) + 28],
			cur3D_vert[(i * num_tri_vert_info) + 38] - cur3D_vert[(i * num_tri_vert_info) + 29]);
		glm::vec3 v22 = glm::vec3(cur3D_vert[(i * num_tri_vert_info) + 45] - cur3D_vert[(i * num_tri_vert_info) + 27],
			cur3D_vert[(i * num_tri_vert_info) + 46] - cur3D_vert[(i * num_tri_vert_info) + 28],
			cur3D_vert[(i * num_tri_vert_info) + 47] - cur3D_vert[(i * num_tri_vert_info) + 29]);
		glm::vec3 n2 = normalize(cross(v21, v22));
		// normal
		cur3D_vert[(i * num_tri_vert_info) + 33] = -n2.x;
		cur3D_vert[(i * num_tri_vert_info) + 34] = -n2.y;
		cur3D_vert[(i * num_tri_vert_info) + 35] = -n2.z;
		// normal
		cur3D_vert[(i * num_tri_vert_info) + 42] = -n2.x;
		cur3D_vert[(i * num_tri_vert_info) + 43] = -n2.y;
		cur3D_vert[(i * num_tri_vert_info) + 44] = -n2.z;
		// normal
		cur3D_vert[(i * num_tri_vert_info) + 51] = -n2.x;
		cur3D_vert[(i * num_tri_vert_info) + 52] = -n2.y;
		cur3D_vert[(i * num_tri_vert_info) + 53] = -n2.z;

		// Curve SIDES
		// Left
		//v1	
		cur3D_vert[(i * num_tri_vert_info) + 54] = curve_vertices_3D[0 + 9 * (i)]; // v1.x
		cur3D_vert[(i * num_tri_vert_info) + 55] = curve_vertices_3D[1 + 9 * (i)]; // v1.y
		cur3D_vert[(i * num_tri_vert_info) + 56] = curve_vertices_3D[2 + 9 * (i)]; // v1.z
		// rgb
		cur3D_vert[(i * num_tri_vert_info) + 57] = curve_vertices_3D[3 + 9 * (i)];
		cur3D_vert[(i * num_tri_vert_info) + 58] = curve_vertices_3D[4 + 9 * (i)];
		cur3D_vert[(i * num_tri_vert_info) + 59] = curve_vertices_3D[5 + 9 * (i)];
		//v2	
		cur3D_vert[(i * num_tri_vert_info) + 63] = curve_vertices_3D[0 + 9 * (i + 1)]; // v1.x
		cur3D_vert[(i * num_tri_vert_info) + 64] = curve_vertices_3D[1 + 9 * (i + 1)]; // v1.y
		cur3D_vert[(i * num_tri_vert_info) + 65] = curve_vertices_3D[2 + 9 * (i + 1)]; // v1.z
		// rgb
		cur3D_vert[(i * num_tri_vert_info) + 66] = curve_vertices_3D[3 + 9 * (i + 1)];
		cur3D_vert[(i * num_tri_vert_info) + 67] = curve_vertices_3D[4 + 9 * (i + 1)];
		cur3D_vert[(i * num_tri_vert_info) + 68] = curve_vertices_3D[5 + 9 * (i + 1)];
		//v1 - back	
		cur3D_vert[(i * num_tri_vert_info) + 72] = curve_vertices_3D[0 + 9 * (i)]; // v1.x
		cur3D_vert[(i * num_tri_vert_info) + 73] = curve_vertices_3D[1 + 9 * (i)]; // v1.y
		cur3D_vert[(i * num_tri_vert_info) + 74] = curve_vertices_3D[2 + 9 * (i)] + thickness; // v1.z
		// rgb
		cur3D_vert[(i * num_tri_vert_info) + 75] = curve_vertices_3D[3 + 9 * (i)];
		cur3D_vert[(i * num_tri_vert_info) + 76] = curve_vertices_3D[4 + 9 * (i)];
		cur3D_vert[(i * num_tri_vert_info) + 77] = curve_vertices_3D[5 + 9 * (i)];
		// Calculate normal for Triangle 3: 
		glm::vec3 v31 = glm::vec3(cur3D_vert[(i * num_tri_vert_info) + 63] - cur3D_vert[(i * num_tri_vert_info) + 54],
			cur3D_vert[(i * num_tri_vert_info) + 64] - cur3D_vert[(i * num_tri_vert_info) + 55],
			cur3D_vert[(i * num_tri_vert_info) + 65] - cur3D_vert[(i * num_tri_vert_info) + 56]);
		glm::vec3 v32 = glm::vec3(cur3D_vert[(i * num_tri_vert_info) + 72] - cur3D_vert[(i * num_tri_vert_info) + 54],
			cur3D_vert[(i * num_tri_vert_info) + 73] - cur3D_vert[(i * num_tri_vert_info) + 55],
			cur3D_vert[(i * num_tri_vert_info) + 74] - cur3D_vert[(i * num_tri_vert_info) + 56]);
		glm::vec3 n3 = normalize(cross(v31, v32));
		// normal
		cur3D_vert[(i * num_tri_vert_info) + 60] = n3.x;
		cur3D_vert[(i * num_tri_vert_info) + 61] = n3.y;
		cur3D_vert[(i * num_tri_vert_info) + 62] = n3.z;
		// normal
		cur3D_vert[(i * num_tri_vert_info) + 69] = n3.x;
		cur3D_vert[(i * num_tri_vert_info) + 70] = n3.y;
		cur3D_vert[(i * num_tri_vert_info) + 71] = n3.z;
		// normal
		cur3D_vert[(i * num_tri_vert_info) + 78] = n3.x;
		cur3D_vert[(i * num_tri_vert_info) + 79] = n3.y;
		cur3D_vert[(i * num_tri_vert_info) + 80] = n3.z;

		// Right
		//v1	
		cur3D_vert[(i * num_tri_vert_info) + 81] = curve_vertices_3D[0 + 9 * (i)]; // v1.x
		cur3D_vert[(i * num_tri_vert_info) + 82] = curve_vertices_3D[1 + 9 * (i)]; // v1.y
		cur3D_vert[(i * num_tri_vert_info) + 83] = curve_vertices_3D[2 + 9 * (i)] + thickness; // v1.z
		// rgb
		cur3D_vert[(i * num_tri_vert_info) + 84] = curve_vertices_3D[3 + 9 * (i)];
		cur3D_vert[(i * num_tri_vert_info) + 85] = curve_vertices_3D[4 + 9 * (i)];
		cur3D_vert[(i * num_tri_vert_info) + 86] = curve_vertices_3D[5 + 9 * (i)];
		//v2	
		cur3D_vert[(i * num_tri_vert_info) + 90] = curve_vertices_3D[0 + 9 * (i + 1)]; // v1.x
		cur3D_vert[(i * num_tri_vert_info) + 91] = curve_vertices_3D[1 + 9 * (i + 1)]; // v1.y
		cur3D_vert[(i * num_tri_vert_info) + 92] = curve_vertices_3D[2 + 9 * (i + 1)] + thickness; // v1.z
		// rgb
		cur3D_vert[(i * num_tri_vert_info) + 93] = curve_vertices_3D[3 + 9 * (i + 1)];
		cur3D_vert[(i * num_tri_vert_info) + 94] = curve_vertices_3D[4 + 9 * (i + 1)];
		cur3D_vert[(i * num_tri_vert_info) + 95] = curve_vertices_3D[5 + 9 * (i + 1)];
		//v1 - back	
		cur3D_vert[(i * num_tri_vert_info) + 99] = curve_vertices_3D[0 + 9 * (i + 1)]; // v1.x
		cur3D_vert[(i * num_tri_vert_info) + 100] = curve_vertices_3D[1 + 9 * (i + 1)]; // v1.y
		cur3D_vert[(i * num_tri_vert_info) + 101] = curve_vertices_3D[2 + 9 * (i + 1)]; // v1.z
		// rgb
		cur3D_vert[(i * num_tri_vert_info) + 102] = curve_vertices_3D[3 + 9 * (i + 1)];
		cur3D_vert[(i * num_tri_vert_info) + 103] = curve_vertices_3D[4 + 9 * (i + 1)];
		cur3D_vert[(i * num_tri_vert_info) + 104] = curve_vertices_3D[5 + 9 * (i + 1)];
		// Calculate normal for Triangle 4: 
		glm::vec3 v41 = glm::vec3(cur3D_vert[(i * num_tri_vert_info) + 90] - cur3D_vert[(i * num_tri_vert_info) + 81],
			cur3D_vert[(i * num_tri_vert_info) + 91] - cur3D_vert[(i * num_tri_vert_info) + 82],
			cur3D_vert[(i * num_tri_vert_info) + 92] - cur3D_vert[(i * num_tri_vert_info) + 83]);
		glm::vec3 v42 = glm::vec3(cur3D_vert[(i * num_tri_vert_info) + 99] - cur3D_vert[(i * num_tri_vert_info) + 81],
			cur3D_vert[(i * num_tri_vert_info) + 100] - cur3D_vert[(i * num_tri_vert_info) + 82],
			cur3D_vert[(i * num_tri_vert_info) + 101] - cur3D_vert[(i * num_tri_vert_info) + 83]);
		glm::vec3 n4 = normalize(cross(v41, v42));
		// normal
		cur3D_vert[(i * num_tri_vert_info) + 87] = -n4.x;
		cur3D_vert[(i * num_tri_vert_info) + 88] = -n4.y;
		cur3D_vert[(i * num_tri_vert_info) + 89] = -n4.z;
		// normal
		cur3D_vert[(i * num_tri_vert_info) + 96] = -n4.x;
		cur3D_vert[(i * num_tri_vert_info) + 97] = -n4.y;
		cur3D_vert[(i * num_tri_vert_info) + 98] = -n4.z;
		// normal
		cur3D_vert[(i * num_tri_vert_info) + 105] = -n4.x;
		cur3D_vert[(i * num_tri_vert_info) + 106] = -n4.y;
		cur3D_vert[(i * num_tri_vert_info) + 107] = -n4.z;

		// Back Side TOP
		//right bottom
		//v1	
		cur3D_vert[(i * num_tri_vert_info) + 108] = curve_vertices_3D[0 + 9 * (i)]; // v1.x
		cur3D_vert[(i * num_tri_vert_info) + 109] = curve_vertices_3D[1 + 9 * (i)]; // v1.y
		cur3D_vert[(i * num_tri_vert_info) + 110] = curve_vertices_3D[2 + 9 * (i)] + thickness; // v1.z
		// rgb
		cur3D_vert[(i * num_tri_vert_info) + 111] = curve_vertices_3D[3 + 9 * (i)];
		cur3D_vert[(i * num_tri_vert_info) + 112] = curve_vertices_3D[4 + 9 * (i)];
		cur3D_vert[(i * num_tri_vert_info) + 113] = curve_vertices_3D[5 + 9 * (i)];
		//v2	
		cur3D_vert[(i * num_tri_vert_info) + 117] = curve_vertices_3D[0 + 9 * (i + 1)]; // v1.x
		cur3D_vert[(i * num_tri_vert_info) + 118] = curve_vertices_3D[1 + 9 * (i + 1)]; // v1.y
		cur3D_vert[(i * num_tri_vert_info) + 119] = curve_vertices_3D[2 + 9 * (i + 1)] + thickness; // v1.z
		// rgb
		cur3D_vert[(i * num_tri_vert_info) + 120] = curve_vertices_3D[3 + 9 * (i + 1)];
		cur3D_vert[(i * num_tri_vert_info) + 121] = curve_vertices_3D[4 + 9 * (i + 1)];
		cur3D_vert[(i * num_tri_vert_info) + 122] = curve_vertices_3D[5 + 9 * (i + 1)];
		//v3
		cur3D_vert[(i * num_tri_vert_info) + 126] = curve_vertices_3D[0 + 9 * (i + 1)]; // v1.x
		cur3D_vert[(i * num_tri_vert_info) + 127] = curve_vertices_3D[1 + 9 * (0)]; // v1.y
		cur3D_vert[(i * num_tri_vert_info) + 128] = curve_vertices_3D[2 + 9 * (i + 1)] + thickness; // v1.z
		// rgb
		cur3D_vert[(i * num_tri_vert_info) + 129] = curve_vertices_3D[3 + 9 * (i + 1)];
		cur3D_vert[(i * num_tri_vert_info) + 130] = curve_vertices_3D[4 + 9 * (0)];
		cur3D_vert[(i * num_tri_vert_info) + 131] = curve_vertices_3D[5 + 9 * (i + 1)];
		// Calculate normal for Triangle 5: 
		glm::vec3 v51 = glm::vec3(cur3D_vert[(i * num_tri_vert_info) + 117] - cur3D_vert[(i * num_tri_vert_info) + 108],
			cur3D_vert[(i * num_tri_vert_info) + 118] - cur3D_vert[(i * num_tri_vert_info) + 109],
			cur3D_vert[(i * num_tri_vert_info) + 119] - cur3D_vert[(i * num_tri_vert_info) + 110]);
		glm::vec3 v52 = glm::vec3(cur3D_vert[(i * num_tri_vert_info) + 126] - cur3D_vert[(i * num_tri_vert_info) + 108],
			cur3D_vert[(i * num_tri_vert_info) + 127] - cur3D_vert[(i * num_tri_vert_info) + 109],
			cur3D_vert[(i * num_tri_vert_info) + 128] - cur3D_vert[(i * num_tri_vert_info) + 110]);
		glm::vec3 n5 = normalize(cross(v51, v52));
		// normal
		cur3D_vert[(i * num_tri_vert_info) + 114] = n5.x;
		cur3D_vert[(i * num_tri_vert_info) + 115] = n5.y;
		cur3D_vert[(i * num_tri_vert_info) + 116] = n5.z;
		// normal
		cur3D_vert[(i * num_tri_vert_info) + 123] = n5.x;
		cur3D_vert[(i * num_tri_vert_info) + 124] = n5.y;
		cur3D_vert[(i * num_tri_vert_info) + 125] = n5.z;
		// normal
		cur3D_vert[(i * num_tri_vert_info) + 132] = n5.x;
		cur3D_vert[(i * num_tri_vert_info) + 133] = n5.y;
		cur3D_vert[(i * num_tri_vert_info) + 134] = n5.z;

		// Front Side BOTTOM
		//left top
		//v1	
		cur3D_vert[(i * num_tri_vert_info) + 135] = curve_vertices_3D[0 + 9 * (i)]; // v1.x
		cur3D_vert[(i * num_tri_vert_info) + 136] = curve_vertices_3D[1 + 9 * (i)]; // v1.y
		cur3D_vert[(i * num_tri_vert_info) + 137] = curve_vertices_3D[2 + 9 * (i)] + thickness; // v1.z
		// rgb
		cur3D_vert[(i * num_tri_vert_info) + 138] = curve_vertices_3D[3 + 9 * (i)];
		cur3D_vert[(i * num_tri_vert_info) + 139] = curve_vertices_3D[4 + 9 * (i)];
		cur3D_vert[(i * num_tri_vert_info) + 140] = curve_vertices_3D[5 + 9 * (i)];
		//v2	
		cur3D_vert[(i * num_tri_vert_info) + 144] = curve_vertices_3D[0 + 9 * (i + 1)]; // v1.x
		cur3D_vert[(i * num_tri_vert_info) + 145] = curve_vertices_3D[1 + 9 * (0)]; // v1.y
		cur3D_vert[(i * num_tri_vert_info) + 146] = curve_vertices_3D[2 + 9 * (i + 1)] + thickness; // v1.z
		// rgb
		cur3D_vert[(i * num_tri_vert_info) + 147] = curve_vertices_3D[3 + 9 * (i + 1)];
		cur3D_vert[(i * num_tri_vert_info) + 148] = curve_vertices_3D[4 + 9 * (0)];
		cur3D_vert[(i * num_tri_vert_info) + 149] = curve_vertices_3D[5 + 9 * (i + 1)];
		//v3	
		cur3D_vert[(i * num_tri_vert_info) + 153] = curve_vertices_3D[0 + 9 * (i)]; // v1.x
		cur3D_vert[(i * num_tri_vert_info) + 154] = curve_vertices_3D[1 + 9 * (0)]; // v1.y
		cur3D_vert[(i * num_tri_vert_info) + 155] = curve_vertices_3D[2 + 9 * (i)] + thickness; // v1.z
		// rgb
		cur3D_vert[(i * num_tri_vert_info) + 156] = curve_vertices_3D[3 + 9 * (i)];
		cur3D_vert[(i * num_tri_vert_info) + 157] = curve_vertices_3D[4 + 9 * (0)];
		cur3D_vert[(i * num_tri_vert_info) + 158] = curve_vertices_3D[5 + 9 * (i)];
		// Calculate normal for Triangle 6: 
		glm::vec3 v61 = glm::vec3(cur3D_vert[(i * num_tri_vert_info) + 144] - cur3D_vert[(i * num_tri_vert_info) + 135],
			cur3D_vert[(i * num_tri_vert_info) + 145] - cur3D_vert[(i * num_tri_vert_info) + 136],
			cur3D_vert[(i * num_tri_vert_info) + 146] - cur3D_vert[(i * num_tri_vert_info) + 137]);
		glm::vec3 v62 = glm::vec3(cur3D_vert[(i * num_tri_vert_info) + 153] - cur3D_vert[(i * num_tri_vert_info) + 135],
			cur3D_vert[(i * num_tri_vert_info) + 154] - cur3D_vert[(i * num_tri_vert_info) + 136],
			cur3D_vert[(i * num_tri_vert_info) + 155] - cur3D_vert[(i * num_tri_vert_info) + 137]);
		glm::vec3 n6 = normalize(cross(v61, v62));
		// normal
		cur3D_vert[(i * num_tri_vert_info) + 141] = n6.x;
		cur3D_vert[(i * num_tri_vert_info) + 142] = n6.y;
		cur3D_vert[(i * num_tri_vert_info) + 143] = n6.z;
		// normal
		cur3D_vert[(i * num_tri_vert_info) + 150] = n6.x;
		cur3D_vert[(i * num_tri_vert_info) + 151] = n6.y;
		cur3D_vert[(i * num_tri_vert_info) + 152] = n6.z;
		// normal
		cur3D_vert[(i * num_tri_vert_info) + 159] = n6.x;
		cur3D_vert[(i * num_tri_vert_info) + 160] = n6.y;
		cur3D_vert[(i * num_tri_vert_info) + 161] = n6.z;

		// Bottom Sides
		// Left
		//v1	
		cur3D_vert[(i * num_tri_vert_info) + 162] = curve_vertices_3D[0 + 9 * (i)]; // v1.x
		cur3D_vert[(i * num_tri_vert_info) + 163] = 0; // v1.y
		cur3D_vert[(i * num_tri_vert_info) + 164] = curve_vertices_3D[2 + 9 * (i)]; // v1.z
		// rgb
		cur3D_vert[(i * num_tri_vert_info) + 165] = curve_vertices_3D[3 + 9 * (i)];
		cur3D_vert[(i * num_tri_vert_info) + 166] = curve_vertices_3D[4 + 9 * (i)];
		cur3D_vert[(i * num_tri_vert_info) + 167] = curve_vertices_3D[5 + 9 * (i)];
		//v2	
		cur3D_vert[(i * num_tri_vert_info) + 171] = curve_vertices_3D[0 + 9 * (i + 1)]; // v1.x
		cur3D_vert[(i * num_tri_vert_info) + 172] = 0; // v1.y
		cur3D_vert[(i * num_tri_vert_info) + 173] = curve_vertices_3D[2 + 9 * (i + 1)]; // v1.z
		// rgb
		cur3D_vert[(i * num_tri_vert_info) + 174] = curve_vertices_3D[3 + 9 * (i + 1)];
		cur3D_vert[(i * num_tri_vert_info) + 175] = curve_vertices_3D[4 + 9 * (i + 1)];
		cur3D_vert[(i * num_tri_vert_info) + 176] = curve_vertices_3D[5 + 9 * (i + 1)];
		//v1 - back	
		cur3D_vert[(i * num_tri_vert_info) + 180] = curve_vertices_3D[0 + 9 * (i)]; // v1.x
		cur3D_vert[(i * num_tri_vert_info) + 181] = 0; // v1.y
		cur3D_vert[(i * num_tri_vert_info) + 182] = curve_vertices_3D[2 + 9 * (i)] + thickness; // v1.z
		// rgb
		cur3D_vert[(i * num_tri_vert_info) + 183] = curve_vertices_3D[3 + 9 * (i)];
		cur3D_vert[(i * num_tri_vert_info) + 184] = curve_vertices_3D[4 + 9 * (i)];
		cur3D_vert[(i * num_tri_vert_info) + 185] = curve_vertices_3D[5 + 9 * (i)];
		// Calculate normal for Triangle 7: 
		glm::vec3 v71 = glm::vec3(cur3D_vert[(i * num_tri_vert_info) + 171] - cur3D_vert[(i * num_tri_vert_info) + 162],
			cur3D_vert[(i * num_tri_vert_info) + 172] - cur3D_vert[(i * num_tri_vert_info) + 163],
			cur3D_vert[(i * num_tri_vert_info) + 173] - cur3D_vert[(i * num_tri_vert_info) + 164]);
		glm::vec3 v72 = glm::vec3(cur3D_vert[(i * num_tri_vert_info) + 180] - cur3D_vert[(i * num_tri_vert_info) + 162],
			cur3D_vert[(i * num_tri_vert_info) + 181] - cur3D_vert[(i * num_tri_vert_info) + 163],
			cur3D_vert[(i * num_tri_vert_info) + 182] - cur3D_vert[(i * num_tri_vert_info) + 164]);
		glm::vec3 n7 = normalize(cross(v71, v72));
		// normal
		cur3D_vert[(i * num_tri_vert_info) + 168] = -n7.x;
		cur3D_vert[(i * num_tri_vert_info) + 169] = -n7.y;
		cur3D_vert[(i * num_tri_vert_info) + 170] = -n7.z;
		// normal
		cur3D_vert[(i * num_tri_vert_info) + 177] = -n7.x;
		cur3D_vert[(i * num_tri_vert_info) + 178] = -n7.y;
		cur3D_vert[(i * num_tri_vert_info) + 179] = -n7.z;
		// normal
		cur3D_vert[(i * num_tri_vert_info) + 186] = -n7.x;
		cur3D_vert[(i * num_tri_vert_info) + 187] = -n7.y;
		cur3D_vert[(i * num_tri_vert_info) + 188] = -n7.z;

		// Right
		//v1	
		cur3D_vert[(i * num_tri_vert_info) + 189] = curve_vertices_3D[0 + 9 * (i)]; // v1.x
		cur3D_vert[(i * num_tri_vert_info) + 190] = 0; // v1.y
		cur3D_vert[(i * num_tri_vert_info) + 191] = curve_vertices_3D[2 + 9 * (i)] + thickness; // v1.z
		// rgb
		cur3D_vert[(i * num_tri_vert_info) + 192] = curve_vertices_3D[3 + 9 * (i)];
		cur3D_vert[(i * num_tri_vert_info) + 193] = curve_vertices_3D[4 + 9 * (i)];
		cur3D_vert[(i * num_tri_vert_info) + 194] = curve_vertices_3D[5 + 9 * (i)];
		//v2	
		cur3D_vert[(i * num_tri_vert_info) + 198] = curve_vertices_3D[0 + 9 * (i + 1)]; // v1.x
		cur3D_vert[(i * num_tri_vert_info) + 199] = 0; // v1.y
		cur3D_vert[(i * num_tri_vert_info) + 200] = curve_vertices_3D[2 + 9 * (i + 1)] + thickness; // v1.z
		// rgb
		cur3D_vert[(i * num_tri_vert_info) + 201] = curve_vertices_3D[3 + 9 * (i + 1)];
		cur3D_vert[(i * num_tri_vert_info) + 202] = curve_vertices_3D[4 + 9 * (i + 1)];
		cur3D_vert[(i * num_tri_vert_info) + 203] = curve_vertices_3D[5 + 9 * (i + 1)];
		//v1 - back	
		cur3D_vert[(i * num_tri_vert_info) + 207] = curve_vertices_3D[0 + 9 * (i + 1)]; // v1.x
		cur3D_vert[(i * num_tri_vert_info) + 208] = 0; // v1.y
		cur3D_vert[(i * num_tri_vert_info) + 209] = curve_vertices_3D[2 + 9 * (i + 1)]; // v1.z
		// rgb
		cur3D_vert[(i * num_tri_vert_info) + 210] = curve_vertices_3D[3 + 9 * (i + 1)];
		cur3D_vert[(i * num_tri_vert_info) + 211] = curve_vertices_3D[4 + 9 * (i + 1)];
		cur3D_vert[(i * num_tri_vert_info) + 212] = curve_vertices_3D[5 + 9 * (i + 1)];
		// Calculate normal for Triangle 8: 
		glm::vec3 v81 = glm::vec3(cur3D_vert[(i * num_tri_vert_info) + 198] - cur3D_vert[(i * num_tri_vert_info) + 189],
			cur3D_vert[(i * num_tri_vert_info) + 199] - cur3D_vert[(i * num_tri_vert_info) + 190],
			cur3D_vert[(i * num_tri_vert_info) + 200] - cur3D_vert[(i * num_tri_vert_info) + 191]);
		glm::vec3 v82 = glm::vec3(cur3D_vert[(i * num_tri_vert_info) + 207] - cur3D_vert[(i * num_tri_vert_info) + 189],
			cur3D_vert[(i * num_tri_vert_info) + 208] - cur3D_vert[(i * num_tri_vert_info) + 190],
			cur3D_vert[(i * num_tri_vert_info) + 209] - cur3D_vert[(i * num_tri_vert_info) + 191]);
		glm::vec3 n8 = normalize(cross(v81, v82));
		// normal
		cur3D_vert[(i * num_tri_vert_info) + 195] = n8.x;
		cur3D_vert[(i * num_tri_vert_info) + 196] = n8.y;
		cur3D_vert[(i * num_tri_vert_info) + 197] = n8.z;
		// normal
		cur3D_vert[(i * num_tri_vert_info) + 204] = n8.x;
		cur3D_vert[(i * num_tri_vert_info) + 205] = n8.y;
		cur3D_vert[(i * num_tri_vert_info) + 206] = n8.z;
		// normal
		cur3D_vert[(i * num_tri_vert_info) + 213] = n8.x;
		cur3D_vert[(i * num_tri_vert_info) + 214] = n8.y;
		cur3D_vert[(i * num_tri_vert_info) + 215] = n8.z;
	}

	free(curve_vertices_3D);

	return cur3D_vert;
}


void VAOsObj()
{
	// Obj VAOs: 

	//2D version
	//FOR DROP
	std::vector<point> ctrl_points;
	ctrl_points.push_back(point(5.f, 0.f, 0.f));
	ctrl_points.push_back(point(4.f, 5.f, 0.f));
	ctrl_points.push_back(point(-5.f, 0.f, 0.f));
	//2D version
	std::vector<point> curve = EvaluateBezierCurve(ctrl_points, num_evals);
	//generate vertex attributes for curve
	int num_curve_verts = 0;
	int num_curve_floats = 0;
	float* curve_vertices = MakeFloatsFromVector(curve, num_curve_verts, num_curve_floats, 0.f, 1.f, 1.f, 0, 0, 1); //normal: x:-l+r, y: +t-b, z: +f-b
	//2D version
	std::vector<point> curve_2D = EvaluateBezierCurve(ctrl_points, num_evals);
	//generate vertex attributes for curve
	int num_curve_verts_2D = 0;
	int num_curve_floats_2D = 0;
	float* curve_vertices_2D = MakeFloatsFromVector(curve_2D, num_curve_verts_2D, num_curve_floats_2D, 0.f, 1.f, 1.f, 0, 0, 1); //normal: x:-l+r, y: +t-b, z: +f-b
	float* cur2D_vert = makeCurve2D(curve_vertices_2D);


	//3D version
	// FOR CURVE Mountain
	std::vector<point> ctrl_points_3D;
	ctrl_points_3D.push_back(point(7.f, 0.0f, 0.f));
	ctrl_points_3D.push_back(point(5.f, 5.f, 0.f));
	ctrl_points_3D.push_back(point(4.f, -3.f, 0.f));
	ctrl_points_3D.push_back(point(3.f, 1.f, 0.f));
	ctrl_points_3D.push_back(point(1.f, 19.f, 0.f));
	ctrl_points_3D.push_back(point(0.f, -4.f, 0.f));
	ctrl_points_3D.push_back(point(-1.f, -1.f, 0.f));
	ctrl_points_3D.push_back(point(-2.f, 3.f, 0.f));
	ctrl_points_3D.push_back(point(-3.f, 8.f, 0.f));
	ctrl_points_3D.push_back(point(-7.f, 0.f, 0.f));
	// 3D Vertion -- mountain
	std::vector<point> curve_3D = EvaluateBezierCurve(ctrl_points_3D, num_evals);
	//generate vertex attributes for curve
	int num_curve_verts_3D = 0;
	int num_curve_floats_3D = 0;
	float* curve_vertices_3D = MakeFloatsFromVector(curve_3D, num_curve_verts_3D, num_curve_floats_3D, 0.f, 1.f, 0.f, 0, 0, 1); //normal: x:-l+r, y: +t-b, z: +f-b
	float* cur3D_vert = makeCurve3DCloud(curve_vertices_3D);



	// FOR CURVE Cloud
	std::vector<point> ctrl_points_3D_m;
	ctrl_points_3D_m.push_back(point(7.f, 0.0f, 0.f));
	ctrl_points_3D_m.push_back(point(5.f, 5.f, 0.f));
	ctrl_points_3D_m.push_back(point(4.f, -3.f, 0.f));
	ctrl_points_3D_m.push_back(point(3.f, 1.f, 0.f));
	ctrl_points_3D_m.push_back(point(1.f, 20.f, 0.f));
	ctrl_points_3D_m.push_back(point(0.f, -4.f, 0.f));
	ctrl_points_3D_m.push_back(point(-1.f, -1.f, 0.f));
	ctrl_points_3D_m.push_back(point(-2.f, 3.f, 0.f));
	ctrl_points_3D_m.push_back(point(-3.f, 8.f, 0.f));
	ctrl_points_3D_m.push_back(point(-7.f, 0.f, 0.f));
	// 3D Vertion -- cloud
	std::vector<point> curve_3D_cloud = EvaluateBezierCurve(ctrl_points_3D_m, num_evals);
	//generate vertex attributes for curve
	int num_curve_verts_3D_cloud = 0;
	int num_curve_floats_3D_cloud = 0;
	float* curve_vertices_3D_cloud = MakeFloatsFromVector(curve_3D_cloud, num_curve_verts_3D_cloud, num_curve_floats_3D_cloud, 1.0f, 1.0f, 1.0f, 0, 0, 1); //normal: x:-l+r, y: +t-b, z: +f-b
	float* cur3D_vert_cloud = makeCurve3DCloud(curve_vertices_3D_cloud);


	// --- OBJ ---
	num_obj = sizeof(obj_Verts); // from drawObj


	glCreateBuffers(NUM_BUFFERS, Buffers);


	// obj 1 Cube Floor Wall
	glNamedBufferStorage(Buffers[0], sizeof(vertices), vertices, 0);
	glGenVertexArrays(NUM_VAOS, VAOs);
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(float)), (void*)0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (6 * sizeof(float)), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(float)), (void*)(3 * sizeof(float)));
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (6 * sizeof(float)), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(float)), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// obj carat
	glNamedBufferStorage(Buffers[1], sizeof(crt_vert), crt_vert, 0);
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(float)), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(float)), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(float)), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// obj grass
	glNamedBufferStorage(Buffers[2], sizeof(grs_vert), grs_vert, 0);
	glBindVertexArray(VAOs[2]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[2]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(float)), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(float)), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(float)), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// obj circle --> Prism  
	glNamedBufferStorage(Buffers[3], sizeof(float) * prs_num_segs * 4 * 9 * 3, cirP_vert, 0);
	//glNamedBufferStorage(Buffers[3], sizeof(float) * num_segs * 9 * 3, cirP_vert, 0);
	glBindVertexArray(VAOs[3]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[3]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(float)), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(float)), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(float)), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//obj curve --> 2D one side plane
	glBindVertexArray(VAOs[4]);
	glNamedBufferStorage(Buffers[4], sizeof(float) * (num_curve_floats * 2 * 3), cur2D_vert, 0);
	//glNamedBufferStorage(Buffers[4], sizeof(float) * num_curve_floats, curve_vertices, 0);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[4]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(float)), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(float)), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(float)), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//obj curve --> 3D -- cloud
	glBindVertexArray(VAOs[5]);
	glNamedBufferStorage(Buffers[5], sizeof(float) * (num_curve_floats_3D * 8 * 3), cur3D_vert_cloud, 0);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[5]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(float)), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(float)), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(float)), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// obj cylinder
	glNamedBufferStorage(Buffers[6], sizeof(float) * cld_num_segs * 4 * 9 * 3, cld_vert, 0);
	glBindVertexArray(VAOs[6]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[6]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(float)), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(float)), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(float)), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//obj curve --> 3D --> green
	glBindVertexArray(VAOs[7]);
	glNamedBufferStorage(Buffers[7], sizeof(float) * (num_curve_floats_3D * 8 * 3), cur3D_vert, 0);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[7]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(float)), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(float)), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(float)), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// texture plane
	glBindVertexArray(VAOs[8]);
	glNamedBufferStorage(Buffers[8], sizeof(vert_plane), vert_plane, 0);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[8]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (11 * sizeof(float)), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (11 * sizeof(float)), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, (11 * sizeof(float)), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, (11 * sizeof(float)), (void*)(9 * sizeof(float)));
	glEnableVertexAttribArray(3);

	//  OBJ
	glBindVertexArray(VAOs[9]);
	glNamedBufferStorage(Buffers[9], sizeof(obj_Verts), obj_Verts, 0);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[9]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(float)), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(float)), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, (9 * sizeof(float)), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// texture cube -- building
	glBindVertexArray(VAOs[10]);
	glNamedBufferStorage(Buffers[10], sizeof(vert_plane), vert_plane, 0);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[10]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (11 * sizeof(float)), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (11 * sizeof(float)), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, (11 * sizeof(float)), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, (11 * sizeof(float)), (void*)(9 * sizeof(float)));
	glEnableVertexAttribArray(3);


	glEnable(GL_DEPTH_TEST);


	// 3D free move to function makeCurve3DCloud() && makeCurve2D()
	//free(curve_vertices);
	//free(curve_vertices_3D);
	//free(obj_vert);
}