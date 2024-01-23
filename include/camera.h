#pragma once

#include <stdio.h>
#include <glm/glm.hpp>



struct SCamera
{
	enum Camera_Movement
	{
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;

	glm::vec3 WorldUp;

	float Yaw;
	float Pitch;

	const float MovementSpeed = 0.5f;
	//const float MovementSpeed = 5.5f;
	float MouseSensitivity = 1.f;



};


void InitCamera(SCamera& in)
{
	//in.Front = glm::vec3(0.0f, 0.0f, -1.0f);
	in.Front = glm::vec3(0.0f, 0.0f, -1.0f);
	in.Position = glm::vec3(0.0f, -7.0f, -7.0f);
	//in.Position = glm::vec3(0.0f, 100.0f, 0.0f);
	in.Up = glm::vec3(0.0f, 1.0f, 0.0f);
	in.WorldUp = in.Up;
	in.Right = glm::normalize(glm::cross(in.Front, in.WorldUp));

	in.Yaw = -90.f;
	in.Pitch = 0.f;
}

float cam_dist = 7.f;

//#define DEG2RAD(n)	n*(M_PI/180)

void MoveAndOrientCamera(SCamera& in, glm::vec3 target, float distance, float xoffset, float yoffset)
{
	in.Yaw -= xoffset * in.MovementSpeed; 
	in.Pitch -= yoffset * in.MovementSpeed;	

	if (in.Pitch > 89.0f)	in.Pitch = 89.0f;
	if (in.Pitch < -89.0f)	in.Pitch = -89.0f;

	//distance = distance * in.Position.z; 

	//in.Yaw -= xoffset; 
	//in.Pitch -= yoffset; 

	//in.Position = glm::vec3(cos(DEG2RAD(in.Yaw))* sin(DEG2RAD(in.Pitch)), 
	//	sin(DEG2RAD(in.Pitch)), sin(DEG2RAD(in.Yaw))* cos(DEG2RAD(in.Pitch))); 

	in.Position.x = cos(glm::radians(in.Yaw)) * cos(glm::radians(in.Pitch));
	in.Position.y = sin(glm::radians(in.Pitch));
	in.Position.z = sin(glm::radians(in.Yaw)) * cos(glm::radians(in.Pitch)); // * distance;
	
	in.Position = in.Position * distance;

	//in.Front = glm::vec3(0.0f, 0.0f, 1.0f);
	in.Front = glm::normalize(target - in.Position);
	in.Right = glm::cross(in.Front, in.WorldUp);
	in.Up = glm::cross(in.Right, in.Front);

}