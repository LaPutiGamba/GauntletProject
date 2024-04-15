#pragma once
#include <vector>


class CollisionManager
{
public:
	enum CollisionType
	{
		CT_NONE = 0,
		CT_PLAYER = 1,
		CT_WALL = 2,
		CT_ENEMY = 4,
		CT_BULLET = 8
	};
	struct Collision
	{
		int id;
		Collision(int x) : id(x) {}
	};
	struct Collider
	{
		int x; 
		int y;
		int width;
		int height;
		int type;
		int collisionsTag;
		std::vector<Collision> collisions;
	};

private:
	std::vector<Collider*> _colliders; ///< List of colliders
	static CollisionManager* _pInstance; ///< Singleton instance

protected:
	CollisionManager();

public:
	~CollisionManager();

	/// \brief Update the collision manager
	void Update();

	/// \brief Add a collider to the list
	/// \param collider The collider to add
	void AddCollider(Collider* collider) { _colliders.push_back(collider); }

	/// \brief Remove a collider from the list
	/// \param collider The collider to remove
	void RemoveCollider(Collider* collider);

	/// \brief Check for collisions
	///  \param The first collider to check
	/// \param The second collider to check
	/// \return True if the colliders are colliding or false if they are not
	bool CheckCollision(Collider* collider1, Collider* collider2);

	/// \brief Get the instance of the collision manager
	/// \return The instance of the collision manager
	static CollisionManager* GetInstance() {
		if (_pInstance == NULL)
			_pInstance = new CollisionManager();
		return _pInstance;
	}
};

