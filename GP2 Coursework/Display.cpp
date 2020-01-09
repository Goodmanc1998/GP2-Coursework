#include "Display.h"


Display::Display()
{
	//setting the gameWindow to null for debugging
	gameWindow = nullptr;

	//setting up the screens width and height
	screenWidth = 1024.0f;
	screenHeight = 768.0f;
}

void Display::startDisplay()
{
	//Initialising SDL
	SDL_Init(SDL_INIT_EVERYTHING); 

	//Setting up double buffer
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);  

	//Creating the gameWindow
	gameWindow = SDL_CreateWindow("GP2 Coursework Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)screenWidth, (int)screenHeight, SDL_WINDOW_OPENGL); // create window

	glContext = SDL_GL_CreateContext(gameWindow);

	//Initialising GLEW
	GLenum error = glewInit();

	glEnable(GL_DEPTH_TEST); //enable z-buffering 
	glEnable(GL_CULL_FACE); //dont draw faces that are not pointing at the camera

	//Setting up the background
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

	//Error checking the gameWindow, glContext and GLEW
	if (gameWindow == nullptr)
	{
		returnError("window failed to create");
	}

	if (glContext == nullptr)
	{
		returnError("SDL_GL context failed to create");
	}

	if (error != GLEW_OK)
	{
		returnError("GLEW failed to initialise");
	}
}

void Display::swapBuffer()
{
	// Swapping buffers
	SDL_GL_SwapWindow(gameWindow);
}

void Display::clear(float r, float g, float b, float a)
{
	//clearing the display
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

float Display::getWidth()
{
	//returning the screens width
	return screenWidth;
}

float Display::getHeight()
{
	//returning screen height
	return screenHeight;
}

void Display::returnError(std::string errorString)
{
	//Outputting and error message and allowing the user to quit
	std::cout << errorString << std::endl;
	std::cout << "press any  key to quit...";
	int in;
	std::cin >> in;
	SDL_Quit();
}

Display::~Display()
{
	//Destroying / deleting the glContext, gameWindow and quiting SDL
	SDL_GL_DeleteContext(glContext); 
	SDL_DestroyWindow(gameWindow); 
	SDL_Quit();
}