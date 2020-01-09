#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "transform.h"
#include "Audio.h"

enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	//Constructor
	MainGame();
	//Deconstructor
	~MainGame();

	//Used to run the game
	void run();

private:
	//Used to start the meshs and start cameras
	void startSystems();
	//Used to process inputs
	void processInput();
	//The game loop
	void gameLoop();
	//Used to draw the game
	void drawGame();
	//Check collisions with the Asteroid
	void collisionCheckAS(glm::vec3 obj1Position, float obj1Radius, glm::vec3 obj2Position, float obj2Radius);
	//Used to check collisions with the Barrier
	void collisionCheckB(glm::vec3 obj1Position, float obj1Radius, glm::vec3 obj2Position, float obj2Radius);

	Display _gameDisplay;
	GameState _gameState;

	Mesh barrierM;
	Mesh moonM;
	Mesh earthM;
	Mesh asteroidM;

	Mesh backgroundOne;
	Mesh backgroundTwo;

	Camera mainCamera;

	Audio audio;

	float counter;
	int asCounter;

	unsigned int bang;
	unsigned int backgroundMusic;
};

