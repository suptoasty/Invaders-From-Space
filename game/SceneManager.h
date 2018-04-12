#pragma once
#include <list>
#include "Alien.h"
#include "Player.h"
#include "Missile.h"

class SceneManager
{
private:
	int level = 1;

	const int ALIEN_COUNT = 10;
	sf::Texture alien_texture; //load static image from file for sprite...changes so it is in scene manager
	sf::Texture alien_texture2; //level 2 load static image from file for sprite...changes so it is in scene manager
	sf::Texture *alien_texture_ptr; //added texture in scene manager passes this pointer to alien instances
	std::list<Alien*> alien_list; //linked list of Alien objects
	std::list<Alien*> *list_ptr; //ptr to Alien linked list
	
	const int MISSILE_LIMIT = 5;
	std::list<Missile*> missile_list; //stores the missiles in the scene
	
	Player *m_player; //points to scenes player
	
	bool repopulate = false;
	bool all_aliens_destroyed = false; //win flag


public:

	//aliens
	std::list<Alien*> *get_alien_list() const; //returns pointer to alien_list
	void draw_aliens(sf::RenderWindow &window); //calls draw in all aliens passing them the window to draw themselves on
	void destroy_aliens(); //use to test delting from list
	
	//missiles
	void make_missile(); //makes missiles limits them to missile limit
	void destroy_missiles(); //destroys missile
	void draw_missiles(sf::RenderWindow &window); //draws missiles

	//scene manager exclusives
	bool get_repopulate()const;
	void set_repopulate(bool repop);
	void repopulate_scene();
	int get_level()const;
	void next_level();
	bool is_win() const; //win condition
	void set_win(bool win);
	void check_collision_state();
	void update(sf::RenderWindow &window, sf::Sprite &missile);

	SceneManager();
	~SceneManager();
};

