#include "Game.h"

int main() 
{
	srand(time(NULL));
	Game* game = new Game();

	if(game != NULL)
		game->Play();

	if (game != NULL)
		delete game;
	return 0;
}