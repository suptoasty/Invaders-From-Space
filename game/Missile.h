#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

class Missile
{
private:
	sf::Texture missile_texture;
	sf::Sprite missile_sprite;
	sf::Sprite *player; //use to get start position of missile

	bool destroy = false;

public:
	Missile * get_missile();
	sf::Sprite get_sprite()const;

	bool is_destroyed()const;
	void set_destroy(bool m_destroyed);

	void collision_check(sf::Sprite alien);

	void move_missile();
	void draw(sf::RenderWindow &window);

	Missile(sf::Vector2f position);
	~Missile();
};

