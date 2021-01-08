#include "ProceduralGenerator.h"

ProceduralGenerator::ProceduralGenerator() {



	

}
ProceduralGenerator::~ProceduralGenerator() {

}



void ProceduralGenerator::drawWall(float ax, float az,float bx, float bz, float height, Vector3 direction, GLuint texture) {

	//draws walls taking a point of start and one to end
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);

	for (int h = 0; h < height; h++) {
		for (int x = ax; x < bx; x++) {
			
			//top left
			glTexCoord2f(0.99f, 0.99f);
			glNormal3f(direction.x, direction.y, direction.z);
			glVertex3f(x, h, az);
			
			//bot left
			glTexCoord2f(0.01f, 0.99f);
			glNormal3f(direction.x, direction.y, direction.z);
			glVertex3f(x + 1, h, az);
			
			//bot right
			glTexCoord2f(0.01f, 0.01f);
			glNormal3f(direction.x, direction.y, direction.z);
			glVertex3f(x + 1, h+1, az);
		
			//top right
			glTexCoord2f(0.99f, 0.01f);
			glNormal3f(direction.x, direction.y, direction.z);
			glVertex3f(x, h+1, az);
			
		}

	}

	for (int h = 0; h < height; h++) {
		for (int z = az; z < bz; z++) {
			//top left
			glTexCoord2f(0.99f, 0.99f);
			glNormal3f(direction.x, direction.y, direction.z);
			glVertex3f(ax, h, z);
			//bot left
			glTexCoord2f(0.01f, 0.99f);
			glNormal3f(direction.x, direction.y, direction.z);
			glVertex3f(ax, h, z+1);
			//bot right
			glTexCoord2f(0.01f, 0.01f);
			glNormal3f(direction.x, direction.y, direction.z);
			glVertex3f(ax, h+1, z + 1);
			//top right
			glTexCoord2f(0.99f, 0.01f);
			glNormal3f(direction.x, direction.y, direction.z);
			glVertex3f(ax, h+1, z );
			
		}
	
	}

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void ProceduralGenerator::drawCircle(float radius, GLuint texture)
{
	

	//CHANGE DELTA TO OPEN CIRCLE
		//Variables
	float theta = 0, delta = 0;
	float res = 20;
	float u = 0, v = 0;


	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture);
	
	for (int lon = 0; lon < res /4; lon++) {
		for (int lat = 0; lat < res; lat++) {
			glBegin(GL_QUADS);

			//topL
			glNormal3f((cosf(theta) * sinf(delta))* radius , 0, (sinf(theta) * sinf(delta)) * radius);
			glTexCoord2f(u, v);
			glVertex3f((cosf(theta) * sinf(delta)) * radius , 0, (sinf(theta) * sinf(delta)) * radius );

			//topR
			glNormal3f((cosf(theta + ((2 * 3.1415) / res)) * sinf(delta)) * radius, 0, (sinf(theta + ((2 * 3.1415) / res)) * sinf(delta)) * radius );
			glTexCoord2f(u + (1 / res), v);										  
			glVertex3f((cosf(theta + ((2 * 3.1415) / res)) * sinf(delta)) * radius, 0, (sinf(theta + ((2 * 3.1415) / res)) * sinf(delta)) * radius );


			//BotL
			glNormal3f((cosf(theta + ((2 * 3.1415) / res)) * sinf(delta + (3.1415 / res))) * radius , 0, (sinf(theta + ((2 * 3.1415) / res)) * sinf(delta + (3.1415 / res))) * radius);
			glTexCoord2f(u + (1 / res), v + (1 / res));
			glVertex3f((cosf(theta + ((2 * 3.1415) / res)) * sinf(delta + (3.1415 / res))) * radius, 0, (sinf(theta + ((2 * 3.1415) / res)) * sinf(delta + (3.1415 / res))) * radius);


			//BotR		
			glNormal3f((cosf(theta) * sinf(delta + (3.1415 / res))) * radius, 0, (sinf(theta) * sinf(delta + (3.1415 / res))) * radius );
			glTexCoord2f(u, v + (1 / res));
			glVertex3f((cosf(theta) * sinf(delta + (3.1415 / res))) * radius, 0, (sinf(theta) * sinf(delta + (3.1415 / res))) * radius );


			glEnd();
			theta += (2 * 3.1415) / res ;
			u += (1 / res) ;
		}




		u = 0;
		delta += 3.1415 / res;
		v += (1 / res) ;
	}

	glDisable(GL_TEXTURE_2D);
}

void ProceduralGenerator::drawSphere(int segments, GLuint texture, float hemisphere) {

	//draws spheres and hemispheres by changing the hemisphere float to > than 1

	//Variables
	float theta = 0, delta = 0;
	float res = segments;
	float u = 0, v = 0;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	for (int lon = 0; lon < res/hemisphere; lon++) {
		for (int lat = 0; lat < res; lat++) {

			glBegin(GL_QUADS);
			
			//topL
			glNormal3f((cosf(theta) * sinf(delta)) , cosf(delta) , (sinf(theta) * sinf(delta) ));
			glTexCoord2f(u, v);
			glVertex3f((cosf(theta) * sinf(delta)) , cosf(delta) , (sinf(theta) * sinf(delta) ));
			
			//topR
			glNormal3f((cosf(theta + ((2 * 3.1415) / res)) * sinf(delta)) , cosf(delta) , (sinf(theta + ((2 * 3.1415) / res)) * sinf(delta) ));
			glTexCoord2f(u + (1 / res), v);
			glVertex3f((cosf(theta + ((2 * 3.1415) / res)) * sinf(delta)) , cosf(delta) , (sinf(theta + ((2 * 3.1415) / res)) * sinf(delta) ));
			
			
			//BotL
			glNormal3f((cosf(theta + ((2 * 3.1415) / res)) * sinf(delta + (3.1415 / res))) , cosf(delta + (3.1415 / res)) , (sinf(theta + ((2 * 3.1415) / res)) * sinf(delta + (3.1415 / res)) ));
			glTexCoord2f(u + (1 / res), v + (1 / res));
			glVertex3f((cosf(theta + ((2 * 3.1415) / res)) * sinf(delta + (3.1415 / res))) , cosf(delta + (3.1415 / res)) , (sinf(theta + ((2 * 3.1415) / res)) * sinf(delta + (3.1415 / res)) ));
			
			
			//BotR		
			glNormal3f((cosf(theta) * sinf(delta + (3.1415 / res))) , cosf(delta + (3.1415 / res)), (sinf(theta) * sinf(delta + (3.1415 / res))));
			glTexCoord2f(u, v + (1 / res));
			glVertex3f((cosf(theta) * sinf(delta + (3.1415 / res))) , cosf(delta + (3.1415 / res)), (sinf(theta) * sinf(delta + (3.1415 / res))));


			glEnd();

			theta += (2 * 3.1415) / res;
			u += (1 / res);

		}

		u = 0;
		delta += 3.1415 / res;
		v += (1/res);
	}
	glDisable(GL_TEXTURE_2D);
}


void ProceduralGenerator::drawEllipse() {

	//Draws an Ellipse, got it from stackoverflow, probably not going to use;
	glBegin(GL_LINE_LOOP);

	float radiusX = 1;
	float radiusY = 2;

	for (int i = 0; i < 360; i++)
	{
		float rad = i * 3.1415/180.f;
		glVertex2f(cos(rad) * radiusX, sin(rad) * radiusY);
	}

	glEnd();
}


void ProceduralGenerator::drawFan(GLuint texture) {

	//draws a fan blade
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_POLYGON);
	

	//glTexCoord2f(0.5, 1);
	glTexCoord2f(0.5, 0.4);
	glVertex3f(0, 0, 0);

	glTexCoord2f(0, 0.7);
	glVertex3f(-0.25, 0, 0.75);

	glTexCoord2f(0, 0);
	glVertex3f(-0.25, 0, 2);

	glTexCoord2f(1, 0);
	glVertex3f(0.25, 0, 2);

	//glTexCoord2f(1, 1);
	glTexCoord2f(1, 0.7);
	glVertex3f(0.25, 0, 0.75);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	
}


void ProceduralGenerator::drawCylinder(float radius, float height, GLuint texture) {

	//a cylinder
		GLfloat x = 0.0, y = 0.0;
		GLfloat angle = 0.0, angle_stepsize = 0.05;

		float u = 0, v = 0;

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
	

		glBegin(GL_TRIANGLE_STRIP);
		angle = 0.0;
		while (angle < 2 * 3.1415) {
			x = radius * cos(angle);
			y = radius * sin(angle);
			
			
			glTexCoord2f(u, 1);
			glNormal3f(x, y, height);
			glVertex3f(x, y, height);

			glTexCoord2f(u, 0);
			glNormal3f(x, y, height);		
			glVertex3f(x, y, 0.0);


			angle = angle + angle_stepsize;

			u += (radius* angle_stepsize)/ (2*3.1415);
			
		}
	
		glTexCoord2f(radius, 1);
		glNormal3f(radius, 0.0, height);
		glVertex3f(radius, 0.0, height);
	
		glTexCoord2f(radius, 0);
		glNormal3f(radius, 0.0, 0.0);
		glVertex3f(radius, 0.0, 0.0);


		glEnd();
	
	glDisable(GL_TEXTURE_2D);

		
}


void ProceduralGenerator::drawCone(float radius, float height, GLuint texture) {

	//NOT USED, draws a cone
	//Variables
	float theta = 0, delta = 0;
	float res = 20;
	float u = 0, v = 0;

	glBindTexture(GL_TEXTURE_2D, texture);

	for (int lon = 0; lon < res ; lon++) {
		for (int lat = 0; lat < res; lat++) {

			glBegin(GL_QUADS);

			//topL
			glNormal3f((cosf(theta) * sinf(delta)), cosf(delta), (sinf(theta) * sinf(delta)));
			glTexCoord2f(u, v);
			glVertex3f((cosf(theta) * sinf(delta)), cosf(delta), (sinf(theta) * sinf(delta)));

			//topR
			glNormal3f((cosf(theta + ((2 * 3.1415) / res)) * sinf(delta)), cosf(delta), (sinf(theta + ((2 * 3.1415) / res)) * sinf(delta)));
			glTexCoord2f(u + (1 / res), v);
			glVertex3f((cosf(theta + ((2 * 3.1415) / res)) * sinf(delta)), cosf(delta), (sinf(theta + ((2 * 3.1415) / res)) * sinf(delta)));


			//BotL
			glNormal3f((cosf(theta + ((2 * 3.1415) / res)) * sinf(delta + (3.1415 / res))), cosf(delta + (3.1415 / res)), (sinf(theta + ((2 * 3.1415) / res)) * sinf(delta + (3.1415 / res))));
			glTexCoord2f(u + (1 / res), v + (1 / res));
			glVertex3f((cosf(theta + ((2 * 3.1415) / res)) * sinf(delta + (3.1415 / res))), cosf(delta + (3.1415 / res)), (sinf(theta + ((2 * 3.1415) / res)) * sinf(delta + (3.1415 / res))));


			//BotR		
			glNormal3f((cosf(theta) * sinf(delta + (3.1415 / res))), cosf(delta + (3.1415 / res)), (sinf(theta) * sinf(delta + (3.1415 / res))));
			glTexCoord2f(u, v + (1 / res));
			glVertex3f((cosf(theta) * sinf(delta + (3.1415 / res))), cosf(delta + (3.1415 / res)), (sinf(theta) * sinf(delta + (3.1415 / res))));


			glEnd();
			theta += (2 * 3.1415) / res;
			u += (1 / res);

		}

		u = 0;
		delta += 1 / res;
		v += (1 / res);
	}





}

void ProceduralGenerator::drawPlane(GLuint texture) {


	//Draws a basic quad, carptes trees etc..
	glEnable(GL_TEXTURE_2D);


	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, texture);

	
	glBegin(GL_QUADS);
	//top left
	glTexCoord2f(0.99f, 0.99f);
	glNormal3f(0, 0, 0);
	glVertex3f(0, 0, 0);

	//bot left
	glTexCoord2f(0.01f, 0.99f);
	glNormal3f(0, 0, 0);
	glVertex3f(1, 0, 0);

	//bot right
	glTexCoord2f(0.01f, 0.01f);
	glNormal3f(0, 0, 0);
	glVertex3f(1,1, 0);

	//top right
	glTexCoord2f(0.99f, 0.01f);
	glNormal3f(0, 0, 0);
	glVertex3f(0, 1, 0);


	glEnd();

	glDisable(GL_TEXTURE_2D);

}



void ProceduralGenerator::drawFloorTile(float v,float i, float height, GLuint texture)
{



	

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);


	glBegin(GL_QUADS);
	

		glTexCoord2f(0, 0);
		glNormal3f(0, 1, 0);
		glVertex3f(v, height, i);
		
		glTexCoord2f(0, 1);
		glNormal3f(0, 1, 0);
		glVertex3f(v, height, i+1);
	
		glTexCoord2f(1, 1);
		glNormal3f(0, 1, 0);
		glVertex3f(v+1, height, i+1);
		
		glTexCoord2f(0, 1);
		glNormal3f(0, 1, 0);
		glVertex3f(v+1, height, i);

		glDisable(GL_TEXTURE_2D);

	glEnd();
}


void ProceduralGenerator::drawCube(float width, float height, float depth, GLuint texture) {

	//Draws a cube or cuboid

	float b =0, n=0;
	
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
	
	//drawfront
	for(float h = 0; h <height; h+= 0.5){
		for (float w = 0; w < width; w += 0.5) {
			
			glTexCoord2f(b , n);
			glNormal3f(0, 0, -1);
			glVertex3f(0.0 + w, 0.0 +h, 0.0);

			glTexCoord2f(b + (0.5 / width), n );
			glNormal3f(0, 0, -1);
			glVertex3f(0.5 + w, 0.0 +h, 0.0);

			glTexCoord2f(b + (0.5 / width), n + (0.5 / height));
			glNormal3f(0, 0, -1);
			glVertex3f(0.5 + w, 0.5 +h, 0.0);

			glTexCoord2f(b ,n + (0.5 / height));
			glNormal3f(0, 0, -1);
			glVertex3f(0.0 + w, 0.5 +h, 0.0);
			
			b += ((0.5/ width));

		}
		b = 0;
		n += (0.5 / height);
	}
	b = 0;
	n = 0;

	//drawright
	for (float d = 0; d < depth; d += 0.5) {
		for (float h = 0; h < height; h += 0.5) {

				glTexCoord2f(b, n);
				glNormal3f(-1, 0, 0);
				glVertex3f(0.0 , 0.0 + h, 0.0+d);

				glTexCoord2f(b + (0.5 / depth), n);
				glNormal3f(-1, 0, 0);
				glVertex3f(0.0 , 0.0 + h, 0.5+d);

				glTexCoord2f(b + (0.5 / depth), n + (0.5 / height));
				glNormal3f(-1, 0, 0);
				glVertex3f(0.0 , 0.5 + h, 0.5+d);

				glTexCoord2f(b, n + (0.5 / height));
				glNormal3f(-1, 0, 0);
				glVertex3f(0.0 , 0.5 + h, 0.0+d);

				n += ((0.5 / height));
		}
		n = 0;
		b += (0.5 / depth);
	}
	b = 0;
	n = 0;
	//drawback
	for (float h = 0; h < height; h += 0.5) {
		for (float w = 0; w < width; w += 0.5) {

			glTexCoord2f(b, n);
			glNormal3f(0, 0, 1);
			glVertex3f(0.0 + w, 0.0 + h, depth);

			glTexCoord2f(b + (0.5 / width), n);
			glNormal3f(0, 0, 1);
			glVertex3f(0.5 + w, 0.0 + h, depth);

			glTexCoord2f(b + (0.5 / width), n + (0.5 / height));
			glNormal3f(0, 0, 1);
			glVertex3f(0.5 + w, 0.5 + h, depth);

			glTexCoord2f(b, n + (0.5 / height));
			glNormal3f(0, 0, 1);
			glVertex3f(0.0 + w, 0.5 + h, depth);



			b += ((0.5 / width));
		}
		b = 0;
		n += (0.5 / height);
	}
	b = 0;
	n = 0;
	//drawleft
	for (float d = 0; d < depth; d += 0.5) {
		for (float h = 0; h < height; h += 0.5) {
			
			glTexCoord2f(b, n);
			glNormal3f(1, 0,0);
			glVertex3f(width, 0.0 + h, 0.0 + d);

			glTexCoord2f(b + (0.5 / depth), n);
			glNormal3f(1, 0, 0);
			glVertex3f(width, 0.0 + h, 0.5 + d);


			glTexCoord2f(b + (0.5 / depth), n + (0.5 / height));
			glNormal3f(1, 0, 0);
			glVertex3f(width, 0.5 + h, 0.5 + d);

			glTexCoord2f(b, n + (0.5 / height));
			glNormal3f(1, 0, 0);
			glVertex3f(width, 0.5 + h, 0.0 + d);

			n += ((0.5 / height));
		}

		n = 0;
		b += (0.5 / depth);

	}
	b = 0;
	n = 0;
	
	//drawtop
	for (float d = 0; d < depth; d += 0.5) {
		for (float w = 0; w < width; w += 0.5) {


			glTexCoord2f(b, n);
			glNormal3f(0, 1, 0);
			glVertex3f(0.0 + w, height, 0.0 + d);

			glTexCoord2f(b + (0.5 / width), n);
			glNormal3f(0, 1, 0);
			glVertex3f(0.5 + w, height, 0.0 + d);

			glTexCoord2f(b + (0.5 / width), n + (0.5 / depth));
			glNormal3f(0, 1, 0);
			glVertex3f(0.5 + w, height, 0.5 + d);

			glTexCoord2f(b, n + (0.5 / depth));
			glNormal3f(0, 1, 0);
			glVertex3f(0.0 + w, height, 0.5 + d);

			b += (0.5 / width);
		}	
		b = 0;
		n += (0.5 / depth);
	}
	b = 0;
	n = 0;

	//drawbot
	for (float d = 0; d < depth; d += 0.5) {
		for (float w = 0; w < width; w += 0.5) {

			glTexCoord2f(b, n);
			glNormal3f(0, -1, 0);
			glVertex3f(0.0 + w, 0.0, 0.0 + d);

			glTexCoord2f(b + (0.5 / width), n);
			glNormal3f(0, -1, 0);
			glVertex3f(0.5 + w, 0.0, 0.0 + d);

			glTexCoord2f(b + (0.5 / width), n + (0.5 / depth));
			glNormal3f(0, -1, 0);
			glVertex3f(0.5 + w, 0.0, 0.5 + d);

			glTexCoord2f(b, n + (0.5 / depth));
			glNormal3f(0, -1, 0);
			glVertex3f(0.0 + w, 0.0, 0.5 + d);

			b += (0.5 / width);
		}

		b = 0;
		n += (0.5 / depth);
	}



	glEnd();
}

