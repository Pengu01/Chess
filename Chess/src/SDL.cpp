#include "SDL.h"

bool SDL::Start()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf(SDL_GetError());
		return false;
	}
	gWindow = SDL_CreateWindow("BulletGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		printf(SDL_GetError());
		return false;
	}
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == NULL)
	{
		printf(SDL_GetError());
		return false;
	}
	gScreenSurface = SDL_GetWindowSurface(gWindow);
	return true;
}

void SDL::GameLoop()
{
	SDL_Event e;
	bool quit = false;
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	LoadTexture("src/Graphic/pawn1.png");
	LoadTexture("src/Graphic/rook1.png");
	LoadTexture("src/Graphic/horse1.png");
	LoadTexture("src/Graphic/bishop1.png");
	LoadTexture("src/Graphic/King1.png");
	LoadTexture("src/Graphic/queen1.png");
	LoadTexture("src/Graphic/pawn.png");
	LoadTexture("src/Graphic/rook.png");
	LoadTexture("src/Graphic/horse.png");
	LoadTexture("src/Graphic/bishop.png");
	LoadTexture("src/Graphic/King.png");
	LoadTexture("src/Graphic/queen.png");
	LoadTexture("src/Graphic/board.png");
	LoadTexture("src/Graphic/valid.png");
	if (SCREEN_HEIGHT > SCREEN_WIDTH)
	{
		tileSize = SCREEN_WIDTH / 8;
		offY = (SCREEN_HEIGHT - SCREEN_WIDTH) / 2;
	}
	else
	{
		tileSize = SCREEN_HEIGHT / 8;
		offX = (SCREEN_WIDTH - SCREEN_HEIGHT) / 2;
	}
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				Select();
			}
		}
		//Clear screen
		SDL_RenderClear(gRenderer);
		//render
		Render();
		//Update screen
		SDL_RenderPresent(gRenderer);
	}
	Close();
}

void SDL::Close()
{
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
}

void SDL::Render()
{
	SDL_Rect renderQuad = { offX, offY, tileSize*8, tileSize*8 };
	SDL_RenderCopyEx(gRenderer, textures[BOARD], NULL, &renderQuad, 0, NULL, SDL_FLIP_NONE);
	renderQuad.w = tileSize * 7 / 8;
	renderQuad.h = tileSize * 7 / 8;
	for (int i = 0; i < 8; i++)
	{
		for (int k = 0; k < 8; k++)
		{
			if (valid[i][k] != NO)
			{
				renderQuad.x = (k * tileSize) + offX + tileSize / 14;
				renderQuad.y = (i * tileSize) + offY + tileSize / 14;
				SDL_RenderCopyEx(gRenderer, textures[valid[i][k]], NULL, &renderQuad, 0, NULL, SDL_FLIP_NONE);
			}
		}
	}
	for (int i = 0; i < 8; i++)
	{
		for (int k = 0; k < 8; k++)
		{
			if (board[i][k] != NO)
			{
				renderQuad.x = (k * tileSize) + offX + tileSize / 14;
				renderQuad.y = (i * tileSize) + offY + tileSize / 14;
				SDL_RenderCopyEx(gRenderer, textures[board[i][k]], NULL, &renderQuad, 0, NULL, SDL_FLIP_NONE);
			}
		}
	}
}

void SDL::LoadTexture(std::string path)
{
	//texture to return
	SDL_Texture* newTexture = NULL;
	//Load image to texture
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		IMG_GetError();
		return;
	}
	//Create texture from loaded surface
	newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	if (newTexture == NULL)
	{
		printf(SDL_GetError());
		return;
	}
	//free the old surface
	SDL_FreeSurface(loadedSurface);
	textures.push_back(newTexture);
}

void SDL::Select()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	SDL_Point select = { 0, 0 };
	while (offX + tileSize * (select.x + 1) < x)
	{
		select.x++;
	}
	while (offY + tileSize * (select.y + 1) < y)
	{
		select.y++;
	}
	if (valid[select.y][select.x] == VA)
	{
		board[select.y][select.x] = board[selected.y][selected.x];
		board[selected.y][selected.x] = NO;
		selected.x = -1;
		ValidClear();
	}
	else
	{
		selected.x = select.x;
		selected.y = select.y;
		ValidMove();
	}
}

void SDL::ValidMove()
{
	ValidClear();
	switch (board[selected.y][selected.x])
	{
	case WP:
		if (board[selected.y - 1][selected.x] == NO)
		{
			valid[selected.y - 1][selected.x] = VA;
			if (selected.y == 6)
			{
				if (board[selected.y - 2][selected.x] == NO)
				{
					valid[selected.y - 2][selected.x] = VA;
				}
			}
		}
		if (board[selected.y - 1][selected.x - 1] <= 11 && board[selected.y - 1][selected.x - 1] >= 6 && selected.x > 0)
		{
			valid[selected.y - 1][selected.x - 1] = VA;
		}
		if (board[selected.y - 1][selected.x + 1] <= 11 && board[selected.y - 1][selected.x + 1] >= 6 && selected.x < 7)
		{
			valid[selected.y - 1][selected.x + 1] = VA;
		}
		break;
	case WR:
		for (int i = 1; i < 8; i++)
		{
			if (selected.y - i > -1 && board[selected.y - i][selected.x] == NO)
			{
				valid[selected.y - i][selected.x] = VA;
				continue;
			}
			if (board[selected.y - i][selected.x] <= 11 && board[selected.y - i][selected.x] >= 6 && selected.y - i > -1)
			{
				valid[selected.y - i][selected.x] = VA;
			}
			break;
		}
		for (int i = 1; i < 8; i++)
		{
			if (selected.y + i < 8 && board[selected.y + i][selected.x] == NO)
			{
				valid[selected.y + i][selected.x] = VA;
				continue;
			}
			if (board[selected.y + i][selected.x] <= 11 && board[selected.y + i][selected.x] >= 6 && selected.y + i < 8)
			{
				valid[selected.y + i][selected.x] = VA;
			}
			break;
		}
		for (int i = 1; i < 8; i++)
		{
			if (selected.x - i > -1 && board[selected.y][selected.x - i] == NO)
			{
				valid[selected.y][selected.x - i] = VA;
				continue;
			}
			if (board[selected.y][selected.x - i] <= 11 && board[selected.y][selected.x - i] >= 6 && selected.x - i > -1)
			{
				valid[selected.y][selected.x - i] = VA;
			}
			break;
		}
		for (int i = 1; i < 8; i++)
		{
			if (selected.x + i < 8 && board[selected.y][selected.x + i] == NO)
			{
				valid[selected.y][selected.x + i] = VA;
				continue;
			}
			if (board[selected.y][selected.x + i] <= 11 && board[selected.y][selected.x + i] >= 6 && selected.x + i <= 7)
			{
				valid[selected.y][selected.x + i] = VA;
			}
			break;
		}
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	case 10:
		break;
	case 11:
		break;
	}
}

void SDL::ValidClear()
{
	for (int i = 0; i < 8; i++)
	{
		for (int k = 0; k < 8; k++)
		{
			valid[i][k] = NO;
		}
	}
}
