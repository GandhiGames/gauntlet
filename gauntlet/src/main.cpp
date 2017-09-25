#include "PCH.h"
#include "Game.h"

// Entry point of the application.
int main()
{
	
	// Set a random seed.
	srand(static_cast<unsigned int>(time(nullptr)));

	// Create the main game object.
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Roguelike Template", sf::Style::Fullscreen);
	Game game(&window);

	// Initialize and run the game object.
	game.Initialize();

	while (game.IsRunning())
	{
		game.Update();
		game.Draw();
		game.LateUpdate();
	}

	//TODO: while(game.running) update, draw, lateupdate

	// Exit the application.
	return 0;
}