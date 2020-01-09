#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct Camera
{
public:
	//Constructor
	Camera()
	{
	}

	//Used to start the camera, takes in starting position, fov, aspect and the near and far clipping planes
	void cameraStart(const glm::vec3& position, float fov, float aspect, float nearClip, float farClip)
	{
		this->position = position;
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projection = glm::perspective(fov, aspect, nearClip, farClip);
	}

	//Used to get the position
	glm::vec3 getPosition() 
	{
		return this->position;
	}

	//Used to get the Projection View 
	inline glm::mat4 GetProjectionView() const
	{
		return projection * glm::lookAt(position, position + forward, up);
	}

	//Used to move the camera left, right, forward, back, up and down
	void moveForward(float forwardAmount)
	{
		position += forward * forwardAmount;
	}

	void moveRight(float rightAmount)
	{
		position += glm::vec3(1.0f, 0.0f, 0.0f) * rightAmount;
	}

	void moveUp(float upAmount)
	{
		position += up * upAmount;
	}

protected:
private:
	glm::mat4 projection;
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 up;
};
