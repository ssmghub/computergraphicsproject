#pragma once
#include "file.h"

GLuint CompileShader(const char* vsFilename, const char* fsFilename)
{
	int success;
	char infoLog[512];

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	char* vertexShaderSource = read_file(vsFilename);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		fprintf(stderr, "Vertex Shader Compiation Fail - %s\n", infoLog);
	}

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	char* fragmentShaderSource = read_file(fsFilename);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		fprintf(stderr, "Fragment Shader Compiation Fail - %s\n", infoLog);
	}

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		fprintf(stderr, "Shader Program Link Fail - %s\n", infoLog);
	}

	free(fragmentShaderSource);
	free(vertexShaderSource);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//LoadShader();

	return shaderProgram;
}