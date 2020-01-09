#pragma once
#include <string>
#include <GL\glew.h>
#include "transform.h"
#include "Camera.h"

class Shader
{
public:
	//Constructor
	Shader(const std::string& filename);
	//Used to bind the shader
	void BindShader(); 
	//used to update the shader
	void Update(const Transform& transform, const Camera& camera);

	//Used to load the shader
	std::string LoadShader(const std::string& filename);
	//Used to create the shader
	GLuint CreateShader(const std::string& text, unsigned int type);
	//USed to check for error
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

    ~Shader();

protected:
private:
	//Number of shaders
	static const unsigned int NUM_SHADERS = 2; 

	enum
	{
		TRANSFORM_U,
		NUM_UNIFORMS
	};

	//Tracking the shader
	GLuint program;
	//array of shaders
	GLuint shaders[NUM_SHADERS]; 
	//Number of Uniform variables
	GLuint uniforms[NUM_UNIFORMS]; 
};
