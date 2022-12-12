#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>

enum chesspieces {
	WP,
	WR,
	WN,
	WB,
	WK,
	WQ,
	BP,
	BR,
	BN,
	BB,
	BK,
	BQ,
	BOARD,
	VA,
	NO
};
class SDL
{
public:
	//Game window size
	static const int SCREEN_WIDTH = 720;
	static const int SCREEN_HEIGHT = 480;
	//Start the window and game
	bool Start();
	//gameloop
	void GameLoop();
	//close and free
	void Close();
	//render board
	void Render();
	//load a texture
	void LoadTexture(std::string path);
	//select a piece
	void Select();
	//checks for all valid moves of a piece
	void ValidMove();
	//resets valid array
	void ValidClear();
	//Game window
	SDL_Window* gWindow = NULL;
	//Surface of game window
	SDL_Surface* gScreenSurface = NULL;
	//Displayed game window surface
	SDL_Surface* gCurrentSurface = NULL;
	//Renderer
	SDL_Renderer* gRenderer = NULL;
	//chess board
	int board [8] [8] =
	{
		{BR, BN, BB, BQ, BK, BB, BN, BR},
		{BP, BP, BP, BP, BP, BP, BP, BP},
		{NO, NO, NO, NO, NO, NO, NO, NO},
		{NO, NO, NO, NO, NO, NO, NO, NO},
		{NO, NO, NO, NO, NO, NO, NO, NO},
		{NO, NO, NO, NO, NO, NO, NO, NO},
		{WP, WP, WP, WP, WP, WP, WP, WP},
		{WR, WN, WB, WQ, WK, WB, WN, WR}
	};
	int valid[8][8] =
	{
		{NO, NO, NO, NO, NO, NO, NO, NO},
		{NO, NO, NO, NO, NO, NO, NO, NO},
		{NO, NO, NO, NO, NO, NO, NO, NO},
		{NO, NO, NO, NO, NO, NO, NO, NO},
		{NO, NO, NO, NO, NO, NO, NO, NO},
		{NO, NO, NO, NO, NO, NO, NO, NO},
		{NO, NO, NO, NO, NO, NO, NO, NO},
		{NO, NO, NO, NO, NO, NO, NO, NO}
	};
	std::vector<SDL_Texture*> textures;
	int tileSize;
	int offX;
	int offY;
	SDL_Point selected = {-1, 0};
private:
};