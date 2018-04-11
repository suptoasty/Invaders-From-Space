#include "SceneManager.h"



std::list<Alien*>* SceneManager::get_alien_list() const
{
	return list_ptr;
}

void SceneManager::draw_aliens(sf::RenderWindow & window)
{
	std::list<Alien*>::iterator iter;
	for (iter = alien_list.begin(); iter != alien_list.end(); iter++)
	{
		if ((*iter)->is_destroyed())
		{
			delete (*iter)->get_alien();
		}
		(*iter)->draw(window);
	}
}

void SceneManager::destroy_aliens()
{
	//make it delete aliens that have destroyed == true from the list
	std::list<Alien*>::iterator iter = alien_list.begin();
	while(iter != alien_list.end())
	{
		//delete all aliens that have the flag destroyed set
		if((*iter)->is_destroyed())
			iter = alien_list.erase(iter);
		iter++;
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

void SceneManager::update(sf::RenderWindow & window)
{
	draw_aliens(window);
	destroy_aliens();
}

SceneManager::SceneManager()
{
	//list_ptr = &alien_list;
	for (int i = 0; i < 10; i++)
	{
		alien_list.push_back(new Alien((static_cast<float>(i)*(11*2)), 200.0f));
	}
}


SceneManager::~SceneManager()
{
}
