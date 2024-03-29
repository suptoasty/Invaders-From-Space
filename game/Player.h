#pragma once
#include <iostream>
#include<SFML\Graphics.hpp>

class Player
{
private:
	sf::Texture player_texture;
	sf::Sprite player_sprite;
	sf::Vector2f position{ 400,500 };

	bool destroy = false;


public:
	Player * get_player();

	sf::Texture get_texture() const;
	void set_texture(sf::Texture m_player_texture);
	sf::Sprite get_sprite()const;
	void set_sprite(sf::Sprite m_player_sprite);

	bool is_destroyed()const;
	void set_destroy(bool m_destroyed);

	sf::Vector2f get_position() const;

	void collision_check(sf::Sprite bomb, int &lives);
	void set_position(sf::Vector2f m_position);
	void poll_events(sf::RenderWindow &window);
	void move_player();

	void draw(sf::RenderWindow &window);

	Player();
	~Player();
};

