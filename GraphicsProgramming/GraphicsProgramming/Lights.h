#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Vector3.h"
#include "Input.h"


class Lights
{
public:
	Lights();
	~Lights();



	void input(Input* input, float dt);
	Vector3 light4_pos, light4_dif;


	void render();
	void sunUpdate(float dt);
	void renderSun();

private:
	GLfloat angle = 0.0, angle_stepsize = 0.05, radius = 8;
	float orbitSpeed = 3;
	float orbitx, orbity;

};

