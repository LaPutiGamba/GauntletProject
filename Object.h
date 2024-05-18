#pragma once
#include "Entity.h"

/// \class Object
/// \brief The object class
class Object : public Entity
{
public:
	/// \enum Type of object
	/// \brief Enum with all the types of object
	enum ObjectType
	{
		OBJ_CHEST,
		OBJ_ENEMY_GENERATOR,
		OBJ_SIZE
	};

protected:
	ObjectType _type; ///< The type of the object

public:
	Object();
	~Object() {}

	virtual void Init() override;
	virtual void Render() override;

	/// \brief Set the type of the object
	/// \param type The type of the object
	void SetType(ObjectType type) { _type = type; }

	/// \brief Gets the type of the object
	/// \return The type of the object
	ObjectType GetType() { return _type; }
};