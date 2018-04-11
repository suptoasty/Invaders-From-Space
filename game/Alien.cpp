#include "Alien.h"
#include <cmath>

Alien * Alien::get_alien()
{
	return this;
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
	return destroyed;
}

void Alien::set_destroyed(bool destroy)
{
	destroyed = destroy;
}

void Alien::draw(sf::RenderWindow & window)
{
	//always update position
	set_position(get_position());

	//what actually draws the alien
	window.draw(alien_sprite);
}

Alien::Alien()
{
	if (!alien_texture.loadFromFile("alien.png"))
	{
		std::cout << "Could not load anlien texture. " << std::endl;
		exit(EXIT_FAILURE);
	}

	alien_sprite.setTexture(alien_texture);

	std::srand(std::time(NULL));
	float x = std::rand() % 800;

	//std::srand(std::time(NULL));
	float y = std::rand() % 600;
	set_position(sf::Vector2f(x,y));

	alien_sprite.setPosition(get_position());
}

Alien::Alien(float x, float y)
{
	if (!alien_texture.loadFromFile("alien.png"))
	{
		std::cout << "Could not load anlien texture. " << std::endl;
		exit(EXIT_FAILURE);
	}

	alien_sprite.setTexture(alien_texture);
	set_position(sf::Vector2f(x,y));
	alien_sprite.setPosition(get_position());
}


Alien::~Alien()
{
	//alien_sprite.setPosition(-get_position()); //ensure hidden
}
