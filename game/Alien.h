#pragma once
#include <iostream>
#include <SFML\Graphics.hpp> //needed for sprite, texture, position, and RenderWindow

class Alien
{
private:
	sf::Texture alien_texture; //load static image from file for sprite
	sf::Sprite alien_sprite; //stores movable/scalable image
	sf::Vector2f position; //stores position
	bool destroyed = false; //used to poll state

public:
	Alien * get_alien(); //returns this ptr to object

	sf::Vector2f get_position() const; //returns the position member var
	void set_position(sf::Vector2f pos); //sets position member var

	bool is_destroyed() const;
	void set_destroyed(bool destroy); //if collided set true, scnmngr checks on draw for destroyed objects and frees

	void draw(sf::RenderWindow &window); //draws the object...called by scene_manager through iterator to linked list


	Alien(); //randomizes position
	Alien(float x, float y); //set default position
	~Alien(); //cleans up when ptr to object in linked list of scene_manager is out of scope
};

