#include "Shader.h"
#include <iostream>
#include <fstream>

Shader::Shader(const std::string& filename)
{
	//Creating the shader program
	program = glCreateProgram(); 

	//loading in the shaders
	shaders[0] = CreateShader(LoadShader("..\\res\\shader.vert"), GL_VERTEX_SHADER); 
	shaders[1] = CreateShader(LoadShader("..\\res\\shader.frag"), GL_FRAGMENT_SHADER); 

	//attaching all the shaders to the program
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(program, shaders[i]); 
	}

	//Binding the positions, texCoords and normals to the program
	glBindAttribLocation(program, 0, "position"); 
	glBindAttribLocation(program, 1, "texCoord");
	glBindAttribLocation(program, 2, "normals");

	//Linking the program 
	glLinkProgram(program); 

	//Validating the program
	glValidateProgram(program); 

	uniforms[TRANSFORM_U] = glGetUniformLocation(program, "transform"); 

	//Checking for errors with the shader
	CheckShaderError(program, GL_LINK_STATUS, true, "Error: Shader program linking failed"); 
	CheckShaderError(program, GL_VALIDATE_STATUS, true, "Error: Shader program not valid");
}

GLuint Shader::CreateShader(const std::string& text, unsigned int type)
{
	//Creating a shader based on the type
	GLuint shader = glCreateShader(type);

	const GLchar* stringSource[1]; 
	stringSource[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, stringSource, lengths); 
	glCompileShader(shader); 

	//Checking for errors with the shader
	if (shader == 0)
		std::cerr << "Error type creation failed " << type << std::endl;

	//Checking for error
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!"); 

	//returning the shader
	return shader;
}

std::string Shader::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void Shader::BindShader()
{
	//Using the program
	glUseProgram(program); 
}

void Shader::Update(const Transform& transform, const Camera& camera)
{
	//updating the shader
	glm::mat4 mvp = camera.GetProjectionView() * transform.GetModel();
	glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GLU_FALSE, &mvp[0][0]);
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

Shader::~Shader()
{
	//detaching the shader from the program and deleting it
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(program, shaders[i]);
		glDeleteShader(shaders[i]);
	}

	//Deleting the program
	glDeleteProgram(program); 
}