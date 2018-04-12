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

void Alien::move()
{
	float DIRECTION = 3.0f;
	if (get_hit_bound() == true)
	{
		DIRECTION *= -1;
		set_hit_bound(false); //bound changes to other side of the screen so this is toggled off
	}

	alien_sprite.move(DIRECTION, 0);
}

bool Alien::get_hit_bound() const
{
	return hit_bound;
}

void Alien::set_hit_bound(bool hit)
{
	hit_bound = hit;
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

void Alien::draw(sf::RenderWindow & window)
{
	//always update position
	move(); //easier than iterating through agian for move

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
