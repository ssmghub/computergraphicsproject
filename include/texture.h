#pragma once

#include <iostream>
#include "bitmap.h"

GLuint setup_texture(const char* filename)
{
	// enable textures
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	//generate an OpenGL texture object
	GLuint texObject;
	glGenTextures(1, &texObject);
	glBindTexture(GL_TEXTURE_2D, texObject);
	//Next set some parameters for how OpenGL will draw the texture.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	//Then load the bitmap file, which is at the location stored in the input argument filename
	unsigned char* pxls = NULL; 
	BITMAPINFOHEADER info;
	BITMAPFILEHEADER file;
	// GLuint loadbitmap(filename, pixelBuffer, infoHeader, fileHeader); 
	loadbitmap(filename, pxls, &info, &file); 

	if (pxls != NULL)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, info.biWidth, info.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, pxls); 
	}
	glGenerateMipmap(GL_TEXTURE_2D); 

	delete[] pxls;
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	return texObject;
	//return 0;
}

GLuint setup_mipmaps(const char* filename[], int n)
{
	// enable textures
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	//generate an OpenGL texture object
	GLuint texObject;
	glGenTextures(1, &texObject);
	glBindTexture(GL_TEXTURE_2D, texObject);
	//Next set some parameters for how OpenGL will draw the texture.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
	//Then load the bitmap file, which is at the location stored in the input argument filename
	unsigned char* pxls[16];
	BITMAPINFOHEADER info[16];
	BITMAPFILEHEADER file[16];
	// GLuint loadbitmap(filename, pixelBuffer, infoHeader, fileHeader); 
	for (int c = 0; c < n; c++)
	{
		loadbitmap(filename[c], pxls[c], &info[c], &file[c]);

		if (pxls != NULL)
		{
			glTexImage2D(GL_TEXTURE_2D, c, GL_RGB, info[c].biWidth, info[c].biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, pxls[c]);
		}
		delete[] pxls[c];
	}
	
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	return texObject;
}
