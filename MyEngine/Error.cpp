#include <SDL/SDL.h>
#include <iostream>
#include <string>
#include <cstdlib>


void fatalError(std::string errorString) {
	std::cout << errorString << std::endl;
	std::cout << "Enter any key to quit";
	int temp;
	std::cin >> temp;
	SDL_Quit();
	exit(69);
}