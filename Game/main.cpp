#include "Game.h"

int main() 
{
	srand(time(NULL));
	Game* game = new Game();

	if (game != NULL) 
	{
		game->InitGame();
		game->Play();
		game->DestroyGame();
		delete game;
	}

	return 0;
}