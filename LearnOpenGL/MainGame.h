#pragma once
#include <SDL/SDL.h>
#include "Sprite.h"
#include "GLSLProgram.h"
#include <vector>

enum class GameState { PLAY, EXIT };

class MainGame {
public:
	MainGame();
	virtual ~MainGame();

	void run();


private:
	void initSystem();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();
	void calculateFPS();

	SDL_Window* _window;
	int _screenWidth;
	int _screenHeight;

	GameState _gameState;

	std::vector<Sprite*> _sprites;

	GLSLProgram _colorProgram;

	float _time;
	float _fps;
	float _frameTime;
	float _maxFPS;
};