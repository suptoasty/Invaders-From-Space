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
	float alien_down_speed = 0.0f; //moves the aliens down
	float speed_mod = 3; //modifis the speed of the aliens movement without causing them to get stuck out of bounds triggering the down_speed to be 20 for every frame
	
	//missiles
	const int MISSILE_LIMIT = 5; //missile limit
	std::list<Missile*> missile_list; //stores the missiles in the scene

	//bombs
	float bomb_speed = 5.0f; //bomb speed
	const int BOMB_LIMIT = MISSILE_LIMIT*2; //ballances the game
	std::list<Bomb*> bomb_list; //holds list of bombs ennemies drop
	int random; //must not be local to bomb dropping  code in collision check since it is a nested loop
	bool toggle_bomb = false;
	//player
	Player *m_player = nullptr; //points to scenes player
	
	//scene manager
	int level = 1; //level count
	
	bool all_aliens_destroyed = false; //win flag
	bool player_destroyed = false; //lose flag


public:
	int lives = 2; //players lives
	int aliens_destroyed = 0; //number of aliens destroyed for game
	bool start = false; //used to start game

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
	void repopulate_scene(); //makes new enemies and player
	
	int get_level()const; //returns the current level
	void next_level(); //increments level
	
	bool is_win() const; //win condition
	void set_win(bool win); //wins the game and helps exit

	bool is_loss()const; //los condition
	void set_lose(bool lose); //loses the game and exits
	
	void check_collision_state(); //checks if nodes are colliding in the scene
	void update(sf::RenderWindow &window); //glob function for scene manager
	void game_started(); //start game
	void clean_up(); //delete everything left over when stopping game

	SceneManager();
	~SceneManager();
};

