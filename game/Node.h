#pragma once
#include <SFML\Graphics.hpp>

//this is what the base class of all scene nodes would look like

class Node
{
private:
	sf::Sprite sprite;
	sf::Vector2f position;
	
	float DIRECTION = 0.0;

	bool destroy = false;

public:

	sf::Sprite get_sprite()const;
	void set_sprite_texture(sf::Texture *m_texture);
	
	sf::Vector2f get_position() const;
	void set_position(sf::Vector2f m_position);
	
	float get_direction()const;
	void set_direction(float m_direction);

	bool is_destroyed()const;
	void set_destroy(bool destroyed);

	void move();
	void collision_check();
	void draw(sf::RenderWindow &window);

	Node(sf::Texture *m_texture, sf::Vector2f m_position);
	~Node();
};

