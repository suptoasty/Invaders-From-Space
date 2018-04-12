#pragma once
#include <list>
#include "Alien.h"
#include "Player.h"
#include "Missile.h"
#include "Bomb.h"

class SceneManager
{
private:
	int level = 1;
	sf::RectangleShape left_bound;
	sf::RectangleShape right_bound;

	//aliens
	bool switch_direction = false; //helps aliens change direction
	const int ALIEN_COUNT_COLUMN = 1; //number of columns of rows of n number of aliens
	const int ALIEN_COUNT_ROW = 10; //aliens in row
	sf::Texture alien_texture; //load static image from file for sprite...changes so it is in scene manager
	sf::Texture alien_texture2; //level 2 load static image from file for sprite...changes so it is in scene manager
	sf::Texture *alien_texture_ptr = nullptr; //added texture in scene manager passes this pointer to alien instances
	std::list<Alien*> alien_list; //linked list of Alien objects
	std::list<Alien*> *list_ptr; //ptr to Alien linked list
	
	//missiles
	const int MISSILE_LIMIT = 5;
	std::list<Missile*> missile_list; //stores the missiles in the scene

	//bombs
	const int BOMB_LIMIT = MISSILE_LIMIT*2;
	std::list<Bomb*> bomb_list;
	//sf::Vector2f air_strike_position; //might not need depending on make_bomb
	
	//player
	Player *m_player = nullptr; //points to scenes player
	
	//scene manager
	bool repopulate = false;
	bool all_aliens_destroyed = false; //win flag
	bool player_destroyed = false; //lose flag


public:

	//aliens
	std::list<Alien*> *get_alien_list() const; //returns pointer to alien_list
	void draw_aliens(sf::RenderWindow &window); //calls draw in all aliens passing them the window to draw themselves on
	void destroy_aliens(); //use to test delting from list
	void set_switch_direction(bool change);
	bool get_switch_direction()const;
	
	//missiles
	void make_missile(); //makes missiles limits them to missile limit
	void destroy_missiles(); //destroys missile
	void draw_missiles(sf::RenderWindow &window); //draws missiles

	//bombs
	void make_bomb(); //makes bombs based off of random alien position
	void destroy_bombs(); //destroys bombs
	void draw_bombs(sf::RenderWindow &window); //draws bombs

	//scene manager exclusives
	void repopulate_scene();
	int get_level()const;
	void next_level();
	bool is_win() const; //win condition
	void set_win(bool win);
	bool is_loss()const;
	void set_lose(bool lose);
	void check_collision_state();
	void update(sf::RenderWindow &window);
	void game_started();

	SceneManager();
	~SceneManager();
};

