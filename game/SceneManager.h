#pragma once
#include <list>
#include "Alien.h"
#include "Player.h"
#include "Missile.h"
#include "Bomb.h"

class SceneManager
{
private:

	//aliens
	int ALIEN_COUNT_COLUMN = 1; //number of columns of rows of n number of aliens
	int ALIEN_COUNT_ROW = 10; //aliens in row
	
	sf::Texture alien_texture; //load static image from file for sprite...changes so it is in scene manager
	sf::Texture alien_texture2; //level 2 load static image from file for sprite...changes so it is in scene manager
	sf::Texture *alien_texture_ptr = nullptr; //added texture in scene manager passes this pointer to alien instances

	std::list<Alien*> alien_list; //linked list of Alien objects

	float alien_speed = 3.0f; //used for direction and speed after aliens are destroyed
	float alien_down_speed = 0.0f;
	
	//missiles
	const int MISSILE_LIMIT = 5;
	std::list<Missile*> missile_list; //stores the missiles in the scene

	//bombs
	float bomb_speed = 5.0f;
	const int BOMB_LIMIT = MISSILE_LIMIT*2; //ballances the game
	std::list<Bomb*> bomb_list; //holds list of bombs ennemies drop
	int random; //must not be local to bomb dropping  code in collision check since it is a nested loop
	
	//player
	Player *m_player = nullptr; //points to scenes player
	
	//scene manager
	int level = 1; //level count
	
	bool all_aliens_destroyed = false; //win flag
	bool player_destroyed = false; //lose flag


public:
	int lives = 2;
	int aliens_destroyed = 0;
	bool start = false;
	//aliens
	void draw_aliens(sf::RenderWindow &window); //calls draw in all aliens passing them the window to draw themselves on
	void destroy_aliens(); //use to test delting from list
	
	//missiles
	void make_missile(); //makes missiles limits them to missile limit
	void destroy_missiles(); //destroys missile
	void draw_missiles(sf::RenderWindow &window); //draws missiles

	//bombs
	void make_bomb(sf::Sprite alien); //makes bombs based off of random alien position
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
	void clean_up();

	SceneManager();
	~SceneManager();
};

