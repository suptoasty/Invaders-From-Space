#include "Missile.h"



Missile * Missile::get_missile() 
{
	return this;
}

sf::Sprite Missile::get_sprite() const
{
	return missile_sprite;
}

bool Missile::is_destroyed() const
{
	return destroy;
}

void Missile::set_destroy(bool m_destroy)
{
	destroy = m_destroy;
}

void Missile::collision_check(sf::Sprite alien)
{
	if (get_sprite().getGlobalBounds().intersects(alien.getGlobalBounds()))
		destroy = true;
}

void Missile::move_missile()
{
	//put in collisioncheck
	if (missile_sprite.getPosition().y <= 0)
		destroy = true;
	else
		missile_sprite.move(sf::Vector2f(0, -5));
}

void Missile::draw(sf::RenderWindow & window)
{
	move_missile();
	window.draw(missile_sprite);
}

Missile::Missile(sf::Vector2f position)
{
	if (!missile_texture.loadFromFile("missile.png"))
	{
		std::cout << "missile texture not load" << std::endl;
		exit(EXIT_FAILURE);
	}
	missile_sprite.setTexture(missile_texture);
	missile_sprite.setPosition(position);
}


Missile::~Missile()
{
}
