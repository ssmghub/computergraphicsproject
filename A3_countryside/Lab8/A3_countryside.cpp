#define _USE_MATH_DEFINES 
#define DEG2RAD(n)	n*(M_PI/180)
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "camera.h"
#include "error.h"
#include "shader.h"
#include "shadow.h"
#include "texture.h"
#include "casteljau_3d.h"
#include "point.h"
#include "vertObj.h"
#include "drawObj.h"
#include "VAOsObj.h"
#include "Texture.h"
#include "objParse.h"

//light direction variable here
glm::vec3 lightDirection = glm::vec3(0.1f, -.81f, -.61f);
glm::vec3 lightPos = glm::vec3(.2f, .6f, .7f);

glm::vec3 lightDirection1 = glm::vec3(0.1f, -.81f, -.61f);
glm::vec3 lightPos1 = glm::vec3(.2f, .6f, .7f);

glm::vec3 lightDirection2 = glm::vec3(0.0f, -1.0f, 0.0f);
glm::vec3 lightPos2 = glm::vec3(.2f, .6f, .7f);

// for light 2 spot control
bool isSpotLight = false;

SCamera Camera;

// Obj VAOs: 
/*
#define NUM_BUFFERS 5
#define NUM_VAOS 5
GLuint Buffers[NUM_BUFFERS];
GLuint VAOs[NUM_VAOS];
*/

#define WIDTH 2000
#define HEIGHT 1700
//#define WIDTH 1024
//#define HEIGHT 768
#define SH_MAP_WIDTH 2048
#define SH_MAP_HEIGHT 2048




void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		lightDirection = Camera.Front;
		lightPos = Camera.Position;
	}

	float x_offset = 0.f;
	float y_offset = 0.f;
	bool cam_changed = false;
	if (key == GLFW_KEY_RIGHT && action == GLFW_REPEAT)
	{
		x_offset = 1.f;
		y_offset = 0.f;
		cam_changed = true;
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_REPEAT)
	{
		x_offset = -1.f;
		y_offset = 0.f;
		cam_changed = true;
	}
	if (key == GLFW_KEY_UP && action == GLFW_REPEAT)
	{
		x_offset = 0.f;
		y_offset = -1.f;
		cam_changed = true;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_REPEAT)
	{
		x_offset = 0.f;
		y_offset = 1.f;
		cam_changed = true;
	}
	if (key == GLFW_KEY_R && action == GLFW_REPEAT)
	{
		cam_dist -= 0.1f;
		cam_changed = true;
	}
	if (key == GLFW_KEY_F && action == GLFW_REPEAT)
	{
		cam_dist += 0.1f;
		cam_changed = true;
	}
	//bool isMove = false;
	if (key == GLFW_KEY_M && action == GLFW_PRESS)
	{
		// "isMove" is from drawObj.h
		if (!isMove)
		{
			isMove = true;

		}
		else {
			isMove = false;

		}
	}
	if (cam_changed)
	{
		MoveAndOrientCamera(Camera, glm::vec3(0.f, 0.f, 0.f), cam_dist, x_offset, y_offset);
	}

	// for light 2 -- spot control
	if (key == GLFW_KEY_I && action == GLFW_PRESS)
	{
		// "isMove" is from drawObj.h
		if (!isSpotLight)
		{
			isSpotLight = true;
			lightDirection2 = Camera.Front;
			lightPos2 = Camera.Position;
		}
		else {
			isSpotLight = false;
		}
	}
	if (cam_changed)
	{
		MoveAndOrientCamera(Camera, glm::vec3(0.f, 0.f, 0.f), cam_dist, x_offset, y_offset);
	}
}

void SizeCallback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}

void renderWithShadow(unsigned int program, ShadowStruct shadow, glm::mat4 projectedLightSpaceMatrix, GLuint* tex) //)
{
	//set the view transformation back to using the screen dimensions
	glViewport(0, 0, WIDTH, HEIGHT);
	
	static const GLfloat bgd[] = { .8f, .8f, .8f, 1.f };
	glClearBufferfv(GL_COLOR, 0, bgd);
	glClear(GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glUseProgram(program);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, shadow.Texture);
	glUniform1i(glGetUniformLocation(program, "Texture"), 0);

	// copy the following vectors to uniforms in the shaders 
	glUniformMatrix4fv(glGetUniformLocation(program, "projectedLightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(projectedLightSpaceMatrix));
	

	// For light 2 control:
	GLint isSpotLight_frag = glGetUniformLocation(program, "isSpotLight");
	glUniform1i(isSpotLight_frag, isSpotLight);
	
	//Lights
	// Set light1 properties
	GLint light1Dir = glGetUniformLocation(program, "lightDirection");
	GLint light1ColorLoc = glGetUniformLocation(program, "lightColour");
	GLint light1PosLoc = glGetUniformLocation(program, "lightPos");
	glUniform3f(light1Dir, lightDirection.x, lightDirection.y, lightDirection.z);
	glUniform3f(light1ColorLoc, 1.f, 1.f, 0.8f);
	glUniform3f(light1PosLoc, lightPos.x, lightPos.y, lightPos.z);

	// Set light2 properties -- Static
	GLint light1Dir1 = glGetUniformLocation(program, "lightDirection1");
	GLint light1ColorLoc1 = glGetUniformLocation(program, "lightColour1");
	GLint light1PosLoc1 = glGetUniformLocation(program, "lightPos1");
	glUniform3f(light1Dir1, lightDirection1.x, lightDirection1.y, lightDirection1.z);
	glUniform3f(light1ColorLoc1, 1.f, 1.f, 0.5f);
	glUniform3f(light1PosLoc1, lightPos1.x, lightPos1.y, lightPos1.z);

	// Set light3 properties -- Static -- Spot
	GLint light1Dir2 = glGetUniformLocation(program, "lightDirection2");
	GLint light1ColorLoc2 = glGetUniformLocation(program, "lightColour2");
	GLint light1PosLoc2 = glGetUniformLocation(program, "lightPos12");
	glUniform3f(light1Dir2, lightDirection2.x, lightDirection2.y, lightDirection2.z);
	glUniform3f(light1ColorLoc2, 1.f, 1.f, 1.1f);
	glUniform3f(light1PosLoc2, lightPos2.x, lightPos2.y, lightPos2.z);

	glm::mat4 view = glm::mat4(1.f);
	view = glm::lookAt(Camera.Position, Camera.Position + Camera.Front, Camera.Up);
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 projection = glm::mat4(1.f);
	projection = glm::perspective(glm::radians(45.f), (float)WIDTH / (float)HEIGHT, .01f, 100.f);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	drawFloorAndCubes(program, VAOs[0]);
	drawCarat(program, VAOs[1]);
	drawGrass(program, VAOs[2]);
	//drawCirPrism(program, VAOs[3]);
	//drawCurve(program, VAOs[4]);
	drawMountain(program, VAOs[7]);
	drawCurve3DCloud(program, VAOs[5]);
	drawCylinder(program, VAOs[6]);
	drawHouse(program, VAOs[3], VAOs[0]);
	drawPlanewithTex(program, VAOs[8],tex);
	drawObj(program, VAOs[9], tex[1]);
	drawPillar(program, VAOs[6]);
}

void generateDepthMap(unsigned int shadowShaderProgram, ShadowStruct shadow, glm::mat4 projectedLightSpaceMatrix, GLuint* tex) //)
{
	//specify the transformation from NDC to screen space 
	glViewport(0, 0, SH_MAP_WIDTH, SH_MAP_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, shadow.FBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	//Enable the new shader program
	glUseProgram(shadowShaderProgram);
	//Load the projected light space matrix as a uniform to the shader uniform.
	glUniformMatrix4fv(glGetUniformLocation(shadowShaderProgram, "projectedLightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(projectedLightSpaceMatrix));
	
	drawFloorAndCubes(shadowShaderProgram, VAOs[0]);
	drawCarat(shadowShaderProgram, VAOs[1]);
	drawGrass(shadowShaderProgram, VAOs[2]);
	drawCurve3DCloud(shadowShaderProgram, VAOs[5]);
	drawCylinder(shadowShaderProgram, VAOs[6]);
	drawHouse(shadowShaderProgram, VAOs[3], VAOs[0]);
	drawMountain(shadowShaderProgram, VAOs[7]);
	drawPlanewithTex(shadowShaderProgram, VAOs[8], tex);
	drawObj(shadowShaderProgram, VAOs[9], tex[1]);
	drawPillar(shadowShaderProgram, VAOs[6]);

	//Unbind our framebuffer object so that OpenGL uses the default frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


int main(int argc, char** argv)
{
	glfwInit();

	// Antianalization
	glfwWindowHint(GL_MAX_SAMPLES, 8);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "City", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetWindowSizeCallback(window, SizeCallback);

	gl3wInit();


	// Antianalization                          /////////////////
	//glEnable(GL_MULTISAMPLE); 
	int max_samples;
	glGetIntegerv(GL_MAX_SAMPLES, &max_samples);
	printf("max samples supported = %d\n", max_samples);


	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(DebugCallback, 0);

	ShadowStruct shadow = setup_shadowmap(SH_MAP_WIDTH, SH_MAP_HEIGHT);

	GLuint program = CompileShader("phong.vert", "phong.frag");
	GLuint shadow_program = CompileShader("shadow.vert", "shadow.frag");

	InitCamera(Camera);
	cam_dist = 7.f;
	MoveAndOrientCamera(Camera, glm::vec3(0, 0, 0), cam_dist, 0.f, 0.f);

	GLuint t1 = setup_texture("Assert/sky_texture2.bmp");
	GLuint t2 = setup_texture("Assert/wood.bmp");
	GLuint t3 = setup_texture("Assert/wood2.bmp");

	GLuint texture[] = {
		t1,t2,
	};

	// Obj VAOs: (with head definition: ...)
	VAOsObj();

	glEnable(GL_DEPTH_TEST);
	//curve
	glPointSize(8);

	while (!glfwWindowShouldClose(window))
	{
		float near_plane = 1.0f, far_plane = 70.5f;
		glm::mat4 lightProjection = glm::ortho(-15.0f, 15.0f, -15.0f, 15.0f, near_plane, far_plane); // change volumn
		glm::mat4 lightView = glm::lookAt(lightPos, lightPos + lightDirection, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 projectedLightSpaceMatrix = lightProjection * lightView;
		
		generateDepthMap(shadow_program, shadow, projectedLightSpaceMatrix, texture);
		renderWithShadow(program, shadow, projectedLightSpaceMatrix, texture);

		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	// for Parsing OBJ files
	main_forParse();

	glfwDestroyWindow(window);
	glfwTerminate();

	free(cirP_vert);
	free(cld_vert);
	return 0;
}