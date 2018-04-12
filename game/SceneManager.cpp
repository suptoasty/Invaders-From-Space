#include "SceneManager.h"


//might not be used
std::list<Alien*>* SceneManager::get_alien_list() const
{
	return list_ptr;
}

/*
	draws every alien in alien_list
*/
void SceneManager::draw_aliens(sf::RenderWindow & window)
{
	std::list<Alien*>::iterator iter = alien_list.begin();
	while(iter != alien_list.end())
	{
			(*iter)->draw(window);
			iter++;
	}
}

/*
	goes through list and deletes all aliens with the destroy flag set to true
	if no aliens are in the list trigger win condition
*/
void SceneManager::destroy_aliens()
{
	if (alien_list.size() > 0)
	{
		std::list<Alien*>::iterator iter = alien_list.begin();
		while (iter != alien_list.end())
		{
			if ((*iter)->is_destroyed())
			{
				iter = alien_list.erase(iter++);
			}
			else
				iter++;

		}
	}
	else
		if (get_level() == 1)
		{
			next_level();
			repopulate_scene();
		}
		else
			set_win(true);
}

/*
	compares every missile_sprite to every alien_sprite and 
	if they intersect set the flag to be destroyed
*/
void SceneManager::check_collision_state()
{
	if (alien_list.size() > 0)
	{
		std::list<Alien*>::iterator iter = alien_list.begin();
		while (iter != alien_list.end())
		{
			if (missile_list.size() > 0)
			{
				std::list<Missile*>::iterator n = missile_list.begin();
				while (n != missile_list.end())
				{
					(*iter)->collision_state((*n)->get_sprite());
					(*n)->collision_state((*iter)->get_sprite());
					n++;
				}
			}
			iter++;
		}
	}
}

//returns what level player is on
int SceneManager::get_level() const
{
	return level;
}

//increments level (capped at 2)
void SceneManager::next_level()
{
	if (get_level() < 2)
		level++;
}

//checks if the game was won
bool SceneManager::is_win() const
{
	if (all_aliens_destroyed == true)
	{
		return true;
	}
	return false;
}

//changes the win flag
void SceneManager::set_win(bool win)
{
	all_aliens_destroyed = win;
}

//makes missile objects and adds pointers to them to list
void SceneManager::make_missile()
{
	if (missile_list.size() != 5)
	{
		missile_list.push_back(new Missile(sf::Vector2f(m_player->get_sprite().getPosition().x+5, m_player->get_sprite().getPosition().y - m_player->get_texture().getSize().y)));
	}
}

//removes all missiles with the destroy flag set to true from missile_list
void SceneManager::destroy_missiles()
{
	if (missile_list.size() > 0)
	{
		std::list<Missile*>::iterator iter = missile_list.begin();
		while (iter != missile_list.end())
		{
			if ((*iter)->is_destroyed())
			{
				iter = missile_list.erase(iter++);
			}
			else
				iter++;
		}
	}
}

//draws all missiles in missile_list
void SceneManager::draw_missiles(sf::RenderWindow &window)
{
	std::list<Missile*>::iterator iter = missile_list.begin();
	while(iter != missile_list.end())
	{
			(*iter)->draw(window);
			iter++;
	}
}

//make new aliens
void SceneManager::repopulate_scene()
{
	std::cout << "Level: " << get_level() << std::endl;
	if (get_level() == 1)
	{
		//creates rows of aliens
		if (!alien_texture.loadFromFile("alien.png"))
		{
			std::cout << "Could not load anlien texture. " << std::endl;
			exit(EXIT_FAILURE);
		}
		alien_texture_ptr = &alien_texture;
	}
	if(get_level() == 2)
	{
		if (!alien_texture2.loadFromFile("alien2.png"))
		{
			std::cout << "could not load alien2 " << std::endl;
			exit(EXIT_FAILURE);
		}
		alien_texture_ptr = &alien_texture2;
	}
	for (int i = 0; i < 5; i++)
	{
		for (int n = 0; n < ALIEN_COUNT; n++)
			alien_list.push_back(new Alien(225 + (static_cast<float>(n)*(11 * 3)), 100+(50.0f*i), alien_texture_ptr));
	}
	if (alien_list.empty())
	{
		std::cout << "No aliens" << std::endl;
	}
}

//updates game state by calling member functions like draws() and destroyes() also polls window events
void SceneManager::update(sf::RenderWindow & window, sf::Sprite &missile)
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed)
			window.close();
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
				window.close();
			if (event.key.code == sf::Keyboard::Space)
			{
				make_missile();
			}

		}
	}
		//m_player->poll_events(window);
		m_player->draw(window);
		check_collision_state();
		destroy_missiles();
		destroy_aliens();
		draw_missiles(window);
		draw_aliens(window);
}

//sets up the scene with enemies and a player
SceneManager::SceneManager()
{
	//creates player
	m_player = new Player;
	
	repopulate_scene();
}

//cleans up after winning
SceneManager::~SceneManager()
{
	if (m_player != nullptr) 
	{
		delete m_player;
		m_player = nullptr;
	}
	//causes crash on exit
	/*if (alien_texture_ptr != nullptr)
	{
		delete alien_texture_ptr;
		alien_texture_ptr = nullptr;
	}*/
}
