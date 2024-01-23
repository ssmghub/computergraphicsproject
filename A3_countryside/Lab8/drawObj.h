#pragma once
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// For OBJ
int num_obj;

// for control animation
bool isMove = false;



void drawFloorAndCubes(unsigned int shaderProgram, float vao)
{
	glBindVertexArray(vao); // dont need change waiting for sky obj
	
	//floor
	glm::mat4 model = glm::mat4(1.f);
	//model = glm::translate(model, glm::vec3(0, -8, 0));
	model = glm::translate(model, glm::vec3(0, -5, 35)); // x+: move left, y+: move up, z+: move forward
	model = glm::scale(model, glm::vec3(120, 0.3, 120));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36); // 36 = 12*3 = 6*2*3 ; cube: 6 faces 
	
	//back wall
	glm::mat4 modelb = glm::mat4(1.f);
	modelb = glm::translate(modelb, glm::vec3(-1, 0, 60)); // x+: move left, y+: move up, z+: move forward
	modelb = glm::scale(modelb, glm::vec3(30, 20, 0.3f));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelb));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// for translate
	float i = 1.0f;
	float j = -4.0f;
	float k = 10.0f;
	// stairs
	int stairNum2 = 2;
	int a = 1; // stair num of first floor
	int b = stairNum2 - a; // null cube num of first floor stair
	for (int m = 0; m < stairNum2; m++)
	{
		for (int n = 0; n < a; n++)
		{
			j += 0.7f;
			k += 1.5f;
			glm::mat4 modeli = glm::mat4(1.f);
			modeli = glm::translate(modeli, glm::vec3(-1, -0.7f + j, k+39));
			modeli = glm::scale(modeli, glm::vec3(50, i, 17.f));
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modeli));
			glDrawArrays(GL_TRIANGLES, 0, 54);
		}
		a += 1;
	}

}

void drawCarat(unsigned int shaderProgram, float vao)
{
	//rorating carat
	//DECLARE POSITION VARIABLES HERE
	glm::vec3 oct_pos = glm::vec3(0, 0.f, 20);

	//SET UP AND COPY MODEL MATRIX HERE
	glm::mat4 model = glm::mat4(1.f);

	//MOVE ANIMATION:
	model = glm::translate(model, oct_pos); //move on Z = -5.f
	model = glm::scale(model, glm::vec3(1.3, 1.3, 1.3));
	model = glm::rotate(model, (float)glfwGetTime() / 2, glm::vec3(0.f, 1.f, 0.f)); //rotate on y-axis by using glfwGetTime(); 
	int mloc = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));

	// Bind carat Vertex Array
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 14 * 3); // draw 14 triangles */

}

void drawGrass(unsigned int shaderProgram, float vao)
{
	glBindVertexArray(vao);

	// Left Grass
	for (int i = 7; i < 8; i++) // -left and right
	{
		for (int j = -1; j < 0; j++) // up & down
		{
			for (int k = -3; k < 5; k++) // -forward and back
			{
				float jj = j * 0.43 - 4;
				float kk = k * 6;
				//outside
				glm::mat4 modelO = glm::mat4(1.f);
				modelO = glm::translate(modelO, glm::vec3(float(i), float(jj), float(kk)));
				modelO = glm::scale(modelO, glm::vec3(1.1f, 1.f, 1.1f));
				modelO = glm::rotate(modelO, glm::radians(45.f), glm::vec3(0.f, 1.f, 0.f)); //rotate on y-axis by using glfwGetTime(); 
				glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelO));
				glDrawArrays(GL_TRIANGLES, 0, 54);
				//inside
				glm::mat4 modelI = glm::mat4(1.f);
				modelI = glm::translate(modelI, glm::vec3(float(i), float(jj) + 0.07f, float(kk)));
				
				if(isMove)
				{
					modelI = glm::scale(modelI, glm::vec3(abs(sin((float)glfwGetTime())), abs(sin((float)glfwGetTime())) + 0.3f, abs(sin((float)glfwGetTime()))));
				}
				else
				{
					modelI = glm::scale(modelI, glm::vec3(1, 1.3, 1));
				}
				int mloc = glGetUniformLocation(shaderProgram, "model");
				glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(modelI));
				glDrawArrays(GL_TRIANGLES, 0, 54);
			}
		}
	}

	// Right Grass
	for (int i = -7; i < -6; i++) // -left and right
	{
		for (int j = -1; j < 0; j++) // up & down
		{
			for (int k = -3; k < 5; k++) // -forward and back
			{
				float jj = j * 0.43 - 4;
				float kk = k * 6;
				//outside
				glm::mat4 modelO = glm::mat4(1.f);
				modelO = glm::translate(modelO, glm::vec3(float(i), float(jj), float(kk)));
				modelO = glm::scale(modelO, glm::vec3(1.1f, 1.f, 1.1f));
				modelO = glm::rotate(modelO, glm::radians(45.f), glm::vec3(0.f, 1.f, 0.f)); //rotate on y-axis by using glfwGetTime(); 
				glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelO));
				glDrawArrays(GL_TRIANGLES, 0, 54);
				//inside
				glm::mat4 modelI = glm::mat4(1.f);
				modelI = glm::translate(modelI, glm::vec3(float(i), float(jj) + 0.07f, float(kk)));
				if (isMove)
				{
					modelI = glm::scale(modelI, glm::vec3(abs(sin((float)glfwGetTime())), abs(sin((float)glfwGetTime())) + 0.3f, abs(sin((float)glfwGetTime()))));
				}
				else
				{
					modelI = glm::scale(modelI, glm::vec3(1, 1.3, 1));
				}
				int mloc = glGetUniformLocation(shaderProgram, "model");
				glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(modelI));
				glDrawArrays(GL_TRIANGLES, 0, 54);
			}
		}
	}
}

void drawCirPrism(unsigned int shaderProgram, float vao)
{
	glBindVertexArray(vao);

	glm::mat4 model = glm::mat4(1.f);
	model = glm::translate(model, glm::vec3(0, 0, -3)); // x+: move left, y+: move up, z+: move forward
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, prs_num_segs * 4 * 9 * 3);
}

void drawCurve(unsigned int shaderProgram, float vao)
{
	int num_evals = 30; // change to PUBLIC eval in VAOsObj.h
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, (num_evals + 1) * 2 * 3);
	glDrawArrays(GL_LINE_STRIP, 0, (num_evals + 1) * 2 * 3);
}

void drawCylinder(unsigned int shaderProgram, float vao)
{
	glBindVertexArray(vao);

	glm::mat4 model = glm::mat4(1.f);
	// x+: move left, y+: move up, z+: move forward
	model = glm::translate(model, glm::vec3(0, -3.8, 20)); 
	model = glm::scale(model, glm::vec3(8, 1, 8));
	model = glm::rotate(model, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f)); //rotate on x-axis by using glfwGetTime(); 
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, cld_num_segs * 4 * 9 * 3);
}

void drawCurve3DCloud(unsigned int shaderProgram, float vao)
{	
	glUseProgram(shaderProgram);

	int num_evals = 128; // change to PUBLIC eval in VAOsObj.h
	glBindVertexArray(vao);

	// Cloud
	for (int i = -1; i < 2; i++) // -left and right
	{
		for (int k = 0; k < 2; k++) // -forward and back
		{
			glm::mat4 model = glm::mat4(1.f);
			if (isMove)
			{
				model = glm::translate(model, glm::vec3(0 + i * 25 + (7 * sin((float)glfwGetTime())), 18, 75 - k * 27));
			}
			else
			{
				model = glm::translate(model, glm::vec3(0 + i * 25, 18, 75 - k * 27));
			}
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, (num_evals + 1) * 8 * 3);
		}
	}
}

void drawHouse(unsigned int shaderProgram, float vao1, float vao2)
{
	// size scale
	float s = 1.2f;
	float i = 1;
	//float k = 1;
	for(int k = -1; k < 2; k++)
	{ 
		//roof
		glBindVertexArray(vao1);
		glm::mat4 model1 = glm::mat4(1.f);
		model1 = glm::translate(model1, glm::vec3(0 + i * 20, 4, 8 + k * 20)); // x+: move left, y+: move up, z+: move forward
		model1 = glm::scale(model1, glm::vec3(9 * s, 5 * s, 3.5 * s));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model1));
		//glBindVertexArray(VAOs[3]);
		glDrawArrays(GL_TRIANGLES, 0, prs_num_segs * 4 * 9 * 3);
		//cube
		glBindVertexArray(vao2);
		glm::mat4 model2 = glm::mat4(1.f);
		model2 = glm::translate(model2, glm::vec3(0 + i * 20, -1, 12 + k * 20)); // x+: move left, y+: move up, z+: move forward
		model2 = glm::scale(model2, glm::vec3(6 * s, 7 * s, 6 * s));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model2));
		glDrawArrays(GL_TRIANGLES, 0, 36); // 36 = 12*3 = 6*2*3 ; cube: 6 faces *
	}

	// Draw Building
	for (int k = -1; k < 1; k++)
	{
		//
		glBindVertexArray(vao2);
		glm::mat4 model2 = glm::mat4(1.f);
		model2 = glm::translate(model2, glm::vec3(-20, 2, 30 + k * 25)); // x+: move left, y+: move up, z+: move forward
		model2 = glm::scale(model2, glm::vec3(10, 20, 10));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model2));
		glDrawArrays(GL_TRIANGLES, 0, 36); // 36 = 12*3 = 6*2*3 ; cube: 6 faces *
	}

}

void drawMountain(unsigned int shaderProgram, float vao)
{
	int num_evals = 128; // change to PUBLIC eval in VAOsObj.h
	glBindVertexArray(vao);

	// Mountain
	glm::mat4 model = glm::mat4(1.f);
	model = glm::translate(model, glm::vec3(0, -5, 70.f));
	model = glm::scale(model, glm::vec3(7, 6, 1));
	model = glm::rotate(model, glm::radians(-8.f), glm::vec3(0.f, 1.f, 0.f));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, (num_evals + 1) * 8 * 3);

}

void drawPlanewithTex(unsigned int shaderProgram, float vao, GLuint* tex)
{
	glUseProgram(shaderProgram);
	glBindVertexArray(vao);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	glUniform1i(glGetUniformLocation(shaderProgram, "Texture"), 1);

	glm::mat4 model = glm::mat4(1.f);
	model = glm::translate(model, glm::vec3(-1, 3, 56)); // x+: move left, y+: move up, z+: move forward
	model = glm::scale(model, glm::vec3(16, 7, 1));
	//model = glm::rotate(model, glm::radians(-90.f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 2 * 3);

}

void drawObj(unsigned int shaderProgram, float vao , GLuint tex)
{
	glBindVertexArray(vao);
	//left
	for (int i = 12; i < 13; i++) // -left and right
	{
		for (int k = 6; k < 7; k++) // -forward and back
		{
			float kk = k * 8-10;
			glm::mat4 model = glm::mat4(1.f);
			model = glm::translate(model, glm::vec3(float(i), -5, kk));
			model = glm::scale(model, glm::vec3(2, 2, 2));
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, num_obj);

		}
	}
	//right
	for (int i = -12; i < -11; i++) // -left and right
	{
		for (int k = 6; k < 7; k++) // -forward and back
		{
			float kk = k * 8-10;
			glm::mat4 model = glm::mat4(1.f);
			model = glm::translate(model, glm::vec3(float(i), -5, kk));
			model = glm::scale(model, glm::vec3(2, 2, 2));
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, num_obj);

		}
	}
}

void drawPillar(unsigned int shaderProgram, float vao)
{
	glBindVertexArray(vao);
	//left
	for (int i = 9; i < 10; i++) // -left and right
	{
		for (int j = -1; j < 0; j++) // up & down
		{
			for (int k = -3; k < 5; k++) // -forward and back
			{
				float jj = j * 0.43 - 1.5;
				float kk = k * 6;

				glm::mat4 model = glm::mat4(1.f);
				// x+: move left, y+: move up, z+: move forward
				model = glm::translate(model, glm::vec3(float(i), jj, kk));
				//model = glm::translate(model, glm::vec3(0, -1.5, 0));
				model = glm::scale(model, glm::vec3(1, 2, 1));
				model = glm::rotate(model, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f)); //rotate on x-axis by using glfwGetTime(); 
				glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
				glDrawArrays(GL_TRIANGLES, 0, cld_num_segs * 4 * 9 * 3);

				glm::mat4 model1 = glm::mat4(1.f);
				// x+: move left, y+: move up, z+: move forward
				model1 = glm::translate(model1, glm::vec3(float(i), -1.1f + j * 0.43, kk));
				model1 = glm::scale(model1, glm::vec3(1.5, 0.2, 1.5));
				model1 = glm::rotate(model1, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f)); //rotate on x-axis by using glfwGetTime(); 
				glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model1));
				glDrawArrays(GL_TRIANGLES, 0, cld_num_segs * 4 * 9 * 3);

			}
		}
	}

	//right
	for (int i = -9; i < -8; i++) // -left and right
	{
		for (int j = -1; j < 0; j++) // up & down
		{
			for (int k = -3; k < 5; k++) // -forward and back
			{
				float jj = j * 0.43 - 1.5;
				float kk = k * 6;

				glm::mat4 model = glm::mat4(1.f);
				// x+: move left, y+: move up, z+: move forward
				model = glm::translate(model, glm::vec3(float(i), jj, kk));
				//model = glm::translate(model, glm::vec3(0, -1.5, 0));
				model = glm::scale(model, glm::vec3(1, 2, 1));
				model = glm::rotate(model, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f)); //rotate on x-axis by using glfwGetTime(); 
				glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
				glDrawArrays(GL_TRIANGLES, 0, cld_num_segs * 4 * 9 * 3);

				glm::mat4 model1 = glm::mat4(1.f);
				// x+: move left, y+: move up, z+: move forward
				model1 = glm::translate(model1, glm::vec3(float(i), -1.1f + j * 0.43, kk));
				model1 = glm::scale(model1, glm::vec3(1.5, 0.2, 1.5));
				model1 = glm::rotate(model1, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f)); //rotate on x-axis by using glfwGetTime(); 
				glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model1));
				glDrawArrays(GL_TRIANGLES, 0, cld_num_segs * 4 * 9 * 3);

			}
		}
	}
}
