#include "Node.h"



Node::Node(sf::Texture *m_texture, sf::Vector2f m_position)
{
	set_position(m_position);
	set_sprite_texture(m_texture);
}


Node::~Node()
{
}

sf::Sprite Node::get_sprite() const
{
	return sprite;
}

void Node::set_sprite_texture(sf::Texture *m_texture)
{
	get_sprite().setTexture((*m_texture));
}

sf::Vector2f Node::get_position() const
{
	return position;
}

void Node::set_position(sf::Vector2f m_position)
{
	position = m_position;
	get_sprite().setPosition(position);
}

float Node::get_direction() const
{
	return DIRECTION;
}

void Node::set_direction(float m_direction)
{
	DIRECTION = m_direction;
}

bool Node::is_destroyed() const
{
	return destroy;
}

void Node::set_destroy(bool destroy)
{
	destroy = destroy;
}

void Node::move()
{
}

void Node::collision_check()
{
}

void Node::draw(sf::RenderWindow & window)
{
	window.draw(sprite);
}
