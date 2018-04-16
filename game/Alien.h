#pragma once
#include <iostream>
#include <SFML\Graphics.hpp> //needed for sprite, texture, position, and RenderWindow

class Alien
{
private:
	sf::Sprite alien_sprite; //stores movable/scalable image
	sf::Vector2f position; //stores position
	bool destroy = false; //used to poll state

	bool hit_bound = false; //toggled to move all aliens in same direction

public:
	Alien * get_alien(); //returns this ptr to object

	sf::Sprite get_sprite() const;

	void move(float &speed, float& down_speed);

	sf::Vector2f get_position() const; //returns the position member var
	void set_position(sf::Vector2f m_position); //sets position member var

	bool is_destroyed() const; //returns destroyed
	void set_destroy(bool m_destroyed); //if collided set true, scnmngr checks on draw for destroyed objects and frees

	void draw(sf::RenderWindow &window, float &speed, float &down_speed); //draws the object...called by scene_manager through iterator to linked list
	void collision_check(sf::Sprite missile); //checks if missile collides then re-evaluates destroyed

	Alien(sf::Texture *alien_texture); //randomizes position
	Alien(float x, float y, sf::Texture *alien_texture); //set default position
	~Alien(); //cleans up when ptr to object in linked list of scene_manager is out of scope
};

