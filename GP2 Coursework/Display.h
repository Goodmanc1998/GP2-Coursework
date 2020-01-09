#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;

class Display
{
public:
	//Constructor
	Display();
	//Deconstructor
	~Display();
	//Starts the display
	void startDisplay();
	//Swaps the buffer
	void swapBuffer();
	//Clears the display
	void clear(float r, float g, float b, float a);
	//Gets the width and height
	float getWidth();
	float getHeight();

private:

	void returnError(std::string errorString);

	SDL_GLContext glContext; 
	SDL_Window* gameWindow; 
	float screenWidth;
	float screenHeight;
};

