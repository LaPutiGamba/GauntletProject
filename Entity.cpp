#include "Entity.h"
#include "MapManager.h"

Entity::Entity()
{
	_currentAnimation = 0;
	_currentState = AN_IDLE;

	_cutRect = { 0, 0 };
	_drawRect = { 0, 0 };

	_position = { 0, 0 };
	_sprite = 0;

	_collisionManager = CollisionManager::GetInstance();

	_width = MapManager::GetInstance()->GetTileWidth(0);
	_height = MapManager::GetInstance()->GetTileHeight(0);
}

Entity::~Entity()
{
}

void Entity::SetX(int x)
{
}

void Entity::SetY(int y)
{
}
