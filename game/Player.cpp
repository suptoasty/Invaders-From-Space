#include "Player.h"



Player * Player::get_player()
{
	return this;
}

sf::Texture Player::get_texture() const
{
	return player_texture;
}

void Player::set_texture(sf::Texture m_player_texture)
{
	player_sprite.setTexture(m_player_texture);
}

sf::Sprite Player::get_sprite() const
{
	return player_sprite;
}

void Player::set_sprite(sf::Sprite m_player_sprite)
{
}

bool Player::is_destroyed() const
{
	return destroy;
}

void Player::set_destroy(bool m_destroyed)
{
	destroy = m_destroyed;
}

sf::Vector2f Player::get_position() const
{
	return position;
}

void Player::collision_check(sf::Sprite bomb)
{
	if (get_sprite().getGlobalBounds().intersects(bomb.getGlobalBounds()))
		set_destroy(true);
}

void Player::set_position(sf::Vector2f m_position)
{
	position = m_position;
}

void Player::poll_events(sf::RenderWindow & window)
{

}

void Player::move_player()
{
	const float DISTANCE = 5.0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			// left arrow is pressed: move our ship left 5 pixels
			// 2nd parm is y direction. We don't want to move up/down, so it's zero.
			if(player_sprite.getPosition().x > 0)
				player_sprite.move(-DISTANCE, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			// right arrow is pressed: move our ship right 5 pixels
			if(player_sprite.getPosition().x < 800-player_texture.getSize().x)
				player_sprite.move(DISTANCE, 0);
		}
}

void Player::draw(sf::RenderWindow &window)
{
	poll_events(window);
	move_player();
	window.draw(player_sprite);
}

Player::Player()
{
	if (!player_texture.loadFromFile("ship.png"))
	{
		std::cout << "could not load ship texture" << std::endl;
		exit(EXIT_FAILURE);
	}
	player_sprite.setTexture(player_texture);
	player_sprite.setPosition(get_position());
}


Player::~Player()
{
}
