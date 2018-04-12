#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

class Bomb
{
private:
	sf::Texture bomb_texture;
	sf::Sprite bomb_sprite;

	sf::Sprite *player_ptr = nullptr; //used by scene manager

	bool destroy = false;

public:

	sf::Sprite get_sprite()const;

	bool is_destroyed()const;
	void set_destroy(bool m_destroyed);

	void collision_check(sf::Sprite player);
	void move_bomb();
	void draw(sf::RenderWindow &window);

	Bomb(sf::Vector2f position);
	~Bomb();
};

