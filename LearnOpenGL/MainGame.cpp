#include "MainGame.h"
#include <iostream>
#include <GL/glew.h>
#include <string>
#include "Error.h"

MainGame::MainGame() : _window(nullptr), _screenHeight(600), _screenWidth(800), _gameState(GameState::PLAY), _time(0), _maxFPS(30.0f) {}

MainGame::~MainGame() {
	//dtor
}

void MainGame::run() {
	initSystem();

	_sprites.push_back(new Sprite());

	_sprites.back()->init(-1.0f, -1.0f, 1.0f, 1.0f, "textures/awesomeface.png");

	_sprites.push_back(new Sprite());

	_sprites.back()->init(0.0f, 0.0f, 1.0f, 1.0f, "textures/awesomeface.png");




	//_playerTexture = ImageLoader::loadPNG("textures/awesomeface.png");

	gameLoop();
}
void MainGame::initSystem() {
	SDL_Init(SDL_INIT_EVERYTHING);

	_window = SDL_CreateWindow("Hello OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
	if (_window == nullptr) {
		fatalError("SDL Window could not be created");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr) {
		fatalError("SDL_GL context could not be created");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatalError("Could not initialize glew");
	}

	printf("OpenGL Version: %s", glGetString(GL_VERSION));


	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	initShaders();
}

void MainGame::initShaders() {
	_colorProgram.compileShaders("shaders/colorShading.vert", "shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

void MainGame::gameLoop() {
	float startTicks, frameTicks;
	float maxFrameTicks = 1000.0f / _maxFPS;
	while (_gameState != GameState::EXIT) {
		startTicks = SDL_GetTicks();

		processInput();

		_time += 0.004;

		drawGame();

		calculateFPS();

		static int frameCount = 0;
		frameCount++;
		if (frameCount == 50) {
			std::printf("%.2ffps\n", _fps);
			frameCount = 0;
		}

		frameTicks = SDL_GetTicks() - startTicks;
		if (maxFrameTicks > frameTicks) {
			SDL_Delay(maxFrameTicks - frameTicks);
		}
	}
}
void  MainGame::processInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
			//        case SDL_MOUSEMOTION:
			//            std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			//            break;
		}
	}
}

void MainGame::drawGame() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();
	glActiveTexture(GL_TEXTURE0);

	//glBindTexture(GL_TEXTURE_2D, _playerTexture.id);

	GLuint textureLocation = _colorProgram.getUniformLocation("mySampler");
	glUniform1f(textureLocation, 0);

	//    GLuint timeLocation = _colorProgram.getUniformLocation("time");
	//    glUniform1f(timeLocation, _time);

		//_sprite.draw();

	for (int i = 0; i < _sprites.size(); i++) {
		_sprites[i]->draw();
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.unuse();

	SDL_GL_SwapWindow(_window);
}

void MainGame::calculateFPS() {
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	static float prevTicks = SDL_GetTicks();

	float currentTicks = SDL_GetTicks();
	_frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

	int count;

	if (currentFrame < NUM_SAMPLES) {
		count = currentFrame;
	}
	else {
		count = NUM_SAMPLES;
	}

	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++) {
		frameTimeAverage += frameTimes[i];
	}

	prevTicks = currentTicks;
	currentFrame++;

	frameTimeAverage /= count;
	if (frameTimeAverage > 0) {
		_fps = 1000.f / frameTimeAverage;
	}
	else {
		_fps = 0.00f;
	}
}