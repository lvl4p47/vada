#include "Game.h"
#include "TextureManager.h"
#include <vector>

int scale = 2, k = 2, pk = 1, alpha = 20;
int w = 4 * scale, h = 7 * scale;
float gx = -1, gy = 0.5;

SDL_Texture* wTex;
SDL_Texture* aTex;
SDL_Texture* sTex;
SDL_Texture* mTex;
SDL_Texture* wfTex;
SDL_Texture* bfTex;
SDL_Rect srcR, destR;


Game::Game()
{

}

Game::~Game()
{

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen == true)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialized" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
			std::cout << "Window created" << std::endl;

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "Renderer created" << std::endl;
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}

	wTex = TextureManager::LoadTexture("textures/W.png", renderer);
	aTex = TextureManager::LoadTexture("textures/A.png", renderer);
	sTex = TextureManager::LoadTexture("textures/S.png", renderer);
	mTex = TextureManager::LoadTexture("textures/M.png", renderer);

	wfTex = TextureManager::LoadTexture("textures/wf.png", renderer);
	bfTex = TextureManager::LoadTexture("textures/bf.png", renderer);
	SDL_SetTextureBlendMode(wfTex, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(bfTex, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(wfTex, alpha);
	SDL_SetTextureAlphaMod(bfTex, alpha);

	destR.h = h + 2 * scale;
	destR.w = 2 * w;
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update(Hex** g, int XG, int YG, int x, int y, bool l)
{
	int* ptr;

	int xc, yc, xn, yn, st, na, a0, a1, a2, random;
	float dp, pc;

	std::vector<std::vector<int>> min, max;
	int minmax[2][3] = { {-1, -1, 1000},
						 {-1, -1, 0}};
	ptr = g[y][x].loopneigh(g, XG, YG, 0, 1);

	st = ptr[2];
	xn = ptr[1];
	yn = ptr[0];

	g[y][x].setPR(0);
	a0 = g[y][x].angle(g, XG, YG);
	pc = 0;
	xc = x;
	yc = y;
	while ((yn != y) || (xn != x))
	{
		dp = (yn - yc) * gy + (xn - xc) * gx;

		xc = xn;
		yc = yn;

		pc += dp;
		g[yc][xc].setPR(pc);

		ptr = g[yc][xc].loopneigh(g, XG, YG, st, 1);
		g[yc][xc].setLV(!l);

		st = ptr[2];
		xn = ptr[1];
		yn = ptr[0];

		a1 = g[yc][xc].angle(g, XG, YG);
		a2 = g[yn][xn].angle(g, XG, YG);
		na = pk * (a0 + k * a1 + a2) - int(pc);

		g[yc][xc].setNA(na);
		a0 = a1;
		if (g[yc][xc].find(g, XG, YG, 0))
		{
			if (xc < XG - 1 && xc > 0 && yc < YG - 1 && yc > 0)
			{
				if (na < minmax[0][2])
				{
					minmax[0][0] = yc;
					minmax[0][1] = xc;
					minmax[0][2] = na;
					min.clear();
					min.push_back({ yc, xc }); // err
				}
				else
					if (na == minmax[0][2])
					{
						min.push_back({ yc, xc });
					}
			}
		}
		if (na > minmax[1][2])
		{
			minmax[1][0] = yc;
			minmax[1][1] = xc;
			minmax[1][2] = na;
			max.clear();
			max.push_back({ yc, xc });
		}
		else
			if (na == minmax[1][2])
			{
				max.push_back({ yc, xc });
			}

	}


	dp = (yn - yc) * gy + (xn - xc) * gx;

	xc = xn;
	yc = yn;

	pc += dp;
	g[yc][xc].setPR(pc);

	ptr = g[yc][xc].loopneigh(g, XG, YG, ptr[2], 1);
	g[yc][xc].setLV(!l);

	st = ptr[2];
	xn = ptr[1];
	yn = ptr[0];

	a1 = g[yc][xc].angle(g, XG, YG);
	a2 = g[yn][xn].angle(g, XG, YG);
	na = pk * (a0 + k * a1 + a2) - int(pc);

	g[yc][xc].setNA(na);

	if (g[yc][xc].find(g, XG, YG, 0))
	{
		if (xc < XG - 1 && xc > 0 && yc < YG - 1 && yc > 0)
		{
			if (na < minmax[0][2])
			{
				minmax[0][0] = yc;
				minmax[0][1] = xc;
				minmax[0][2] = na;
				min.clear();
				min.push_back({ yc, xc });
			}
			else
				if (na == minmax[0][2])
				{
					min.push_back({ yc, xc });
				}
		}
	}
	if (na > minmax[1][2])
	{
		minmax[1][0] = yc;
		minmax[1][1] = xc;
		minmax[1][2] = na;
		max.clear();
		max.push_back({ yc, xc });
	}
	else
		if (na == minmax[1][2])
		{
			max.push_back({ yc, xc });
		}

	if (min.size() != 0)
	{
		random = rand() % min.size();
		minmax[0][0] = min[random][0];
		minmax[0][1] = min[random][1];
	}
	if (max.size() != 0)
	{
		random = rand() % max.size();
		minmax[1][0] = max[random][0];
		minmax[1][1] = max[random][1];
	}
	if (minmax[0][0] != -1 && minmax[1][0] != -1)// && minmax[1][2] - minmax[0][2] > 0)
	{
		g[minmax[0][0]][minmax[0][1]].add(g, XG, YG, l);
		g[minmax[1][0]][minmax[1][1]].rem(g, XG, YG, l);
		
	}
}

void Game::arrupd(Hex** g, int XG, int YG, bool l)
{
	for (int i = 0; i < YG; i++)
	{
		for (int j = 0; j < XG; j++)
		{
			g[i][j].onborder(g, XG, YG);
		}
	}
}

void Game::render(Hex** g, int XG, int YG, int x, int y)
{
	bool bord, lva;

	SDL_RenderClear(renderer);

	for (int i = 0; i < YG; i++)
	{
		for (int j = 0; j < XG; j++)
		{
			destR.y = i * h;
			destR.x = (2 * j + YG - i) * w;
			bord = g[i][j].getBD();
			//lva = g[i][j].getLV();
			{
				switch (g[i][j].getAN())
				{
				case 0:
					SDL_RenderCopy(renderer, aTex, NULL, &destR);
					if (bord)
						SDL_RenderCopy(renderer, bfTex, NULL, &destR);
					break;
				case 1:
					SDL_RenderCopy(renderer, wTex, NULL, &destR);
					if (bord)
						SDL_RenderCopy(renderer, bfTex, NULL, &destR);
					break;
				case 2:
					SDL_RenderCopy(renderer, mTex, NULL, &destR);
					if (bord)
						SDL_RenderCopy(renderer, bfTex, NULL, &destR);
					break;
				}
				/*
				if (lva)
					SDL_RenderCopy(renderer, bfTex, NULL, &destR);
				else
					SDL_RenderCopy(renderer, wfTex, NULL, &destR);
					//*/
			}
		}
	}
	//destR.y = y * h;
	//destR.x = (2 * x + YG - y) * w;
	//SDL_RenderCopy(renderer, sTex, NULL, &destR);

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}