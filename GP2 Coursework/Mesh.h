#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "obj_loader.h"

class Mesh
{
public:
	//Constructor
	Mesh();
	//Deconstructor
	~Mesh();
	//Used to draw the model
	void draw();
	//Used to create individual Pollys
	void drawTri(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	//Used to get the model
	void getModel(const std::string& filename);
	//Used to create the model
	void createModel(const IndexedModel& model);
	//Updates the collision position and radius
	void updateSphereData(glm::vec3 pos, float radius);

	//Used to get the position and radius of the collision position and radius
	glm::vec3 getSpherePos()
	{
		return meshCollision.GetPosition();
	}

	float getSphereRadius()
	{
		return meshCollision.GetRadius();
	}

private:

	enum
	{
		POSITION_VERTEXBUFFER,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	CollisionSphere meshCollision;
	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS];
	unsigned int drawCount;
};

struct Vertex
{
public:
	Vertex(const glm::vec3& position, const glm::vec2& texCoord)
	{
		this->position = position;
		this->texCoord = texCoord;
		this->normal = normal;
	}
	//Used to get position, texture coordinartes and normals
	glm::vec3* GetPosition()
	{ 
		return &position; 
	}
	
	glm::vec2* GetTexCoord() 
	{ 
		return &texCoord; 
	}

	glm::vec3* GetNormal() 
	{ 
		return &normal; 
	}

private:
	glm::vec3 position;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

struct CollisionSphere
{
public:
	//Constructor
	CollisionSphere() {}

	//Used to pass in position and radius for collision
	CollisionSphere(glm::vec3& position, float radius)
	{
		this->position = position;
		this->radius = radius;
	}

	//Gets position and radius 
	glm::vec3 GetPosition() 
	{ 
		return position; 
	}

	float GetRadius() 
	{ 
		return radius; 
	}

	//Used to set the position and radius
	void SetDetails(glm::vec3 position, float radius)
	{
		this->position = position;
		this->radius = radius;
	}

private:
	glm::vec3 position;
	float radius;
};

