#include "Bomb.h"


sf::Sprite Bomb::get_sprite() const
{
	return bomb_sprite;
}

//checks if bomb is destroyed
bool Bomb::is_destroyed() const
{
	return destroy;
}

//sets destroy flag
void Bomb::set_destroy(bool m_destroy)
{
	destroy = m_destroy;
}

//check of outside window
void Bomb::collision_check(sf::Sprite player)
{
	if (bomb_sprite.getGlobalBounds().intersects(player.getGlobalBounds()))
	{
		set_destroy(true);
	}
	if (bomb_sprite.getPosition().y >= 800)
	{
		set_destroy(true);
	}
}

//move bomb
void Bomb::move_bomb()
{
	const float DIRECTION = 5.0f;
	bomb_sprite.move(0, DIRECTION);
}

//draw bomb
void Bomb::draw(sf::RenderWindow & window)
{
	move_bomb();
	window.draw(bomb_sprite);
}

//initialize bomb
Bomb::Bomb(sf::Vector2f position)
{
	if (!bomb_texture.loadFromFile("bomb.png"))
	{
		std::cout << "could not load bomb" << std::endl;
		exit(EXIT_FAILURE);
	}
	bomb_sprite.setTexture(bomb_texture);
	bomb_sprite.setScale(1.5, 1.5);
	bomb_sprite.setPosition(position);
}

Bomb::~Bomb()
{
}
