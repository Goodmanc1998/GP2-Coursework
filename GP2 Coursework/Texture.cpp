#include "Texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

Texture::Texture(const std::string& fileName)
{
	//Width, height and number of components for the texture
	int width, height, numComponents; 
	//Loads the image and stores it
	unsigned char* imageData = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);

	glGenTextures(1, &textureHandler); 
	glBindTexture(GL_TEXTURE_2D, textureHandler); 

	//Wrapping the textures height and width
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Filtering for minification and magnifcation
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData); 
	stbi_image_free(imageData);

	//Error checking the Image data
	if (imageData == NULL)
	{
		std::cerr << "texture load failed" << fileName << std::endl;
	}
}

void Texture::Bind(unsigned int unit)
{
	//Checking there is 32 textures
	assert(unit >= 0 && unit <= 31);
	//Set active texture units
	glActiveTexture(GL_TEXTURE0 + unit);
	//Type of texture and binding it to unit
	glBindTexture(GL_TEXTURE_2D, textureHandler);
}

Texture::~Texture()
{
	//Number and address of textures
	glDeleteTextures(1, &textureHandler); 
}