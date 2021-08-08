#include "Game.h"
#include <iostream>
int main(int argc, char* argv[])
{
	try
	{
		Shitful::Game game;
		game.run();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
	return 0;
}