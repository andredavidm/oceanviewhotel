#pragma once
#include "Camera.h"
#include "glut.h"
#include <vector>
#include "Vector3.h"
#include <iostream>
#include "Input.h"

class Camera
{
public:
	Camera();
	~Camera();

	void update();
	void input(Input* input, float dt);
	bool locked = false;

	Vector3 pos;
private:

	//Calculations Variables
	float posX=0, posY=0, posZ=0;
	float lx, ly, lz;
	float upx, upy, upz;

	Vector3 forward, lookAt, up;
	float yaw, roll, pitch;
	float speed;

	//Input Variables
	int mousePosX;
	int mousePosY;
	float distanceX;
	float distanceY;
	
	//NEEDS FIXING
	int width = 1200;
	int height = 640;


};

