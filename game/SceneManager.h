#pragma once
#include <list>
#include "Alien.h"

class SceneManager
{
private:
	std::list<Alien*> alien_list; //linked list of Alien objects
	std::list<Alien*> *list_ptr; //ptr to Alien linked list
	bool all_aliens_destroyed = false; //win flag
public:
	std::list<Alien*> *get_alien_list() const; //returns pointer to alien_list
	void draw_aliens(sf::RenderWindow &window); //calls draw in all aliens passing them the window to draw themselves on
	void destroy_aliens(); //use to test delting from list
	bool is_win() const; //win condition

	void update(sf::RenderWindow &window);

	SceneManager();
	~SceneManager();
};

