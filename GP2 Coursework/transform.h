#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct Transform
{
public:
	//Constructor
	Transform(const glm::vec3& position = glm::vec3(), const glm::vec3& rotation = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;
	}

	//Used to get the models details, Position, scale, rotation
	inline glm::mat4 GetModel() const
	{
		glm::mat4 posMat = glm::translate(position);
		glm::mat4 scaleMat = glm::scale(scale);
		glm::mat4 rotX = glm::rotate(rotation.x, glm::vec3(1.0, 0.0, 0.0));
		glm::mat4 rotY = glm::rotate(rotation.y, glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 rotZ = glm::rotate(rotation.z, glm::vec3(0.0, 0.0, 1.0));
		glm::mat4 rotMat = rotX * rotY * rotZ;

		return posMat * rotMat * scaleMat;
	}

	//Used to get the Position, rotation and scale
	inline glm::vec3* GetPosition()
	{ 
		return &position; 
	}

	inline glm::vec3* GetRotation()
	{ 
		return &rotation; 
	}

	inline glm::vec3* GetScale()
	{ 
		return &scale; 
	}

	//Used to set the Position, Rotation or Scale
	inline void SetPosition(glm::vec3 position) 
	{ 
		this->position = position;
	}

	inline void SetRotation(glm::vec3 rotation)
	{ 
		this->rotation = rotation; 
	}

	inline void SetScale(glm::vec3 scale)
	{
		this->scale = scale; 
	}

	//Used to move the cameras postion left, right, up and down
	void moveRight(float rightAmount)
	{
		position += glm::vec3(1.0f, 0.0f, 0.0f) * rightAmount;
	}

	void moveUp(float upAmount)
	{
		position += glm::vec3(0.0f, 1.0f, 0.0f) * upAmount;
	}

protected:
private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};


