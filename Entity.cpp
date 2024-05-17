#include "Entity.h"
#include "MapManager.h"
#include "ResourceManager.h"

Entity::Entity()
{
	_currentAnimation = 0;
	_currentState = AN_IDLE;

	_cutRect = { 0, 0 };
	_drawRect = { 0, 0 };

	_position = { 0, 0 };
	_sprite = 0;

	_collisionManager = CollisionManager::GetInstance();
	_collider = nullptr;

	_width = MapManager::GetInstance()->GetTileWidth(0);
	_height = MapManager::GetInstance()->GetTileHeight(0);

}

Entity::~Entity()
{
}

void Entity::Init()
{
	_sprite = ResourceManager::GetInstance()->LoadAndGetGraphicID("images/entities.png");

	_collider = new CollisionManager::Collider();
	_collider->width = _width;
	_collider->height = _height;
	_collider->entity = this;
}
