#include "Render.h"

Render::Render() {

}

Render::~Render() {

}


//To render vertex arrays
void Render::render2(static std::vector<float> verts)
{
	// add code to render the cube (above) using method 2
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, verts.data());
	glDrawArrays(GL_QUADS, 0, 3);
	glDisableClientState(GL_VERTEX_ARRAY);
	
	

}


//To load models
bool Render::load(char* modelFilename, char* textureFilename) {

	bool result;

	// Load in the model data,
	result = loadModel(modelFilename);
	if (!result)
	{
		MessageBox(NULL, "Model failed to load", "Error", MB_OK);
		return false;
	}

	// Load the texture for this model.
	tx.loadTextures_name(textureFilename);

	return true;



}

//Part of the model loading process
bool Render::loadModel(char* filename) {


	std::vector<Vector3> temp_verts;
	std::vector<Vector3> temp_norms;
	std::vector<Vector3> temp_texCs;
	std::vector<unsigned int> faces;

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


		vertex.push_back(temp);

		//Assign texture
		Index = faces[i + 1];
		temp = temp_texCs[Index - 1];

		texCoords.push_back(temp);


		//Assign norms
		Index = faces[i + 2];
		temp = temp_norms[Index - 1];

		normals.push_back(temp);



	}

#pragma endregion unroll_data

	// Once data has been sorted clear read data (which has been copied and are not longer needed).
	temp_verts.clear();
	temp_norms.clear();
	temp_texCs.clear();
	faces.clear();

	return true;




}
