#include "Alien.h"
#include <cmath>

Alien * Alien::get_alien()
{
	return this;
}

sf::Sprite Alien::get_sprite() const
{
	return alien_sprite;
}

void Alien::move(float &speed, float &down_speed)
{

	alien_sprite.move(speed, down_speed);
}

sf::Vector2f Alien::get_position() const
{
	return position;
}

void Alien::set_position(sf::Vector2f pos)
{
	position = pos;

	alien_sprite.setPosition(get_position());
}

bool Alien::is_destroyed() const
{
	return destroy;
}

void Alien::set_destroy(bool m_destroy)
{
	destroy = m_destroy;
}

void Alien::draw(sf::RenderWindow & window, float &speed, float &down_speed)
{
	//always update position
	move(speed, down_speed); //easier than iterating through agian for move

	//what actually draws the alien
	window.draw(alien_sprite);
}

void Alien::collision_check(sf::Sprite missile)
{
	if (alien_sprite.getGlobalBounds().intersects(missile.getGlobalBounds()))
	{
		set_destroy(true);
	}
}

Alien::Alien(sf::Texture* alien_texture)
{
	alien_sprite.setTexture((*alien_texture));
	std::srand(std::time(NULL));

	float x = std::rand() % 800;
	float y = std::rand() % 600;

	set_position(sf::Vector2f(x,y));

	alien_sprite.setPosition(get_position());
}

Alien::Alien(float x, float y, sf::Texture* alien_texture)
{
	alien_sprite.setTexture((*alien_texture));
	alien_sprite.setScale(sf::Vector2f(1.5, 1.5));
	set_position(sf::Vector2f(x,y));
	alien_sprite.setPosition(get_position());
}


Alien::~Alien()
{
}
