#include "SceneManager.h"



std::list<Alien*>* SceneManager::get_alien_list() const
{
	return list_ptr;
}

void SceneManager::draw_aliens(sf::RenderWindow & window)
{
	std::list<Alien*>::iterator iter;
	for (iter = alien_list.begin(); iter != alien_list.end(); )
	{
		if ((*iter)->is_destroyed())
		{
			delete (*iter)->get_alien();
		}
		else 
		{
			(*iter)->draw(window);
			iter++;
		}
	}
}

void SceneManager::destroy_aliens()
{
	////make it delete aliens that have destroyed == true from the list
	//std::list<Alien*>::iterator iter = alien_list.begin();
	//	while (iter != alien_list.end())
	//	{
	//		//delete all aliens that have the flag destroyed set

	//		if ((*iter)->is_destroyed())
	//		{
	//			if((iter != alien_list.end()) && (next(iter) == alien_list.end()))
	//			{
	//				std::cout << "destroy end" << std::endl;
	//				alien_list.pop_back();
	//			}
	//			else
	//				iter = alien_list.erase(iter);
	//		}
	//		if (*iter > 0)
	//			iter++;
	//		else
	//			set_win(true);
	//	}
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
		set_win(true);
}

void SceneManager::check_collision_state()
{
	std::list<Alien*>::iterator iter = alien_list.begin();
	std::list<Missile*>::iterator iter2 = missile_list.begin();
		while (iter != alien_list.end() && iter2 != missile_list.end())
		{
				(*iter)->collision_state((*iter2)->get_sprite());
				(*iter2)->collision_state((*iter)->get_sprite());
				iter++;
				iter2++;
		}
}

bool SceneManager::is_win() const
{
	if (all_aliens_destroyed == true)
	{
		return true;
	}
	return false;
}

void SceneManager::set_win(bool win)
{
	all_aliens_destroyed = win;
}

void SceneManager::make_missile()
{
	if (missile_list.size() != 5)
	{
		missile_list.push_back(new Missile(sf::Vector2f(m_player->get_sprite().getPosition().x+5, m_player->get_sprite().getPosition().y - m_player->get_texture().getSize().y)));
	}
}

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

void SceneManager::draw_missiles(sf::RenderWindow &window)
{
	std::list<Missile*>::iterator iter = missile_list.begin();
	while(iter != missile_list.end())
	{
			(*iter)->draw(window);
			iter++;
	}
}

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

SceneManager::SceneManager()
{
	//list_ptr = &alien_list;
	m_player = new Player;

	if (!alien_texture.loadFromFile("alien.png"))
	{
		std::cout << "Could not load anlien texture. " << std::endl;
		exit(EXIT_FAILURE);
	}
	
	alien_texture_ptr = &alien_texture;
	for (int i = 0; i < ALIEN_COUNT; i++)
	{	
		alien_list.push_back(new Alien(20.0f+(static_cast<float>(i)*(11*3)), 50.0f, alien_texture_ptr));
	}
	if (alien_list.empty())
	{
		std::cout << "empyyy" << std::endl;
	}

}


SceneManager::~SceneManager()
{
	delete m_player;
	m_player = nullptr;
}
