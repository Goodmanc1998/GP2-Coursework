#include "MainGame.h"
#include "Camera.h"
#include <iostream>
#include <string>

//Vertices used to store the positions of the background
Vertex vertices[] = { Vertex(glm::vec3(-100, -100, 100), glm::vec2(0, 0.0)),
					Vertex(glm::vec3(100, 100, 100), glm::vec2(1.0, 1.0)),
					Vertex(glm::vec3(100, -100, 100), glm::vec2(1.0, 0.0))};

Vertex vertices1[] = { Vertex(glm::vec3(-100, 100, 100), glm::vec2(1, 0.0)),
					Vertex(glm::vec3(100, 100, 100), glm::vec2(1.0, 1.0)),
					Vertex(glm::vec3(-100, -100, 100), glm::vec2(0,0.0)) };

unsigned int indices[] = { 0, 1, 2 };

//Transform used to store most of the meshes details and seperate transform to control the barriers transform
Transform transform;
Transform barrierTransform;

//A vector 3 used to store the barriers starting position
glm::vec3 barrierStartPosition;

MainGame::MainGame()
{
	//setting the Game state to play
	_gameState = GameState::PLAY;

	//Bringing in the required scripts for the game
	Display* _gameDisplay = new Display();

	Mesh* barrierM();
	Mesh* moonM();
	Mesh* earthM();
	Mesh* asteroidM();

	Mesh* backgroundOne();
	Mesh* backgroundTwo();
	
	Audio* audio();

	//Setting up the barriers starting position
	barrierStartPosition = glm::vec3(-60, 0, 50);
}

void MainGame::run()
{
	//Starting the systems for the game
	startSystems();
	//Starting the game loop
	gameLoop();
}

void MainGame::startSystems()
{
	//Starting the games display
	_gameDisplay.startDisplay();

	//Bringing in the sounds
	bang = audio.loadSound("..\\res\\Bang.wav");
	backgroundMusic = audio.loadSound("..\\res\\Background.wav");

	//Setting up the background
	backgroundOne.drawTri(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	backgroundTwo.drawTri(vertices1, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));

	//Bringing in the required models
	earthM.getModel("..\\res\\Earth.obj");
	moonM.getModel("..\\res\\Moon_2K.obj");
	asteroidM.getModel("..\\res\\Asteroid.obj");
	barrierM.getModel("..\\res\\barrier.obj");

	//Setting the barriers transform to the stored starting position
	barrierTransform.SetPosition(barrierStartPosition);

	//Setting up the camera
	mainCamera.cameraStart(glm::vec3(0, 0, -100), 70.0f, (float)_gameDisplay.getWidth() / _gameDisplay.getHeight(), 0.01f, 10000.0f);
	
	//Starting the counter and counter used in the astroid counter
	counter = 0.0f;
	asCounter = 300;

	//Playing the background Audio 
	audio.playSound(backgroundMusic, barrierStartPosition);

}

void MainGame::gameLoop()
{
	//Running while the Gamestate is not in exit
	while (_gameState != GameState::EXIT)
	{
		//Calling processInput
		processInput();

		//Drawing the game
		drawGame();

		//Checking the collisions between the asteroid and the plannets and barrier
		collisionCheckAS(asteroidM.getSpherePos(), asteroidM.getSphereRadius(), moonM.getSpherePos(), moonM.getSphereRadius());
		collisionCheckAS(asteroidM.getSpherePos(), asteroidM.getSphereRadius(), earthM.getSpherePos(), earthM.getSphereRadius());
		collisionCheckAS(asteroidM.getSpherePos(), asteroidM.getSphereRadius(), barrierM.getSpherePos(), barrierM.getSphereRadius());

		//Checking the collisions between the barrier and the planets
		collisionCheckB(barrierM.getSpherePos(), barrierM.getSphereRadius(), moonM.getSpherePos(), moonM.getSphereRadius());
		collisionCheckB(barrierM.getSpherePos(), barrierM.getSphereRadius(), earthM.getSpherePos(), earthM.getSphereRadius());
	}
}

void MainGame::processInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			//Checking if a key is pressed
			case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				//Checks if the key is being pressed and moving the appropriate mesh / camera. Also used to end the game
				case SDLK_d:
				{
					mainCamera.moveRight(-3);
				}
				break;
				case SDLK_a:
				{
					mainCamera.moveRight(3);
				}
				break;
				case SDLK_w:
				{
					mainCamera.moveForward(3);
				}
				break;
				case SDLK_s:
				{
					mainCamera.moveForward(-3);
					
				}
				break;
				case SDLK_SPACE:
				{
					mainCamera.moveUp(3);
				}
				break;
				case SDLK_LSHIFT:
				{
					mainCamera.moveUp(-3);
				}
				break;
				case SDLK_UP:
				{
					barrierTransform.moveUp(3);
				}
				break;
				case SDLK_DOWN:
				{
					barrierTransform.moveUp(-3);
				}
				break;
				case SDLK_LEFT:
				{
					barrierTransform.moveRight(3);
				}
				break;
				case SDLK_RIGHT:
				{
					barrierTransform.moveRight(-3);
				}
				break;
				case SDLK_ESCAPE:
				{
					_gameState = GameState::EXIT;
				}
				
			}
		}
	}
}

void MainGame::collisionCheckAS(glm::vec3 obj1Position, float obj1Radius, glm::vec3 obj2Position, float obj2Radius)
{
	//Getting the distance between the two objects 
	float distance = glm::sqrt((obj2Position.x - obj1Position.x)*(obj2Position.x - obj1Position.x) + (obj2Position.y - obj1Position.y)*(obj2Position.y - obj1Position.y) + (obj2Position.z - obj1Position.z)*(obj2Position.z - obj1Position.z));

	//if this distance is less than the two radius then they are colliding
	if (distance < (obj1Radius + obj2Radius))
	{
		//resetting the counter used in the asteroid
		asCounter = 300;

		//playing the Bang sound
		audio.playSound(bang, obj1Position);
	}
}

void MainGame::collisionCheckB(glm::vec3 obj1Position, float obj1Radius, glm::vec3 obj2Position, float obj2Radius)
{
	//Getting the distance between the two objects 

	float distance = glm::sqrt((obj2Position.x - obj1Position.x)*(obj2Position.x - obj1Position.x) + (obj2Position.y - obj1Position.y)*(obj2Position.y - obj1Position.y) + (obj2Position.z - obj1Position.z)*(obj2Position.z - obj1Position.z));

	//if this distance is less than the two radius then they are colliding

	if (distance < (obj1Radius + obj2Radius))
	{
		//Resseting the barriers position
		barrierTransform.SetPosition(barrierStartPosition);

		//playing the Bang sound
		audio.playSound(bang, obj1Position);
	}
}

void MainGame::drawGame()
{
	//Clearing the display
	_gameDisplay.clear(0.0f, 0.0f, 0.0f, 1.0f);

	//Bringing in the new Shader
	Shader shader("..\\res\\shader"); 

	//Bringing in the required textures
	Texture earthT("..\\res\\Earth.jpg");
	Texture moonT("..\\res\\Moon.jpg");
	Texture asteroidT("..\\res\\Asteroid.jpg");
	Texture backgroundT("..\\res\\SpaceBackground.jpg");
	Texture barrierT("..\\res\\Concrete.jpg");

	//The following section adjusts the transform details for each object, binds and updates the shader, updates the collision and draws each mesh used within the game

	//
	//	Earth
	//
	
	transform.SetPosition(glm::vec3(0,0, 50));
	transform.SetRotation(glm::vec3(counter * 3,counter * 3, 0.0));
	transform.SetScale(glm::vec3(1.5, 1.5, 1.5));

	shader.BindShader();
	shader.Update(transform, mainCamera);
	earthT.Bind(0);
	earthM.draw();
	earthM.updateSphereData(*transform.GetPosition(), 15.0f);

	//
	//	Moon
	//

	transform.SetPosition(glm::vec3(cosf(counter * 3) * 50, sinf(counter * 3) * 50, 50));
	transform.SetRotation(glm::vec3(0.0, counter * 2, 0.0));
	transform.SetScale(glm::vec3(0.5, 0.5, 0.5));

	shader.BindShader();
	shader.Update(transform, mainCamera);
	moonT.Bind(0);
	moonM.draw();
	moonM.updateSphereData(*transform.GetPosition(), 0.6f);

	//
	// Asteroid
	//

	if (asCounter < -300)
	{
		asCounter = 300;
	}
	else
		asCounter -= 3;

	transform.SetPosition(glm::vec3(asCounter, 0, 50));
	transform.SetRotation(glm::vec3(0.0, counter * 4, 0.0));
	transform.SetScale(glm::vec3(0.05, 0.05, 0.05));

	shader.BindShader();
	shader.Update(transform, mainCamera);
	asteroidT.Bind(0);
	asteroidM.draw();
	asteroidM.updateSphereData(*transform.GetPosition(), 12.0f);

	//
	//	Barrier
	//

	transform.SetScale(glm::vec3(0.5, 0.5, 0.5));
	shader.BindShader();
	shader.Update(barrierTransform, mainCamera);
	barrierT.Bind(0);
	barrierM.draw();
	barrierM.updateSphereData(*barrierTransform.GetPosition(), 0.3f);

	//
	// Background
	//

	//Updating the trasnforms position, rotation and scale for the Backgroud
	transform.SetPosition(glm::vec3(0,0,100));
	transform.SetRotation(glm::vec3(0.0, 0.0, 0.0));
	transform.SetScale(glm::vec3(1, 1, 1));


	shader.BindShader();
	shader.Update(transform, mainCamera);
	backgroundT.Bind(0);
	backgroundOne.draw();
	backgroundTwo.draw();


	//Update Counter
	counter = counter + 0.01f;

	//Swapping buffers
	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	_gameDisplay.swapBuffer();
}

MainGame::~MainGame()
{
}