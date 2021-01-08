#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Model.h"

Model::Model() {

	//load models and textures

	loadModel("models/bed.obj", &bed_vertex, &bed_normals, &bed_texCoords);
	loadModel("models/chair4.obj", &chair_vertex, &chair_normals, &chair_texCoords);

}

Model::~Model() {


}



void Model::render(static std::vector<Vector3> verts, static std::vector<Vector3> normals, static std::vector<Vector3> texCoords, GLuint texture)
{
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, verts.data());
	glNormalPointer(GL_FLOAT, 0, normals.data());
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glBindTexture(GL_TEXTURE_2D, texture);
		glDrawArrays(GL_TRIANGLES, 0, verts.size());



	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	
	

}


// Modified from a mulit-threaded version by Mark Ropper.
bool Model::loadModel(char* filename, vector<Vector3>* vertex, vector<Vector3>* normals, vector<Vector3>* texCoords)
{

	vector<Vector3> temp_verts;
	vector<Vector3> temp_norms;
	vector<Vector3> temp_texCs;
	vector<unsigned int> faces;

	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		return false;
	}
	while (true)
	{
		char lineHeader[128];

		// Read first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			break; // exit loop
		}
		else // Parse
		{
			if (strcmp(lineHeader, "v") == 0) // Vertex
			{
				Vector3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				temp_verts.push_back(vertex);
			}
			else if (strcmp(lineHeader, "vt") == 0) // Tex Coord
			{
				Vector3 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				temp_texCs.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0) // Normal
			{
				Vector3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				temp_norms.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0) // Face
			{
				unsigned int face[9];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &face[0], &face[1], &face[2],
					&face[3], &face[4], &face[5],
					&face[6], &face[7], &face[8]);
				if (matches != 9)
				{
					// Parser error, or not triangle faces
					return false;
				}

				for (int i = 0; i < 9; i++)
				{
					faces.push_back(face[i]);
				}


			}
		}
	}

	#pragma region unroll_data
		// "Unroll" the loaded obj information into a list of triangles.
		// TODO: By this point all model has been read from the file, but is not in the correct order.
		// You NEED to loop over all the data and sort it into a render ready order/format.
	
		for (int i = 0; i < faces.size(); i += 3) {
	
			//Assign Vertex
			unsigned int Index = faces[i];
			Vector3 temp = temp_verts[Index - 1];
	
		
			vertex->push_back(temp);
	
			//Assign texture
			Index = faces[i + 1];
			temp = temp_texCs[Index - 1];
	
			texCoords->push_back(temp);
	
	
			//Assign norms
			Index = faces[i + 2];
			temp = temp_norms[Index - 1];
	
			normals->push_back(temp);
	
	
	
		}
	
	#pragma endregion unroll_data
	
		// Once data has been sorted clear read data (which has been copied and are not longer needed).
		temp_verts.clear();
		temp_norms.clear();
		temp_texCs.clear();
		faces.clear();
	
		return true;
}


void Model::drawModels() {

	//Draw Chairs
	glPushMatrix();
		glTranslatef(4, 0, 6);
		glRotatef(-90, 0, 1, 0);
			glPushMatrix();
				glPushMatrix();
					glScalef(0.020, 0.020, 0.020);
					glColor3f(0.1, 0.3, 0.4);
					renderChair();
				glPopMatrix();
		glTranslatef(-1.2, 0, 0.6);
		glRotatef(90, 0, 1, 0);
		glScalef(0.020, 0.020, 0.020);
		glColor3f(0.1, 0.3, 0.4);
		renderChair();
		glPopMatrix();
	glPopMatrix();

	//Bed
	glPushMatrix();
		glTranslatef(2.8, 0, 8.8);
		glScalef(0.16, 0.16, 0.16);
		glRotatef(180, 0, 1, 0);
		glColor3f(0.8, 0.8, 0.8);
		renderBed();
	glPopMatrix();


}


void Model::renderBed() {

	render(bed_vertex, bed_normals, bed_texCoords, NULL);
}

void Model::renderChair() {

	render(chair_vertex, chair_normals, chair_texCoords, NULL);
	
}



void Model::modelShadow() {

	//Model shadows with no color - same as drawModels
		//Draw Chairs
		glPushMatrix();
		glTranslatef(4, 0, 6);
		glRotatef(-90, 0, 1, 0);
		glPushMatrix();
		glPushMatrix();
		glScalef(0.020, 0.020, 0.020);

		renderChair();
		glPopMatrix();
		glTranslatef(-1.2, 0, 0.6);
		glRotatef(90, 0, 1, 0);
		glScalef(0.020, 0.020, 0.020);
	
		renderChair();
		glPopMatrix();
		glPopMatrix();
}