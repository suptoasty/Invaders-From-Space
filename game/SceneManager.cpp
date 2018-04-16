#include "SceneManager.h"

//////////////////////////////////////////////////
//////aliens//////
//////////////////////////////////////////////////

/*
	draws every alien in alien_list
*/
void SceneManager::draw_aliens(sf::RenderWindow & window)
{
	std::list<Alien*>::iterator iter = alien_list.begin();
	while (iter != alien_list.end())
	{
		(*iter)->draw(window, alien_speed, alien_down_speed);
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
				if(alien_list.size() <= 10)
					alien_speed += alien_speed/10;
				aliens_destroyed += 1;
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

//////////////////////////////////////////////////
//////missiles//////
//////////////////////////////////////////////////

//makes missile objects and adds pointers to them to list
void SceneManager::make_missile()
{
	if (missile_list.size() != 5)
	{
		missile_list.push_back(new Missile(sf::Vector2f(m_player->get_sprite().getPosition().x+5, m_player->get_sprite().getPosition().y - m_player->get_texture().getSize().y)));
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

//////////////////////////////////////////////////
//////bombs//////
//////////////////////////////////////////////////

//makes all missiles in missile_list
void SceneManager::make_bomb(sf::Sprite alien)
{
	//random alien position
	if(bomb_list.size() < BOMB_LIMIT)
		bomb_list.push_back(new Bomb(alien.getPosition()));
}

//draws all bombs in bomb_list
void SceneManager::draw_bombs(sf::RenderWindow & window)
{
	std::list<Bomb*>::iterator iter = bomb_list.begin();
	while (iter != bomb_list.end())
	{
		(*iter)->draw(window, bomb_speed);
		iter++;
	}
}

//detroys all bombs in bomb_list
void SceneManager::destroy_bombs()
{
	if (bomb_list.size() > 0)
	{
		std::list<Bomb*>::iterator iter = bomb_list.begin();
		while (iter != bomb_list.end())
		{
			if ((*iter)->is_destroyed())
				iter = bomb_list.erase(iter++);
			else
				iter++;
		}
	}
}

//////////////////////////////////////////////////
//////scene manager//////
//////////////////////////////////////////////////

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

//checks if game is lost
bool SceneManager::is_loss() const
{
	return player_destroyed;
}

//sets player_destroyed flag
void SceneManager::set_lose(bool lose)
{
	player_destroyed = lose;
}

/*
compares every missile_sprite to every alien_sprite and
if they intersect set the flag to be destroyed
also works bomb log...threw it in here because I got lazy and iterating through what bombs are deleted
*/
void SceneManager::check_collision_state()
{
	if (alien_list.size() > 0)
	{
		std::list<Alien*>::iterator a_iter = alien_list.begin();
		while (a_iter != alien_list.end())
		{
			std::list<Missile*>::iterator m_iter = missile_list.begin();
			while (m_iter != missile_list.end())
			{
				if ((*m_iter)->get_sprite().getGlobalBounds().intersects((*a_iter)->get_sprite().getGlobalBounds()))
				{
					(*a_iter)->set_destroy(true);
					(*m_iter)->set_destroy(true);
				}
				m_iter++;
			}
			if ((*a_iter)->get_sprite().getPosition().x > 0 && (*a_iter)->get_sprite().getPosition().x < 800)
				alien_down_speed = 0.0f;
			else if ((*a_iter)->get_sprite().getPosition().x < 0)
			{
				alien_down_speed = 20.0f;
				alien_speed *= -1;
			}
			else if ((*a_iter)->get_sprite().getPosition().x > 800)
			{
				alien_down_speed = 20.0f;
				alien_speed *= -1;
			}
			else
			{
				alien_speed *= -1;
				alien_down_speed = 0;
			}
			if ((*a_iter)->get_sprite().getPosition().y >= 500)
				m_player->set_destroy(true);
			a_iter++;
		}
		if (bomb_list.size() != 0)
		{
			std::list<Bomb*>::iterator b_iter = bomb_list.begin();
			while (b_iter != bomb_list.end())
			{
				(*b_iter)->collision_check(m_player->get_sprite());
				m_player->collision_check((*b_iter)->get_sprite(), lives);
				if (m_player->is_destroyed() == true)
					lives--;
				b_iter++;
			}
		}
		else {
			std::srand(std::time(NULL)+random);
			random = std::rand() % 2;
			std::list<Alien*>::iterator i = alien_list.begin();
			while (i != alien_list.end())
			{
				int random2 = std::rand() % 1;
				if (random == random2)
				{
					make_bomb((*i)->get_sprite());
					random += random;
					random2 += random2 * random;
				}
				i++;
			}
		}
	}
	if (lives <= 0)
	{
		m_player->set_destroy(true);
	}
}

//make new aliens
void SceneManager::repopulate_scene()
{
	alien_speed = 3.0f;
	//inform on level in terminal
	std::cout << "Level: " << get_level() << std::endl;

	//conditions for level one
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

	//conditions for level two
	if(get_level() == 2)
	{
		if (!alien_texture2.loadFromFile("alien2.png"))
		{
			std::cout << "could not load alien2 " << std::endl;
			exit(EXIT_FAILURE);
		}
		//see destructor with same commented out code
		/*if (alien_texture_ptr != nullptr)
		{
			delete alien_texture_ptr;
			alien_texture_ptr = nullptr;
		}*/
		bomb_speed = 10.0f;
		alien_texture_ptr = &alien_texture2;
		ALIEN_COUNT_COLUMN = (std::rand() % 5)+1; //randomize enemy count for level to (helps balance game)
		ALIEN_COUNT_ROW = (std::rand() % 10)+1; //randomize enemy count for level to (helps balance game)
	}

	//makes enemies
	for (int i = 0; i < ALIEN_COUNT_COLUMN; i++)
	{
		for (int n = 0; n < ALIEN_COUNT_ROW; n++)
			alien_list.push_back(new Alien(225 + (static_cast<float>(n)*(11 * 3)), 100+(50.0f*i), alien_texture_ptr));
	}
	if (alien_list.empty())
	{
		std::cout << "No aliens" << std::endl;
	}
}

//updates game state by calling member functions like draws() and destroyes() also polls window events
void SceneManager::update(sf::RenderWindow & window)
{
	//might as well set it in collision check
	if (m_player->is_destroyed())
	{
		start = false;
		set_lose(true);
	}

	m_player->draw(window);
	draw_aliens(window);
	draw_missiles(window);
	draw_bombs(window);

	destroy_aliens();
	destroy_missiles();
	destroy_bombs();

	check_collision_state();

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

	//alien_down_speed = 0.0f;
}

void SceneManager::game_started()
{
	//creates player
	m_player = new Player;

	repopulate_scene();
}

void SceneManager::clean_up()
{
	bomb_speed = 5.0f;
	aliens_destroyed = 0;
	alien_speed = 3.0f;
	level = 1;
	if (m_player->is_destroyed())
	{
		std::cout << "loose" << std::endl;
		if (alien_list.size() > 0)
		{
			std::list<Alien*>::iterator a_iter = alien_list.begin();
			while (a_iter != alien_list.end() && alien_list.size() != 0)
			{
				a_iter = alien_list.erase(a_iter++);

			}
			std::list<Bomb*>::iterator b_iter = bomb_list.begin();
			while (b_iter != bomb_list.end() && bomb_list.size() != 0)
			{
				b_iter = bomb_list.erase(b_iter++);

			}
			std::list<Missile*>::iterator m_iter = missile_list.begin();
			while (m_iter != missile_list.end() && missile_list.size() != 0)
			{
				m_iter = missile_list.erase(m_iter++);

			}

		}
	}
	delete m_player;
}

//sets up the scene with enemies and a player
SceneManager::SceneManager()
{
	std::srand(std::time(NULL));
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
