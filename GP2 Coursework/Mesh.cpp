#include "Mesh.h"
#include <vector>

Mesh::Mesh()
{
	drawCount = NULL;
}

void Mesh::drawTri(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	IndexedModel model;

	for (unsigned int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*vertices[i].GetPosition());
		model.texCoords.push_back(*vertices[i].GetTexCoord());
		model.normals.push_back(*vertices[i].GetNormal());
	}

	for (unsigned int i = 0; i < numIndices; i++)
		model.indices.push_back(indices[i]);

	createModel(model);
}

void Mesh::getModel(const std::string& filename)
{
	IndexedModel model = OBJModel(filename).ToIndexedModel();
	createModel(model);
	CollisionSphere meshCollision();
}

void Mesh::createModel(const IndexedModel& model)
{

	drawCount = model.indices.size();

	//Generating a vertex array to store the vertexArrayObject and then binding it
	glGenVertexArrays(1, &vertexArrayObject); 
	glBindVertexArray(vertexArrayObject); 

	//generating our buffers based off of the array of buffers
	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);

	//Binding the buffer and telling the buffer the type of array data and passing in the data to work on the position
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VERTEXBUFFER]); 
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW); 
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	//Unbinding the Vertex Array Object
	glBindVertexArray(0); 
}

void Mesh::draw()
{

	glBindVertexArray(vertexArrayObject);

	glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, drawCount);

	glBindVertexArray(0);
}

void Mesh::updateSphereData(glm::vec3 pos, float radius)
{
	meshCollision.SetDetails(pos, radius);
}

Mesh::~Mesh()
{
	//Delete vertex array object
	glDeleteVertexArrays(1, &vertexArrayObject);
}


