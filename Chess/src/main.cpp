#include "SDL.h"

int main(int argc, char* args[])
{
	SDL sdl;
	if (sdl.Start())sdl.GameLoop();
	return 0;
}