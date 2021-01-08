#include "Scene.h"

// Scene constructor, initilises OpenGL
// You should add further variables to need initilised.
Scene::Scene(Input *in)
{
	// Store pointer for input class
	input = in;
	initialiseOpenGL();

	// Other OpenGL / render setting should be applied here.

	// Initialise scene variables
	srand(0);
	
	tx.loadTextures2();
	//tx.loadTextures();

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	
	

}

void Scene::updateLight_pos() {
	shadow.lightpos[0] = lights.light4_pos.x;
	shadow.lightpos[1] = lights.light4_pos.y;
	shadow.lightpos[2] = lights.light4_pos.z;

}

void Scene::handleInput(float dt)
{
	// Handle user input
	camera.input(input, dt);
	lights.input(input, dt);

	if (input->isKeyDown(112))
	{
		wireframe++;
		if (wireframe > 3)
			wireframe = 0;

		input->setKeyUp(112);
	}

}

void Scene::update(float dt)
{
	// update scene related variables.
	lights.sunUpdate(dt);
	room.update(dt);
	updateLight_pos();

	// Calculate FPS for output
	calculateFPS();
	pos = pos - 2 * dt;

}

void Scene::render() {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);


	// Reset transformations
	glLoadIdentity();

	//Update Camera
	camera.update();
	//gluLookAt(1, 2, 1, 2, 1, 4, 0, 1, 0);

	//WIREFRAME MODES
	if (wireframe == 0)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else if (wireframe == 1) {
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_FILL);
	}
	else if (wireframe == 2) {
		glPolygonMode(GL_BACK, GL_LINE);
		glPolygonMode(GL_FRONT, GL_FILL);
	}
	else if (wireframe == 3) 
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Skybox
	glDisable(GL_DEPTH_TEST);
	glPushMatrix();
		glTranslatef(camera.pos.x, camera.pos.y, camera.pos.z);
		pg.drawSphere(20, tx.skybox, 1);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);

	//Sun
	glPushMatrix();
		glTranslatef(lights.light4_pos.x, lights.light4_pos.y, lights.light4_pos.z);
		gluSphere(gluNewQuadric(), 0.50, 30, 30);
	glPopMatrix();

	
	room.renderFloor();
	room.drawRoom();


	//STENCIL
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	
	glDisable(GL_DEPTH_TEST);
	
		//add to stencil
		glPushMatrix();
			glTranslatef(2, 0, 0.01);
			glScalef(2, 3, 1);
			pg.drawPlane(NULL);
		glPopMatrix();
	
	glEnable(GL_DEPTH_TEST);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	
	
	//start drawing reflections
	glPushMatrix();
		glScalef(1.0, 1.0, -1.0);
	
			glEnable(GL_TEXTURE_2D);
	
			room.renderFloor();
			room.drawRoom();
	
			//Lights
			lights.renderSun();
			if (lights.light4_pos.y < 0)
				lights.render();
			else {
				glDisable(GL_LIGHT1);
				glDisable(GL_LIGHT2);
			}
		
		
	
	
			//roof
			room.renderRoof();
	
			//Models
			glColor3f(1, 1, 1);
				room.drawScene();
				model.drawModels();
	
		glPopMatrix();
	
	
	
		glDisable(GL_STENCIL_TEST);
		glEnable(GL_BLEND);
	
		//draw the mirror
		glPushMatrix();
			glTranslatef(2, 0, 0.01);
			glColor4f(0.8, 0.8, 0.8, 0.4);
			glScalef(2, 3, 1);
			pg.drawPlane(NULL);
		glPopMatrix();
	
		
		glDisable(GL_BLEND);

		//finish drawing reflection

		

		glEnable(GL_TEXTURE_2D);

		//Lights
		lights.renderSun();

		if (lights.light4_pos.y < 0)
			lights.render();
		else {
			glDisable(GL_LIGHT1);
			glDisable(GL_LIGHT2);
		}

			//Shadows
			glEnable(GL_BLEND);
				room.renderFloor();//floor
				room.drawRoom();//walls
				shadow.renderShadow();
			glDisable(GL_BLEND);


			room.renderRoof();
			//Models
			glColor3f(1, 1, 1);
			room.drawScene();
			model.drawModels();
			
		glPopMatrix();




	glDisable(GL_TEXTURE_2D);

	// End render geometry --------------------------------------

	// Render text, should be last object rendered.
	renderTextOutput();
	
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}


void Scene::test() {

	glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);

	glVertex3f(2,-2, -2);
	glVertex3f(2,-2, 2);
	glVertex3f(2, 2, 2);
	glVertex3f(2, 2, -2);


	glEnd();
	glEnable(GL_TEXTURE_2D);
}
void Scene::test2() {

	glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);


	glVertex3f(-3,  0, -3);
	glVertex3f(-3,  0,  3);
	glVertex3f( 3,  0,  3);
	glVertex3f( 3,  0, -3);




	glEnd();
	glEnable(GL_TEXTURE_2D);
}


void Scene::initialiseOpenGL()
{
	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
//	glShadeModel(GL_FLAT);
	glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


}

// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h) 
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

// Calculates FPS
void Scene::calculateFPS()
{
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
	
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput()
{
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width/(float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}
