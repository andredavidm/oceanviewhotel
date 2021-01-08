// Scene class. Configures a basic 3D scene.
// Interfaces with the Input class to handle user input
// Calculates and outputs Frames Per Second (FPS) rendered.
// Important functions are the constructor (initialising the scene), 
// update (for process user input and updating scene objects) and render (renders scene).
#ifndef _SCENE_H
#define _SCENE_H

// Include GLUT, openGL, input.
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
// Further includes should go here:
#include "SOIL.h"
#include <vector>
#include "Camera.h"
#include "RoomMaker.h"
#include "Lights.h"
#include "ProceduralGenerator.h"
#include "TextureLoader.h"
#include "ObjectMaker.h"
#include <iostream>
#include <array>
#include <cstdlib>
#include <time.h> 
#include "Shadow.h"
#include "Model.h"

class Scene{

public:
	Scene(Input *in);
	// Main render function
	void render();
	// Handle input function that receives delta time from parent.
	void handleInput(float dt);
	// Update function receives delta time from parent (used for frame independent updating).
	void update(float dt);
	// Resizes the OpenGL output based on new window size.
	void resize(int w, int h);
	float pos = 0.01;
	
	void updateLight_pos();

	int wireframe = 0;

	Camera camera;
	RoomMaker room;
	Lights lights;
	ProceduralGenerator pg;
	TextureLoader tx;
	GLuint lamp0;
	ObjectMaker obj;
	Model model;

	Shadow shadow;
	

	vector<Vector3> vertex, norms, texCoords;


	std::vector<float> caster_verts = { 0,2, 0, // 2.875f y value. Unit quad renders plane at a -2 y position.
							3, 2, 0,				// This disrupts everything being automatically in place and required		} - AMMEND : before implementing in final coursework.
							3, 2, 3,				// manual tracking of where this plane was after transforms and scaling.
							0, 2, 3 };






	float flooor[12] = { -1, 0.01, -1,
						 -1, 0.01,  1,
						  1, 0.01,  1,
						  1, 0.01, -1 };

	float walll[12] = { 4.99, -1, -1,
					    4.99, -1,  1,
					    4.99,  1,  1,
					    4.99,  1, -1 };

	
	void test();
	void test2();
protected:
	// configure opengl render pipeline
	void initialiseOpenGL();
	// Renders text (x, y positions, RGB colour of text, string of text to be rendered)
	void displayText(float x, float y, float r, float g, float b, char* string);
	// A function to collate all text output in a single location
	void renderTextOutput();
	void calculateFPS();

	// draw primitive functions
	

	// For access to user input.
	Input* input;
		
	// For Window and frustum calculation.
	int width, height;
	float fov, nearPlane, farPlane;

	// For FPS counter and mouse coordinate output.
	int frame = 0, time, timebase = 0;
	char fps[40];
	char mouseText[40];

};

#endif