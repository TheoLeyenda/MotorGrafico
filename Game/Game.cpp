#include "Game.h"

Game::Game(){}

Game::~Game(){}

void Game::Play()
{
	Game::Update();
}

int Game::InitGame()
{
	resultInit = GameBase::InitGame();
	return resultInit;
	//return 0;
}

void Game::Update()
{
	GameBase::Update();
}

void Game::DestroyGame()
{
	GameBase::DestroyGame();
}
