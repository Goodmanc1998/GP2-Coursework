#pragma once
#include <string>
#include <GL\glew.h>

class Texture
{
public:
	//Constructor
	Texture(const std::string& fileName);

	//Used to bind the texture
	void Bind(unsigned int unit); 

	//Deconstructor
	~Texture();

protected:
private:

	GLuint textureHandler;
};

