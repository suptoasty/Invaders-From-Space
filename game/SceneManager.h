#pragma once
#include <list>
#include "Alien.h"
#include "Player.h"
#include "Missile.h"

class SceneManager
{
private:
	const int ALIEN_COUNT = 10;
	std::list<Alien*> alien_list; //linked list of Alien objects
	std::list<Alien*> *list_ptr; //ptr to Alien linked list
	bool all_aliens_destroyed = false; //win flag

	Player *m_player;

	std::list<Missile*> missile_list;

	sf::Texture alien_texture; //load static image from file for sprite
	sf::Texture *alien_texture_ptr; //added texture in scene manager passes this pointer to alien instances
public:
	std::list<Alien*> *get_alien_list() const; //returns pointer to alien_list
	void draw_aliens(sf::RenderWindow &window); //calls draw in all aliens passing them the window to draw themselves on
	void destroy_aliens(); //use to test delting from list
	void check_collision_state();
	bool is_win() const; //win condition
	void set_win(bool win);

	void make_missile();
	void destroy_missiles();
	void draw_missiles(sf::RenderWindow &window);

	void update(sf::RenderWindow &window, sf::Sprite &missile);

	SceneManager();
	~SceneManager();
};

