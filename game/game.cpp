#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
#include "Game.h"
using namespace sf;

//============================================================
// Jason Lonsinger
// Programming II: MWF 12:30
// Progam 8: Space Invaders
// April 20th, 2018
//============================================================

int main()
{
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "aliens!");
	// Limit the framerate to 60 frames per second
	window.setFramerateLimit(60);

	Texture starsTexture;
	if (!starsTexture.loadFromFile("stars.jpg"))
	{
		cout << "Unable to load stars texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Font font;
	if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
	{
		cout << "could not load font: C:\\Windows\\Fonts\\arial.ttf" << endl;
		exit(EXIT_FAILURE);
	}

	Sprite background;
	background.setTexture(starsTexture);
	// The texture file is 640x480, so scale it up a little to cover 800x600 window
	background.setScale(1.5, 1.5);

	RectangleShape start_button;
	start_button.setSize(Vector2f(290, 50));
	start_button.setPosition(Vector2f(290, 25));
	start_button.setFillColor(Color::White);


	Text start_text;
	start_text.setFont(font);
	start_text.setPosition(start_button.getPosition());
	start_text.setString("Press SPACE to start");
	start_text.setFillColor(Color::Black);

	Text f;
	f.setFont(font);
	Text lives;
	lives.setFont(font);
	lives.setPosition(Vector2f(700, 0));


	SceneManager scene_manager; //handles stage/scene/whateveryoucallit and its actors/nodes/whatevers
	while (window.isOpen())
	{
		while (!scene_manager.start)
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (scene_manager.is_loss() || scene_manager.is_win())
				{
					scene_manager.lives = 2;
					scene_manager.clean_up();
					scene_manager.set_lose(false);
					scene_manager.set_win(false);

				}
				// "close requested" event: we close the window
				if (event.type == Event::Closed)
				{
					window.close();
					exit(EXIT_SUCCESS);
				}
				else if(event.type == Event::KeyPressed)
					if (event.key.code == Keyboard::Space)
					{
						scene_manager.game_started();
						scene_manager.start = true;
					}
			}
			
			window.draw(background);

			window.draw(start_button);
			window.draw(start_text);

			window.display();
		}

		//===========================================================
		// Everything from here to the end of the loop is where you put your
		// code to produce ONE frame of the animation. The next iteration of the loop will
		// render the next frame, and so on. All this happens ~ 60 times/second.
		//===========================================================

		// draw background first, so everything that's drawn later 
		// will appear on top of background
		window.draw(background);

		f.setString("aliens destroyed: "+to_string(scene_manager.aliens_destroyed));
		window.draw(f);
		lives.setString("lives: "+to_string(scene_manager.lives));
		window.draw(lives);

		//if won exit with win message
		if (scene_manager.is_win())
		{
			std::cout << "WIN" << std::endl;
			scene_manager.start = false;
		}
		//check if any aliens were destroyed
		else
		{
			scene_manager.update(window);
			window.display();
		}
	} // end body of animation loop

	return 0;
}