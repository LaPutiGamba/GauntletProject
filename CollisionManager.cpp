#include "CollisionManager.h"
#include "Entity.h"

CollisionManager* CollisionManager::_pInstance = nullptr;

CollisionManager::CollisionManager()
{
    _colliders.resize(0);
}

CollisionManager::~CollisionManager()
{   
}

void CollisionManager::Update()
{
    size_t cSize = _colliders.size();
    
    for (size_t i = 0; i < cSize; i++) {
        _colliders[i]->collisions.clear();
    }

    for (size_t i = 0; i < cSize-1; i++) {
        for (size_t ii = 1; ii < cSize; ii++) {
            Collider* c1 = _colliders[i];
            Collider* c2 = _colliders[ii];

            if (c1->collisionsTag & c2->type) {
                if (CheckCollision(c1, c2)) {
                    Collision col(_colliders[ii]->type, _colliders[ii]->entity);
                    _colliders[i]->collisions.emplace_back(col);
                    if (c2->collisionsTag & c1->type) {
                        Collision col2(_colliders[i]->type, _colliders[i]->entity);
                        _colliders[ii]->collisions.emplace_back(col2);
                    }
                }
            } else if (c2->collisionsTag & c1->type) {
                if (CheckCollision(c2, c1)) {
                    Collision col(_colliders[i]->type, _colliders[i]->entity);
                    _colliders[ii]->collisions.emplace_back(col);
                }
            }
        }
    }
}

void CollisionManager::RemoveCollider(Collider* collider)
{
    for (int i = 0; i < _colliders.size(); i++) {
        if (_colliders[i] == collider) {
			_colliders.erase(_colliders.begin() + i);
			break;
		}
	}
}

bool CollisionManager::CheckCollision(Collider* collider1, Collider* collider2)
{
    if (collider1->x + collider1->width < collider2->x) 
        return false;
    if (collider1->x > collider2->x + collider2->width) 
        return false;
    if (collider1->y + collider1->height < collider2->y) 
        return false;
    if (collider1->y > collider2->y + collider2->height) 
        return false;
    return true;
}
