#pragma once
#include <iostream>
#include <SFML\Graphics.hpp> //needed for sprite, texture, position, and RenderWindow

class Alien
{
private:
	sf::Sprite alien_sprite; //stores movable/scalable image
	sf::Vector2f position; //stores position
	bool destroyed = false; //used to poll state

public:
	Alien * get_alien(); //returns this ptr to object

	sf::Sprite get_sprite() const;


	sf::Vector2f get_position() const; //returns the position member var
	void set_position(sf::Vector2f pos); //sets position member var

	bool is_destroyed() const; //returns destroyed
	void set_destroyed(bool destroy); //if collided set true, scnmngr checks on draw for destroyed objects and frees

	void draw(sf::RenderWindow &window); //draws the object...called by scene_manager through iterator to linked list
	void collision_state(sf::Sprite missile); //checks if missile collides then re-evaluates destroyed

	Alien(sf::Texture *alien_texture); //randomizes position
	Alien(float x, float y, sf::Texture *alien_texture); //set default position
	~Alien(); //cleans up when ptr to object in linked list of scene_manager is out of scope
};

