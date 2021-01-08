#include "Lights.h"

Lights::Lights() {


}

Lights::~Lights() {

}


void Lights::input(Input* input, float dt) {
	
	//speeds up orbit
	if (input->isKeyDown(111)) {

		sunUpdate(dt);
		sunUpdate(dt);
		sunUpdate(dt);

	}

}
void Lights::render() {
	

	
	//FanLight1
	GLfloat	Light_Ambient1[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat Light_Diffuse1[] = { 0.8f, 0.8f, 0.85f, 1.0f };

	GLfloat Light_Position1[] = { 2.f, 2.98f, 5.f, 1.0f };
	GLfloat Light_Direction1[] = { 0.0f, -1.0f, 0.0f };



	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.f);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Light_Direction1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Light_Diffuse1);
	glLightfv(GL_LIGHT1, GL_POSITION, Light_Position1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, Light_Ambient1);


	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.3);

	glEnable(GL_LIGHT1);


	//FanLight2
	GLfloat	Light_Ambient2[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat Light_Diffuse2[] = { 0.8f, 0.8f, 0.85f, 1.0f };

	GLfloat Light_Position2[] = { 2.f, 2.98f, 8.f, 1.0f };
	GLfloat Light_Direction2[] = { 0.0f, -1.0f, 0.0f };



	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 45.f);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, Light_Direction2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, Light_Diffuse2);
	glLightfv(GL_LIGHT2, GL_POSITION, Light_Position2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, Light_Ambient2);


	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.5);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.3);

	glEnable(GL_LIGHT2);

	
}


void Lights::sunUpdate(float dt) {

	//updates sun orbit
	orbity = radius* sin(angle);
	orbitx = radius * cos(angle);
	angle = angle - angle_stepsize * dt * orbitSpeed;

	light4_pos.x = orbitx;
	light4_pos.y = orbity;
	light4_pos.z = 6;
	

	light4_dif.x = (light4_pos.y / radius);
	light4_dif.y = (light4_pos.y / radius);
	light4_dif.z = (light4_pos.y / radius);

	if (light4_pos.y > 0) {
		light4_dif.x = (light4_pos.y / radius) * 0.5;
		light4_dif.y = (light4_pos.y / radius) * 0.35;
		light4_dif.z = (light4_pos.y / radius) * 0.15;
	}
}

void Lights::renderSun() {

	//Sunlight global
	GLfloat	Light_Ambient4[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat Light_Diffuse4[] = { light4_dif.x , light4_dif.y, light4_dif.z, 1.0f };

	GLfloat Light_Position4[] = { light4_pos.x, light4_pos.y, light4_pos.z, 0.0f };


	glLightfv(GL_LIGHT4, GL_DIFFUSE, Light_Diffuse4);
	glLightfv(GL_LIGHT4, GL_POSITION, Light_Position4);
	glLightfv(GL_LIGHT4, GL_AMBIENT, Light_Ambient4);


	glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, 0.5);
	glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 0.2);

	glEnable(GL_LIGHT4);


}